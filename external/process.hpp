#pragma once

#include <TlHelp32.h>
#include <shellapi.h>
#include <winternl.h>

// TODO: Automatically CloseHandle on class destruct
const auto CloseHandleCall = [](HANDLE h) { CloseHandle(h); };
typedef std::unique_ptr<void, decltype(CloseHandleCall)> CloseHandlePtr;

class process
{
private:
	std::uint32_t pid = {};
	std::uint32_t parent_pid = {};
	std::uint32_t flags = {};

	std::wstring file = {};

public:
	process() = default;
	~process() = default;

	process(PROCESSENTRY32 entry)
	{
		pid = entry.th32ProcessID;
		parent_pid = entry.th32ParentProcessID;
		flags = entry.dwFlags;
		file = std::wstring(entry.szExeFile);
	}

public:
	static std::vector<process> enumerate_process_list()
	{
		std::vector<process> procs = {};

		const auto hnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 entry; entry.dwSize = sizeof(entry);

		if (!Process32First(hnd, &entry))
			return {};

		do
		{
			procs.emplace_back(entry);
		} while (Process32Next(hnd, &entry));

		CloseHandle(hnd);
		return procs;
	}

	static process get_by_name(std::wstring_view name, const std::vector<process>& cached_procs = {})
	{
		if (name.empty())
			return {};

		auto procs = cached_procs;
		if (procs.empty())
			procs = enumerate_process_list();

		// TODO: should it be formatted to lowercase?
		for (const auto& ctx : procs)
		{
			auto current = ctx.get_name();
			if (name.find(L".exe") == std::wstring_view::npos)
			{
				if (current.find(name) == std::wstring_view::npos)
					continue;
			}
			else
			{
				if (current != name)
					continue;
			}

			return ctx;
		}

		return {};
	}

	static process get_by_pid(std::uint32_t pid, const std::vector<process>& cached_procs = {})
	{
		if (pid == 0)
			return {};

		auto procs = cached_procs;
		if (procs.empty())
			procs = enumerate_process_list();

		for (const auto& ctx : procs)
		{
			if (pid == ctx.get_pid())
				return ctx;
		}

		return {};
	}

	static process get_by_window(std::wstring_view window, std::wstring_view clss = {}, const std::vector<process>& cached_procs = {})
	{
		if (window.empty())
			return {};

		auto procs = cached_procs;
		if (procs.empty())
			procs = enumerate_process_list();

		auto hwnd = FindWindow(clss.data(), window.data());
		if (!hwnd)
			return {};

		DWORD pid = 0;
		GetWindowThreadProcessId(hwnd, &pid);

		if (pid == 0)
			return {};

		for (const auto& ctx : procs)
		{
			if (pid == ctx.get_pid())
				return ctx;
		}

		return {};
	}

public:
	static process spawn_using_shell(std::wstring_view file, std::wstring_view params, std::wstring_view path)
	{
		SHELLEXECUTEINFO pi;
		{
			pi.cbSize = sizeof(SHELLEXECUTEINFO);
			pi.fMask = SEE_MASK_NOCLOSEPROCESS;
			pi.hwnd = nullptr;
			pi.lpVerb = L"runas";
			pi.lpFile = file.data();
			pi.lpParameters = params.data();
			pi.lpDirectory = path.data();
			pi.nShow = SW_HIDE;
			pi.hInstApp = nullptr;
		}
		ShellExecuteEx(&pi);

		auto tmp = GetProcessId(pi.hProcess);
		CloseHandle(pi.hProcess);

		return get_by_pid(tmp);
	}

public:
	inline bool is_valid() const
	{
		return pid != 0;
	}

	inline bool is_running() const
	{
		return get_by_pid(pid).is_valid();
	}

public:
	inline bool terminate() const
	{
		const auto proc = LI_FN(OpenProcess).cached()(PROCESS_TERMINATE, false, pid);
		if (proc == INVALID_HANDLE_VALUE)
			return {};

		CloseHandlePtr handle_guard(proc, CloseHandleCall);

		TerminateProcess(proc, 9);
		CloseHandle(proc);

		return true;
	}

public:
	inline std::uint32_t get_pid() const
	{
		return pid;
	}

	inline std::uint32_t get_parent_pid() const
	{
		return parent_pid;
	}

	inline std::uint32_t get_flags() const
	{
		return flags;
	}

	inline std::wstring get_name() const
	{
		return file;
	}
};
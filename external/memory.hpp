#pragma once

#include <TlHelp32.h>

class c_memory
{
private:
	std::once_flag grab_text_section_once = {};

	bool attached{};
	HANDLE process_handle{};
	DWORD process_id{};

	bool memory_compare(const std::uint8_t* bData, const std::uint8_t* bMask, const char* szMask);

public:
	c_memory() = default;
	~c_memory() = default;

	std::uintptr_t pattern_scan(std::uintptr_t dll_base, const char* sig, const char* mask);
	std::uintptr_t read_chain(std::uintptr_t dw_address, const std::vector<std::uintptr_t>& offsets);

	bool get_module(std::wstring_view mod, std::pair<std::uintptr_t, std::uintptr_t>& data);

	bool attach();

	bool read(std::uintptr_t dw_address, LPVOID lp_buffer, std::uintptr_t dw_size) const;

	template <typename T>
	T read(std::uintptr_t dwAddress, const T& tDefault = T())
	{
		T t_ret{};
		if (!read(dwAddress, &t_ret, sizeof(T)))
			return tDefault;

		return t_ret;
	}

	template <typename T>
	T resolve_offset(std::uintptr_t current_addr, std::uintptr_t module_base, const std::uint32_t relative_offset = sizeof(T))
	{
		T read_data = read<T>(current_addr);

		// failed read
		if (read_data == T())
			return T();

		T relative_address = current_addr + read_data + relative_offset;
		return relative_address - module_base;
	}

	bool write(std::uintptr_t dw_address, LPCVOID lp_buffer, std::uintptr_t dw_size) const;
	bool unload();

	template <typename T>
	bool write(std::uintptr_t dwAddress, const T& tValue)
	{
		return write(dwAddress, &tValue, sizeof(T));
	}

	void set_pid(int pid)
	{
		process_id = pid;
	}

	int get_pid() const
	{
		return process_id;
	}

	bool is_loaded() const
	{
		return true;
	}
};

inline std::unique_ptr<c_memory> memory = std::make_unique<c_memory>();
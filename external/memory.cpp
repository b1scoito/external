#include "pch.hpp"
#include "memory.hpp"

bool c_memory::memory_compare(const std::uint8_t* bData, const std::uint8_t* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++bData, ++bMask)
	{
		if (*szMask == 'x' && *bData != *bMask)
			return false;
	}

	return (*szMask == NULL);
}

std::uintptr_t c_memory::pattern_scan(std::uintptr_t dll_base, const char* sig, const char* mask)
{
	// for signatures that are hardcoded and not set
	if (!dll_base || sig == nullptr || mask == nullptr)
		return NULL;

	static std::uint32_t section_base_addr = {};
	static std::uint32_t section_size = {};

	std::call_once(grab_text_section_once, [this, dll_base]() {
		const std::uint16_t dos_sig = read<std::uint16_t>(dll_base);
		if (dos_sig != IMAGE_DOS_SIGNATURE)
			return NULL;

		const std::int32_t e_lfanew_offset = read<std::int32_t>(dll_base + FIELD_OFFSET(IMAGE_DOS_HEADER, e_lfanew)); // e_lfanew
		if (!e_lfanew_offset)
			return NULL;

		const std::uintptr_t nt_header = dll_base + e_lfanew_offset;

		const std::uint32_t e_lfanew = read<std::uint32_t>(nt_header);
		if (!e_lfanew || e_lfanew != IMAGE_NT_SIGNATURE)
			return NULL;

		const std::uint16_t num_sections = read<std::uint16_t>(nt_header + (FIELD_OFFSET(IMAGE_NT_HEADERS, FileHeader.NumberOfSections)));
		if (num_sections < 1)
			return NULL;

		const std::uint16_t size_of_optional_header = read<std::uint16_t>(nt_header + (FIELD_OFFSET(IMAGE_NT_HEADERS, FileHeader.SizeOfOptionalHeader)));
		if (!size_of_optional_header)
			return NULL;

		const std::uintptr_t first_section = nt_header + FIELD_OFFSET(IMAGE_NT_HEADERS, OptionalHeader) + size_of_optional_header;

		for (auto i = 0; i < num_sections; ++i)
		{
			const auto section = first_section + (i * sizeof(IMAGE_SECTION_HEADER));
			char section_name[IMAGE_SIZEOF_SHORT_NAME] = { 0 };

			if (read(section + FIELD_OFFSET(IMAGE_SECTION_HEADER, Name), section_name, sizeof(section_name)))
			{
				if (!strcmp(section_name, xorstr(".text")))
				{
					section_base_addr = read<std::uint32_t>(section + FIELD_OFFSET(IMAGE_SECTION_HEADER, VirtualAddress));
					section_size = read<std::uint32_t>(section + FIELD_OFFSET(IMAGE_SECTION_HEADER, Misc.VirtualSize));
					break;
				}
			}
		}

		return 1;
		});

	if (!section_base_addr || !section_size)
		return NULL;

	auto data = std::make_unique<std::uint8_t[]>(section_size);

	read(dll_base + section_base_addr, data.get(), section_size);
	for (std::uint32_t i = 0; i < section_size; ++i)
	{
		if (memory_compare((const std::uint8_t*)(data.get() + i), (const std::uint8_t*)sig, mask))
			return dll_base + section_base_addr + i;
	}

	return NULL;
}

std::uintptr_t c_memory::read_chain(std::uintptr_t dw_address, const std::vector<uintptr_t>& offsets)
{
	auto result = read<std::uintptr_t>(dw_address + offsets.at(0));

	for (size_t i = 1; i < offsets.size(); i++)
		result = read<std::uintptr_t>(result + offsets.at(i));

	return result;
}

bool c_memory::read(std::uintptr_t dw_address, LPVOID lp_buffer, std::uintptr_t dw_size) const
{
	auto ret = LI_FN(ReadProcessMemory).cached()(process_handle, (LPCVOID)dw_address, lp_buffer, dw_size, nullptr);
	return ret != 0;
}

bool c_memory::write(std::uintptr_t dw_address, LPCVOID lp_buffer, std::uintptr_t dw_size) const
{
	auto ret = LI_FN(WriteProcessMemory).cached()(process_handle, (LPVOID)dw_address, lp_buffer, dw_size, nullptr);
	return ret != 0;
}

bool c_memory::unload()
{
	return CloseHandle(process_handle) != 0;
}

bool c_memory::get_module(std::wstring_view mod, std::pair<std::uintptr_t, std::uintptr_t>& data)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
	if (handle == INVALID_HANDLE_VALUE)
		return false;

	MODULEENTRY32 entry = {}; entry.dwSize = sizeof(entry);
	if (!Module32First(handle, &entry))
	{
		CloseHandle(handle);
		return false;
	}

	do
	{
		if (mod == entry.szModule)
		{
			data = std::make_pair((std::uintptr_t)entry.modBaseAddr, (std::uintptr_t)entry.modBaseSize);
			CloseHandle(handle);

			return true;
		}
	} while (Module32Next(handle, &entry));

	CloseHandle(handle);
	return false;
}

bool c_memory::attach()
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 entry = {}; entry.dwSize = sizeof(entry);
	if (!Process32First(handle, &entry))
	{
		CloseHandle(handle);
		return false;
	}

	do
	{
		if (var::game::str_process == entry.szExeFile)
		{
			process_id = entry.th32ProcessID;
			CloseHandle(handle);

			process_handle = LI_FN(OpenProcess).cached()(PROCESS_ALL_ACCESS, false, process_id);
			attached = true;

			return true;
		}
	} while (Process32Next(handle, &entry));

	CloseHandle(handle);
	return false;
}
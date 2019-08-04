#include "utilities.hpp"

namespace utilities {
	bool get_open_process(unique_handle &process_handle, std::uint32_t process_rights, bool inherit_handle, std::uint16_t process_identifier) noexcept {
		if (!process_rights || !process_identifier)
			return false;
		
		unique_handle return_handle(OpenProcess(process_rights, inherit_handle, process_identifier));
		if (return_handle.get() == INVALID_HANDLE_VALUE)
			return false;

		process_handle.swap(return_handle);
		return true;
	}

	bool get_library_path(std::string library_name, std::string &library_path) noexcept {
		if (library_name.length() <= (size_t)0)
			return false;

		char return_value[MAX_PATH];
		if (!GetFullPathName(library_name.c_str(), MAX_PATH, return_value, NULL))
			return false;
	
		library_path += return_value;
		return true;
	}

	bool get_process_id(std::string_view process_name, int &process_id) noexcept {
		const unique_handle process_snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));
		if (process_snapshot.get() == INVALID_HANDLE_VALUE)
			return false;

		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32);

		// fix iteration
		while (Process32Next(process_snapshot.get(), &process_entry))
			if (process_entry.szExeFile == process_name)
				process_id = process_entry.th32ProcessID;

		return true;
	}
}
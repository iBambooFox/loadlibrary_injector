#include "utilities.hpp"

namespace n_utilities {
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
		HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (process_snapshot == INVALID_HANDLE_VALUE)
			return false;

		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32);

		while (Process32Next(process_snapshot, &process_entry))
			if (process_entry.szExeFile == process_name)
				process_id = process_entry.th32ProcessID;

		CloseHandle(process_snapshot);
		return true;
	}
}
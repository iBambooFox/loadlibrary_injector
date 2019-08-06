#include "utilities.hpp"

namespace utilities {
	bool get_open_process(unique_handle &process_handle, std::uint32_t process_rights, bool inherit_handle, std::uint16_t process_identifier) noexcept {
		if (!process_rights || !process_identifier)
			return false;
		
		unique_handle return_process_handle(OpenProcess(process_rights, inherit_handle, process_identifier));
		if (return_process_handle.get() == INVALID_HANDLE_VALUE)
			return false;

		process_handle = std::move(return_process_handle);
		return true;
	}

	bool get_allocated_memory(unique_memory &memory_handle, unique_handle &process_handle, data_structure data, std::uint32_t memory_rights, std::uint16_t memory_protect) noexcept {
		if (data.library_path.length() <= (size_t)0 || !data.process_identifier || !memory_rights || !memory_protect)
			return false;

		unique_memory return_memory_handle(VirtualAllocEx(process_handle.get(), 0x0, sizeof(data.library_path), memory_rights, memory_protect));
		if (return_memory_handle.get() == INVALID_HANDLE_VALUE)
			return false;

		memory_handle = std::move(return_memory_handle);
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

	bool get_process_name(PROCESSENTRY32 &process_entry, std::string_view &process_name, std::uint16_t &process_id) noexcept {
		if (!process_entry.szExeFile || process_name.length() <= (size_t)0)
			return false;

		if (process_entry.szExeFile == process_name) {
			process_id = (std::uint16_t)process_entry.th32ProcessID;
		}

		else if (process_entry.szExeFile != process_name) {
			return false;
		}

		return true;
	}

	bool get_process_id(std::string_view process_name, std::uint16_t &process_id) noexcept {
		const unique_handle process_snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));
		if (process_snapshot.get() == INVALID_HANDLE_VALUE || process_name.length() <= (size_t)0)
			return false;

		PROCESSENTRY32 process_entry;
		process_entry.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(process_snapshot.get(), &process_entry)) {
			while (Process32Next(process_snapshot.get(), &process_entry)) {
				get_process_name(process_entry, process_name, process_id);
			}
		}

		return true;
	}

	bool get_remote_thread_and_write(unique_handle &process_handle, unique_memory &memory_handle, data_structure local_data) noexcept {
		if (process_handle.get() == INVALID_HANDLE_VALUE || memory_handle.get() == INVALID_HANDLE_VALUE || local_data.library_path.length() <= (size_t)0)
			return false;

		if (WriteProcessMemory(process_handle.get(), memory_handle.get(), local_data.library_path.c_str(), local_data.library_path.size(), NULL)) {
			CreateRemoteThread(process_handle.get(), 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, memory_handle.get(), 0, 0);
		
			return true;
		}

		return false;
	}

}
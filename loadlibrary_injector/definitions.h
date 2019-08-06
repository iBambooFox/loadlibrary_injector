#pragma once
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>

struct data_structure {
	std::string library_path;
	std::uint16_t process_identifier;
};

struct handle_disposer {
	using pointer = HANDLE;
	void operator()(const HANDLE handle) const noexcept {
		CloseHandle(handle);
	}
}; using unique_handle = std::unique_ptr<void, handle_disposer>;

struct memory_disposer {
	unique_handle process_handle;
	data_structure local_data;
	
	using pointer = HANDLE;
	void operator()(const HANDLE handle) const noexcept {
		if (process_handle.get() == INVALID_HANDLE_VALUE || local_data.library_path.length() <= (size_t)0)
			return;
		
		// yo @laxol pls help me with this RAII shit here. I gotta find the address somehow, but dont define it in the first place.
		VirtualFreeEx(process_handle.get(), 0x0, local_data.library_path.size(), MEM_RELEASE);
	}
}; using unique_memory = std::unique_ptr<void, memory_disposer>;
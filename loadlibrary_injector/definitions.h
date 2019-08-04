#pragma once
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>

// check the return value of GetFullPathName when it fails
// check if virtualfreeex gets called when it falls out of scope
// fix memory_disposer

struct data_structure {
	std::string library_path;
	int process_identifier;

	data_structure() noexcept {
		library_path = "";
		process_identifier = 0;
	}
};

struct handle_disposer {
	using pointer = HANDLE;
	void operator()(const HANDLE handle) const noexcept {
		CloseHandle(handle);
	}
}; using unique_handle = std::unique_ptr<void, handle_disposer>;

struct memory_disposer{
	using pointer = LPVOID;
	void operator()(const HANDLE handle, LPVOID address, SIZE_T size, DWORD free_type) const noexcept {
		VirtualFreeEx(handle, address, size, free_type);
	}
}; using unique_memory = std::unique_ptr<LPVOID, memory_disposer>;
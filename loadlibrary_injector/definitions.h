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
	using pointer = HANDLE;
	void operator()(const HANDLE handle) const noexcept {
		VirtualFree(nullptr, sizeof(0x04), MEM_RELEASE); // fix
	}
}; using unique_memory = std::unique_ptr<void, memory_disposer>;
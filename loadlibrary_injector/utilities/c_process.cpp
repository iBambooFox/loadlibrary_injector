#include "c_process.hpp"

c_process process;

void c_process::initialise_process(const char* process_name) noexcept {
	HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (process_snapshot == INVALID_HANDLE_VALUE)
		return;

	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	while (Process32Next(process_snapshot, &process_entry))
		if (!strcmp(process_entry.szExeFile, process_name))
			this->process_index = process_entry.th32ProcessID;

	this->process_flags = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | 
		PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	CloseHandle(process_snapshot);
}
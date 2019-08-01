#include "n_process.hpp"

void n_process::initialise_process(std::string process_name) noexcept {
	HANDLE process_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (process_snapshot == INVALID_HANDLE_VALUE)
		return;

	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32Next(process_snapshot, &process_entry))
		if (process_entry.szExeFile == process_name)
			process_index = process_entry.th32ProcessID;

	CloseHandle(process_snapshot);
}
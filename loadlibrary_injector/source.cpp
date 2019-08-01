#include "utilities/n_dump.hpp"
#include "utilities/n_process.hpp"
#include "utilities/n_library.hpp"

int main(int argument_count, const char* argument_vector[]) {

	n_process::initialise_process("csgo.exe");
	n_library::initialise_library("cheat.dll");

	auto access_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	HANDLE process_handle = OpenProcess(access_rights, FALSE, n_process::process_index);
	LPVOID memory_allocated = VirtualAllocEx(process_handle, NULL, sizeof(n_library::library_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(process_handle, memory_allocated, n_library::library_path, sizeof(n_library::library_path), NULL);
	CreateRemoteThread(process_handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, memory_allocated, 0, 0);

	CloseHandle(process_handle);
	return EXIT_SUCCESS;
}
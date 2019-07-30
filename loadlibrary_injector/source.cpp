#include "utilities/c_process.hpp"
#include "utilities/c_library.hpp"
#include "utilities/c_dump.hpp"

/*
	Instead of returning EXIT_FAILURE where the process id could not be found, or consequently a handle could not be opened,
	I have implemented a very basic log system where you could check what went wrong after the application executed.

	Since the handle would fail and no memory would be allocated, this isn't destructive and shouldn't cause unknown crashes.
	The LoadLibrary method only executes if the memory has been allocated, meaning that the handle has to be valid and so the
	process id must also be correct.
*/

int main(int argument_count, const char* argument_vector[]) {
	if (argument_count < 2) {
		dump.add_entry("Invalid argument count\n");
	}

	process.initialise_process(argument_vector[1]);
	library.initialise_library(argument_vector[2]);

	if (!process.process_index) {
		dump.add_entry("Invalid process index\n");
	}

	dump.add_entry("Attempting to open process handle\n");
	HANDLE process_handle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, process.process_index);
	LPVOID memory_allocated = VirtualAllocEx(process_handle, NULL, sizeof(library.library_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	if (memory_allocated != nullptr) {
		WriteProcessMemory(process_handle, memory_allocated, library.library_path, sizeof(library.library_path), NULL);
		CreateRemoteThread(process_handle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, memory_allocated, 0, 0);
	} else {
		dump.add_entry("Allocated memory was nullptr\n");
	}

	dump.add_entry("Closing handle\n");
	CloseHandle(process_handle);

	dump.dump_log();
	return EXIT_SUCCESS;
}
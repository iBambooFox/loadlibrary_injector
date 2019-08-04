#include "utilities/utilities.hpp"

int main(int argument_count, const char* argument_vector[]) {
	if (argument_count < (SIZE_T)2)
		return EXIT_FAILURE;

	auto local_data = data_structure();
	if (!utilities::get_library_path("cheat.dll", local_data.library_path) || !utilities::get_process_id("chrome.exe", local_data.process_identifier))
		return EXIT_FAILURE;

	std::cout << "path		-> " << local_data.library_path << std::endl;
	std::cout << "size		-> " << sizeof(local_data.library_path) << std::endl;
	std::cout << "identifier	-> " << local_data.process_identifier << std::endl;

	auto process_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	const unique_handle process_handle(OpenProcess(process_rights, FALSE, local_data.process_identifier));

	/*
	auto process_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	unique_handle process_handle(OpenProcess(process_rights, FALSE, data.get()->process_identifier));
	unique_memory memory_allocated(VirtualAllocEx(process_handle.get(), NULL, sizeof(data.get()->library_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));

	// check if allocated memory is not null
	if (memory_allocated.get() != nullptr) {
		WriteProcessMemory(process_handle.get(), memory_allocated.get(), data.get()->library_path.c_str(), sizeof(data.get()->library_path), NULL);
		CreateRemoteThread(process_handle.get(), 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, memory_allocated.get(), 0, 0);
	}
	*/

	return EXIT_SUCCESS;
}
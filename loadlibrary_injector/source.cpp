#include "utilities/utilities.hpp"

int main(std::uint16_t argument_count, const char* argument_vector[]) {
	if (argument_count < (SIZE_T)2)
		; //EXIT_FAILURE

	auto local_data = data_structure();
	if (!utilities::get_library_path("cheat.dll", local_data.library_path) || !utilities::get_process_id("csgo.exe", local_data.process_identifier))
		return EXIT_FAILURE;

	std::cout << "path		-> " << local_data.library_path << std::endl;
	std::cout << "size		-> " << sizeof(local_data.library_path) << std::endl;
	std::cout << "identifier	-> " << local_data.process_identifier << std::endl;

	unique_handle process_handle(nullptr);
	unique_memory memory_handle(nullptr);

	std::uint32_t process_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	if (!utilities::get_open_process(process_handle, process_rights, false, local_data.process_identifier)) {
		return EXIT_FAILURE;
	}

	std::uint32_t memory_rights = MEM_RESERVE | MEM_COMMIT;
	if (!utilities::get_allocated_memory(memory_handle, process_handle, local_data, memory_rights, PAGE_READWRITE)) {
		return EXIT_FAILURE;
	}

	if (memory_handle.get() != INVALID_HANDLE_VALUE) {
		WriteProcessMemory(process_handle.get(), memory_handle.get(), local_data.library_path.c_str(), local_data.library_path.length, NULL);
		CreateRemoteThread(process_handle.get(), 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, memory_handle.get(), 0, 0);
	}
}
#include "utilities/utilities.hpp"

int main(std::uint16_t argument_count, const char* argument_vector[]) {
	if (argument_count < (size_t)2)
		return EXIT_FAILURE;

	auto local_data = data_structure();
	if (!utilities::get_library_path(argument_vector[1], local_data.library_path) || !utilities::get_process_id(argument_vector[2], local_data.process_identifier))
		return EXIT_FAILURE;

	std::cout << "path		-> " << local_data.library_path << std::endl;
	std::cout << "size		-> " << local_data.library_path.size() << std::endl;
	std::cout << "id		-> " << local_data.process_identifier << std::endl;

	unique_handle process_handle(nullptr);
	unique_memory memory_handle(nullptr);

	std::uint16_t process_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	if (!utilities::get_open_process(process_handle, process_rights, false, local_data.process_identifier)) {
		return EXIT_FAILURE;
	}

	std::uint16_t memory_rights = MEM_RESERVE | MEM_COMMIT;
	if (!utilities::get_allocated_memory(memory_handle, process_handle, local_data, memory_rights, PAGE_READWRITE)) {
		return EXIT_FAILURE;
	}

	utilities::get_remote_thread_and_write(process_handle, memory_handle, local_data);
}
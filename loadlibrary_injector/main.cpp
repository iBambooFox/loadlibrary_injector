#include "shared/utilities.hpp"

auto main( std::uint16_t argument_count, std::uint8_t* argument_vector[ ] ) -> std::uint32_t
{
	if ( argument_count < static_cast <std::size_t> ( 2 ) )
		return exit_condition::bad;

	auto local_data = data_structure {};
	if ( !utilities->get_library_path( reinterpret_cast <char*> ( argument_vector[ 1 ] ), local_data.library_path ) || !utilities->get_process_id( 
		reinterpret_cast <char*> ( argument_vector[ 2 ] ), local_data.process_identifier ) )
		return exit_condition::bad;

	std::cout << "path		-> " << local_data.library_path << std::endl << "size		-> " << local_data.library_path.size() 
		<< std::endl << "id		-> " << local_data.process_identifier << std::endl;

	unique_memory process_handle, data_handle;

	std::uint16_t access_rights = PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION;
	if ( !utilities->get_open_process( process_handle, access_rights, false, local_data.process_identifier ) )
		return exit_condition::bad;

	access_rights = MEM_RESERVE | MEM_COMMIT;
	if ( !utilities->get_allocated_memory( data_handle, process_handle, local_data, access_rights, PAGE_READWRITE ) )
		return exit_condition::bad;

	utilities->get_remote_thread_and_write( process_handle, data_handle, local_data );
	return exit_condition::ok;
}

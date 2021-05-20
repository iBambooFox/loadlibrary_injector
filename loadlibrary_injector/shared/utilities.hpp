#include "definitions.hpp"

constexpr std::uint16_t max_path = 260;

struct utilities_t
{
	auto get_open_process( unique_memory& process_handle, std::uint32_t process_rights, bool inherit_handle, std::uint16_t process_identifier ) -> bool
	{
		auto return_process_handle = unique_memory{ ::OpenProcess( process_rights, inherit_handle, process_identifier ) };
		if ( return_process_handle.get( ) == INVALID_HANDLE_VALUE )
			return false;

		return static_cast <bool> ( process_handle = std::move( return_process_handle ) );
	}

	auto get_allocated_memory( unique_memory& memory_handle, unique_memory& process_handle, data_structure_t local_data, std::uint32_t memory_rights, std::uint16_t memory_protect ) -> bool 
	{
		auto return_memory_handle = unique_memory{ ::VirtualAllocEx( process_handle.get( ), 0, local_data.library_path.size( ), memory_rights, memory_protect ) };
		if ( return_memory_handle.get() == INVALID_HANDLE_VALUE )
			return false;

		return static_cast <bool> ( memory_handle = std::move( return_memory_handle ) );
	}

	auto get_library_path( std::string library_name, std::string& library_path ) -> bool
	{
		if ( library_name.empty( ) )
			return false;

		char return_value[ max_path ];
		if ( !::GetFullPathNameA( library_name.c_str( ), sizeof( return_value ), return_value, 0 ) )
			return false;

		library_path += return_value;
		return true;
	}

	auto get_process_name( PROCESSENTRY32& process_entry, std::string& process_name, std::uint16_t& process_id ) -> bool
	{
		if ( !process_entry.szExeFile || process_name.empty( ) )
			return false;

		if ( process_entry.szExeFile == process_name )
		{
			return static_cast <bool> ( process_id = static_cast <std::uint16_t> ( process_entry.th32ProcessID ) );
		}

		return false;
	}

	auto get_process_id( std::string process_name, std::uint16_t& process_id ) -> bool
	{
		const auto process_snapshot = unique_memory{ ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ) };
		if ( process_snapshot.get( ) == INVALID_HANDLE_VALUE || process_name.empty( ) )
			return false;

		auto process_entry = PROCESSENTRY32 {};
		process_entry.dwSize = sizeof( process_entry );

		if ( ::Process32First( process_snapshot.get( ), &process_entry ) )
		{
			while ( ::Process32Next( process_snapshot.get( ), &process_entry ) )
			{
				get_process_name( process_entry, process_name, process_id );
			}
		}

		return true;
	}

	auto get_remote_thread_and_write( unique_memory& process_handle, unique_memory& memory_handle, data_structure_t local_data ) -> bool
	{
		if ( process_handle.get( ) == INVALID_HANDLE_VALUE || memory_handle.get( ) == INVALID_HANDLE_VALUE || local_data.library_path.empty( ) )
			return false;

		if ( ::WriteProcessMemory( process_handle.get( ), memory_handle.get( ), local_data.library_path.c_str( ), local_data.library_path.size( ), 0 ) )
		{
			auto remote_thread = unique_memory{ CreateRemoteThread( process_handle.get( ), 0, 0, reinterpret_cast <LPTHREAD_START_ROUTINE> ( LoadLibrary ), memory_handle.get( ), 0, 0 ) };
			return remote_thread.get( ) != INVALID_HANDLE_VALUE;
		}

		return false;
	}
};

utilities_t* utilities;
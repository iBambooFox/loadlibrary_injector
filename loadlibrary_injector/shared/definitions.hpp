#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>

enum exit_condition : std::uint16_t
{
	ok = 0,
	bad
};

struct data_structure
{
	std::string library_path;
	std::uint16_t process_identifier;
};

struct memory_disposer
{
	auto operator( )( void* handle ) -> void
	{
		CloseHandle( static_cast <HANDLE> ( handle ) );
	}
};

using unique_memory = std::unique_ptr <void, memory_disposer>;
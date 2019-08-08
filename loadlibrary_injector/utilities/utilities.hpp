#pragma once
#include "../definitions.h"

namespace utilities {
	bool get_open_process(unique_handle &, std::uint32_t, bool, std::uint16_t) noexcept;
	bool get_allocated_memory(unique_memory &, unique_handle &, data_structure, std::uint32_t, std::uint16_t) noexcept;
	bool get_library_path(std::string, std::string&) noexcept;
	bool get_process_name(PROCESSENTRY32&, std::string&, std::uint16_t&) noexcept;
	bool get_process_id(std::string, std::uint16_t&) noexcept;
	bool get_remote_thread_and_write(unique_handle &, unique_memory &, data_structure) noexcept;
}
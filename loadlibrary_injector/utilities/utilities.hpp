#pragma once
#include "../definitions.h"

namespace utilities {
	bool get_open_process(unique_handle&, std::uint32_t, bool, std::uint16_t) noexcept;
	bool get_library_path(std::string, std::string&) noexcept;
	bool get_process_id(std::string_view, int&) noexcept;
}
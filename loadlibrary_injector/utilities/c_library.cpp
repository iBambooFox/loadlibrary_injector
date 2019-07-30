#include "c_library.hpp"

c_library library;

void c_library::initialise_library(const char* library_name) noexcept {
	if (!library_name)
		return;
	
	GetFullPathNameA(library_name, MAX_PATH, this->library_path, 0);
}
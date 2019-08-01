#include "c_library.hpp"

using namespace injector;
void n_library::initialise_library(std::string library_name) noexcept {
	if (library_name.length() <= (size_t)0)
		return;

	std::string return_value;
	if (GetFullPathName(library_name.c_str(), MAX_PATH, (LPSTR)return_value.c_str(), NULL))
		library_path = return_value;
}
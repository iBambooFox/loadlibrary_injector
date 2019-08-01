#include "n_library.hpp"

void n_library::initialise_library(std::string library_name) noexcept {
	if (library_name.length() <= (size_t)NULL)
		return;

	GetFullPathName(library_name.c_str(), MAX_PATH, library_path, NULL);
}
#pragma once
#include "../includes.hpp"

namespace n_library {
	static char library_path[MAX_PATH];
	void initialise_library(std::string) noexcept;
};
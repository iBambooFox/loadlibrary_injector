#pragma once
#include <Windows.h>

class c_library {
public:
	char library_path[MAX_PATH];
	void initialise_library(const char*) noexcept;
};

extern c_library library;
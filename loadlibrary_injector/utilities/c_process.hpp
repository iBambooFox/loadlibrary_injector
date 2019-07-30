#pragma once
#include <Windows.h>
#include <TlHelp32.h>

class c_process {
public:
	int process_index, process_flags;
	void initialise_process(const char*) noexcept;
};

extern c_process process;
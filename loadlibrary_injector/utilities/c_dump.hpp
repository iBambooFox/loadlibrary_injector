#pragma once
#include <cstring>
#include <fstream>
#include <chrono>
#include <ctime> 

class c_dump {
public:
	std::string log;
	void dump_log() noexcept;
	void add_entry(std::string) noexcept;
};

extern c_dump dump;
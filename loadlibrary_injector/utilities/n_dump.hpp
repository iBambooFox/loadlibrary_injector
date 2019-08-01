#pragma once
#include "../includes.hpp"

namespace n_dump {
	static std::string log;
	void add_entry(std::string) noexcept;
	void dump_log() noexcept;
};
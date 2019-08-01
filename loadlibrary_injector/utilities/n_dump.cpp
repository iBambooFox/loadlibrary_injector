#include "n_dump.hpp"

void n_dump::add_entry(std::string entry) noexcept {
	log = std::string(log + "[!] " + entry);
}

void n_dump::dump_log() noexcept {
	if (log.length() <= (size_t)NULL)
		return;
	std::ofstream file ("log_dump.txt", std::ofstream::out); {
		file << "Start injector routine\n\n" + log + "\nEnd injector routine";
	}
}
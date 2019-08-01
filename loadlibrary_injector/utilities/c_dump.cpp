#include "c_dump.hpp"

using namespace injector;
void n_dump::dump_log() noexcept {
	if (sizeof(log) == NULL)
		return;
	std::ofstream file ("log_dump.txt", std::ofstream::out); {
		file << "Start injector routine\n\n" + log + "\nEnd injector routine";
	}
}

void n_dump::add_entry(std::string entry) noexcept {
	log = std::string(log + "[!] " + entry);
}
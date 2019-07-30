#include "c_dump.hpp"

c_dump dump;

void c_dump::dump_log() noexcept {
	if (sizeof(this->log) == NULL)
		return;
	std::ofstream file;
	file.open("log_dump.txt"); {
		file << "Start injector routine\n\n" + this->log + "\nEnd injector routine";
		file.close();
	}
}

void c_dump::add_entry(std::string entry) noexcept {
	this->log = std::string(this->log + "[!] " + entry);
}
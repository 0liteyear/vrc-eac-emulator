#pragma once

class utils {
public:
	static void init_logger();

	static void* scan_pattern(const char* pattern);

	static void sleep(unsigned int ms);
};

#pragma once

#include <iostream>

#define LogWarning(msg) std::cerr << "[WARNING] " << msg << '\n';

#define LOG_FATAL(msg) \
	std::cerr << "[FATAL] " << msg << '\n'; \
	exit(EXIT_FAILURE);

#pragma once

#ifndef _WIN32 || WIN32 || __WIN32__ || _WIN64 || WIN64
	#include <unistd>
#endif

#ifndef _WIN32
	#define SNPRINTF _snprinf_s
#else
	#define SNPRINTF snprintf
#endif

#include <vector>
#include <string>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

namespace Util
{
	void Sleep(int milliseconds);
	std::vector<std::string> Split(const std::string &s, char delim);
};


#pragma once

#include <iostream>

#ifdef NDEBUG
	#define Log(x)
#else
	#define Log(x) std::cout << x
#endif

#pragma once

#include <chrono>
#include <cstddef>
#include <functional>
#include <vector>

long double operator "" _Hz(unsigned long long d);
long double operator "" _kHz(unsigned long long d);
long double operator "" _MHz(unsigned long long d);
long double operator "" _GHz(unsigned long long d);

long double operator "" _Hz(long double d);
long double operator "" _kHz(long double d);
long double operator "" _MHz(long double d);
long double operator "" _GHz(long double d);

class Clock
{
	using clock_type = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds period;
	clock_type::time_point last;
	size_t tick;
	std::vector<std::pair<size_t, std::function<void()>>> callbacks;
public:
	explicit Clock(long double freq);
	void cycle(size_t count = 1);
	void addHandler(size_t onTick, std::function<void()> callback);
};

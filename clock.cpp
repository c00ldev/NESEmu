#include "clock.h"

#include <cmath>
#include <thread>
#include <cstdint>


long double operator ""_Hz(unsigned long long d) {	return d; }
long double operator ""_kHz(unsigned long long d) { return d * 1'000; }
long double operator ""_MHz(unsigned long long d) { return d * 1'000'000; }
long double operator ""_GHz(unsigned long long d) { return d * 1'000'000'000; }

long double operator ""_Hz(long double d) {	return d; }
long double operator ""_kHz(long double d) { return d * 1'000; }
long double operator ""_MHz(long double d) { return d * 1'000'000; }
long double operator ""_GHz(long double d) { return d * 1'000'000'000; }

Clock::Clock(long double freq)
	: period(static_cast<int64_t>(std::round(1'000'000'000 / freq)))
	, last(clock_type::now())
	, tick(0)
{
}

void Clock::cycle(size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		for (auto & callback : callbacks)
			if (tick % callback.first == 0)
				callback.second();
		++tick;
	}
	std::this_thread::sleep_until(last += period * count);
}

void Clock::addHandler(size_t onTick, std::function<void()> callback)
{
	callbacks.emplace_back(onTick, callback);
}

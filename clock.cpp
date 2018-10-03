#include "clock.h"

#include <chrono>
#include <thread>
#include <cmath>


Clock::Clock(long double frequency)
	: period(1.0 / frequency)
{

}

void Clock::tick()
{
	for (auto & [t, tickable] : handlers)
		if (ticks % t == 0)
			tickable.tick();
	++ticks;
}

void Clock::run()
{
	using clock_type = std::chrono::high_resolution_clock;
	clock_type::time_point start = clock_type::now();
	tick();
	std::this_thread::sleep_until(start + std::chrono::duration_cast<clock_type::duration>(std::chrono::duration<long double, std::ratio<1, 1>>(period)));
}

void Clock::addHandler(Tickable & tickable, size_t onTick)
{
	handlers.emplace_back(onTick, tickable);
}

void Clock::addHandler(long double freq, Tickable & tickable)
{
	long double per = 1.0 / freq;
	auto onTick = (size_t)std::round(per / period);
	if (onTick == 0)
		++onTick;
	addHandler(tickable, onTick);
}

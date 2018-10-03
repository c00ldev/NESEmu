#include "clock.h"

#include <thread>

#include <iostream>

Clock::Clock(long double frequency, double dutyCycle)
	: clock()
	, period(1.0 / frequency)
	, dutyCycle(dutyCycle)
{
	addHandler(1, *this);
}

bool Clock::run()
{
	clock_type::time_point start = clock_type::now();
	std::chrono::duration<long double, std::ratio<1>> duration(period);
	for (const auto & [t, obj] : handlers)
		if (ticks % t == 0)
			obj.tick();
	std::this_thread::sleep_until(start + std::chrono::duration_cast<clock_type::duration>(duration * dutyCycle));
	for (const auto & [t, obj] : handlers)
		if (ticks % t == 0)
			obj.tick_down();
	std::this_thread::sleep_until(start + std::chrono::duration_cast<clock_type::duration>(duration));
	return true;
}

void Clock::tick()
{
	std::cout << "Tick" << "\n";
}

void Clock::tick_down()
{
}

void Clock::addHandler(size_t onTick, Tickable & object)
{
	handlers.emplace_front(onTick, object);
}

void Clock::start()
{
	std::thread th([&] () {
		while (run())
			;
	});
	th.detach();
}

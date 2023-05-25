#pragma once
#include <chrono>

using namespace std::chrono;

class Timer {
public:
	Timer();
	void SetStart();
	float GetDeltaTime() const;

private:
	time_point<steady_clock> m_Start;
};
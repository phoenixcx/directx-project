#include "Timer.h"

Timer::Timer() : m_Start(steady_clock::now()) {}

void Timer::SetStart() {
	m_Start = steady_clock::now();
}

float Timer::GetDeltaTime() const {
	return duration<float>(steady_clock::now() - m_Start).count();
}
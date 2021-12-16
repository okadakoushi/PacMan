#include "stdafx.h"
#include "Timer.h"
#include "mmsystem.h"

Timer* Timer::m_instance = nullptr;

void Timer::StartTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_begin);
}

void Timer::StopTimer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_end);
	m_elapsed = double(m_end - m_begin) / m_freq;
}

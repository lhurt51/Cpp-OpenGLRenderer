#include "Profiling.h"

#include <iostream>
#include <cassert>

#include "Utils\Time\Time.h"

void ProfileTimer::StartInvocation()
{
	m_startTime = Time::GetTime();
}

void ProfileTimer::StopInvocation()
{
	if (m_startTime == 0)
	{
		std::cerr << "Error: Stop Invocation called without matching start invocation" << std::endl;
		assert(m_startTime != 0);
	}
	m_numInvocations++;
	m_totalTime += (Time::GetTime() - m_startTime);
	m_startTime = 0;
}

void ProfileTimer::DisplayAndReset(const std::string& message)
{
	std::cout << message << ((1000.0 * m_totalTime) / ((double)m_numInvocations)) << " ms" << std::endl;

	m_totalTime = 0.0;
	m_numInvocations = 0;
}

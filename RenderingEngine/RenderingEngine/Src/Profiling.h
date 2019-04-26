#pragma once

#include <string>

class ProfileTimer
{

	int		m_numInvocations;
	double	m_totalTime;
	double	m_startTime;

public:

	ProfileTimer() : m_numInvocations(0), m_totalTime(0), m_startTime(0)
	{}

	void	StartInvocation();
	void	StopInvocation();

	void	DisplayAndReset(const std::string& message);

};

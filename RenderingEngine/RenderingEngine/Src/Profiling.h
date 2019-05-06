#pragma once

#include <string>

#define PROFILING_DISABLE_MESH_DRAWING 0
#define PROFILING_DISABLE_SHADING 0
#define PROFILING_SET_1x1_VIEWPORT 0
#define PROFILING_SET_2x2_TEXTURE 0

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

	double	GetTimeAndReset(double dividend = 0);
	double	DisplayAndReset(const std::string& message, double dividend = 0, int displayedMessageLength = 40);

};

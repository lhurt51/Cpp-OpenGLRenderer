#pragma once

class ReferenceCounter
{

	int m_refCount;

public:

	ReferenceCounter()
	{
		m_refCount = 1;
	}

	inline int GetReferenceCount() { return m_refCount; }

	inline void AddReference() { m_refCount++; }
	inline bool RemoveReference() { m_refCount--; return m_refCount == 0; }
};
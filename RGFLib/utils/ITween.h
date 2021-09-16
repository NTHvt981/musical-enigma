#pragma once
#include <Windows.h>

namespace rgf
{
template <typename T>
class ITween
{
protected:
	T m_startValue;
	T m_endValue;
	DWORD m_totalTick;
	DWORD m_currentTick;

public:
	ITween( T i_startValue, T i_endValue, DWORD i_tick );
	void Reset( T i_startValue, T i_endValue, DWORD i_tick );
	int UpdateValue( DWORD i_incrementTick );
	int GetCurrentValue();
	bool IsEnd();
};
}//namespace rgf


#include "ITween.h"
namespace rgf
{
template <typename T>
ITween<T>::ITween( T i_startValue, T i_endValue, DWORD i_tick )
{
	m_startValue = i_startValue;
	m_endValue = i_endValue;
	m_totalTick = i_tick;
	m_currentTick = 0;
}
template<typename T>
void ITween<T>::Reset( T i_startValue, T i_endValue, DWORD i_tick )
{
	m_startValue = i_startValue;
	m_endValue = i_endValue;
	m_totalTick = i_tick;
	m_currentTick = 0;
}
template<typename T>
int ITween<T>::UpdateValue( DWORD i_incrementTick )
{
	m_currentTick = std::min( m_currentTick + i_incrementTick, m_totalTick );
	return this->GetCurrentValue();
}
template<typename T>
int ITween<T>::GetCurrentValue()
{
	return m_startValue + ((m_currentTick / m_totalTick) * (m_endValue - m_startValue));
}
template<typename T>
bool ITween<T>::IsEnd()
{
	return (m_currentTick == m_totalTick);
}
}
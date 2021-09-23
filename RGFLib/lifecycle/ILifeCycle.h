#pragma once
#include <Windows.h>

namespace rgf
{
class ILifeCycle
{
public:
	virtual void Init() = 0;
	virtual void Update( DWORD dt ) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};
} // namespace rgf

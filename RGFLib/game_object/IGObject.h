#pragma once
#include <queue>
#include <Windows.h>

#include "message/IMessageable.h"
#include "game/IGameInfo.h"
#include "lifecycle/ILifeCycle.h"

namespace rgf
{

/// <summary>
/// gameobject inherit imessageable and lifecycle
/// </summary>
class IGObject:public IMessageable, public ILifeCycle
{
protected:
	const IGameInfo* m_gameInfo;
	const int m_id;

public:
	IGObject( const IGameInfo& info, int id = -1 );
	virtual int GetRenderLevel() = 0;
	int GetId() { return m_id; }
};
} //namespace rgf
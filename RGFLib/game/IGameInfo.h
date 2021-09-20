#pragma once
#include "RgfConstants.h"
#include <queue>

namespace rgf
{
struct IGameInfo
{
	unsigned int m_frameRate = DEFAULT_GAME_FPS;
	/// <summary>
	/// Window width plus task bar
	/// </summary>
	unsigned int m_windowFullWidth = WINDOW_WIDTH;
	/// <summary>
	/// Window height plus task bar
	/// </summary>
	unsigned int m_windowFullHeight = WINDOW_HEIGHT;
	/// <summary>
	/// true window width
	/// </summary>
	unsigned int m_windowClientWidth = WINDOW_HEIGHT;
	/// <summary>
	/// true window height
	/// </summary>
	unsigned int m_windowClientHeight = WINDOW_HEIGHT;
};
}


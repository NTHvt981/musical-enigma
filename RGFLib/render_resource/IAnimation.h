#pragma once
#include <vector>

#include "ISpriteLib.h"

namespace rgf
{
#define ANI_MODE_NORMAL 1
#define ANI_MODE_PAUSE 0
#define ANI_MODE_REVERSE -1

/// <summary>
/// Contain sprite and its pos in animated timeline
/// </summary>
class IAnimationFrame
{
public:
	IAnimationFrame(LPSprite sprite, int time) { this->m_sprite = sprite; this->m_tick = time; }
	LPSprite m_sprite;
	DWORD m_tick;
};
typedef std::shared_ptr<IAnimationFrame> LPAnimationFrame;

/// <summary>
/// Use for animation, contains animation frame
/// </summary>
class IAnimation
{
protected:
	DWORD m_lastFrameTick;
	DWORD m_defaultTick;
	int m_currentFrame;
	int m_mode;
	std::vector<LPAnimationFrame> m_frames;

	bool m_isLoop;
	bool m_isEnd = false;
	float m_speed = 1;
	float m_alpha = 1;

	void SelfSetCurrentFrame();

public:
	IAnimation(int defaultTick, bool loop = true, int mode = ANI_MODE_NORMAL, float alpha = 1) {
		this->m_defaultTick = defaultTick;
		this->m_isLoop = loop;
		m_lastFrameTick = -1;
		m_currentFrame = 0;
		m_mode = mode;
		m_alpha = alpha;
	}
	void Add(int spriteId, DWORD time = 0);
	void Add(int spriteIds[], int size);
	/// <param name="alpha">range 0 to 1</param>
	void Render(rgf::Vector position);
	/// <param name="alpha">range 0 to 1</param>
	void Render(float x, float y);
	/// <param name="alpha">range 0 to 1</param>
	void RenderCenter(float x, float y);
	/// <param name="alpha">range 0 to 1</param>
	void RenderWithFixedPosition(float x, float y);
	int GetId();
	bool IsLoop();
	bool IsEnd();
	float GetAlpha();
	void SetAlpha(float alpha);
	void Reset();

	int GetMode();
	void SetMode(int mode);

	int GetCurrentFrame();
	void SetCurrentFrame(int frame);

	void GetSize(int& width, int& height, int frame=0);

	void SetSpeed(float _speed);
	float GetSpeed();
};
typedef std::shared_ptr<IAnimation> LPAnimation;

} //namespace rgf
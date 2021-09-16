#include "IAnimation.h"

namespace rgf
{
void IAnimation::SelfSetCurrentFrame()
{
	DWORD now = GetTickCount64();
	if (m_lastFrameTick == -1)
	{
		m_lastFrameTick = now;
	}

	DWORD t = m_frames[m_currentFrame]->m_tick;
	if ((now - m_lastFrameTick) * m_speed > t)
	{
		m_currentFrame = m_currentFrame + m_mode;
		m_lastFrameTick = now;
	}

	//check to see if current frame out of frames limit
	if (m_currentFrame == -1)
	{
		m_currentFrame = m_frames.size() - 1;

		if (!m_isLoop) {
			m_currentFrame = 0;
			m_isEnd = true;
		}
	}
	else if (m_currentFrame == m_frames.size()) {
		m_currentFrame = 0;

		if (!m_isLoop) {
			m_currentFrame = m_frames.size() - 1;
			m_isEnd = true;
		}
	}
}

void IAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->m_defaultTick;

	LPSprite sprite = ISpriteLib::GetInstance()->Get(spriteId);
	LPAnimationFrame frame = std::make_shared<IAnimationFrame>(IAnimationFrame(sprite, t));
	m_frames.push_back(frame);
}

void IAnimation::Add(int spriteIds[], int size)
{
	for (int i = 0; i < size; i++)
	{
		Add(spriteIds[i]);
	}
}

void IAnimation::Render(rgf::Vector position)
{
	Render(position.x, position.y);
}

void IAnimation::Render(float x, float y)
{
	SelfSetCurrentFrame();

	m_frames[m_currentFrame]->m_sprite->Draw(x, y, m_alpha);
}

void IAnimation::RenderCenter(float x, float y)
{
	SelfSetCurrentFrame();

	int w, h;
	m_frames[m_currentFrame]->m_sprite->GetSize(w, h);

	m_frames[m_currentFrame]->m_sprite->Draw(x - w / 2, y - h / 2, m_alpha);
}

void IAnimation::RenderWithFixedPosition(float x, float y)
{
	SelfSetCurrentFrame();

	m_frames[m_currentFrame]->m_sprite->DrawWithFixedPosition(x, y, m_alpha);
}

int IAnimation::GetId()
{
	throw("NOT IMPLEMENT");
}

bool IAnimation::IsLoop()
{
	return m_isLoop;
}

bool IAnimation::IsEnd()
{
	return m_isEnd;
}

float IAnimation::GetAlpha()
{
	return m_alpha;
}

void IAnimation::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void IAnimation::Reset()
{
	if (m_mode == ANI_MODE_NORMAL)
	{
		m_currentFrame = 0;
	}
	else if (m_mode == ANI_MODE_REVERSE)
	{
		m_currentFrame = m_frames.size() - 1;
	}
	m_isEnd = false;
}

int IAnimation::GetMode()
{
	return m_mode;
}

void IAnimation::SetMode(int mode)
{
	m_mode = mode;
}

int IAnimation::GetCurrentFrame()
{
	return m_currentFrame;
}

void IAnimation::SetCurrentFrame(int frame)
{
	m_currentFrame = frame;
}

void IAnimation::GetSize(int& width, int& height, int frame)
{
	m_frames[frame]->m_sprite->GetSize(width, height);
}

void IAnimation::SetSpeed(float speed)
{
	m_speed = speed;
}

float IAnimation::GetSpeed()
{
	return m_speed;
}

} //namespace rgf
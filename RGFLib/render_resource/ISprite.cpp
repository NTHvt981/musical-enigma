#include "ISprite.h"

namespace rgf
{
ISprite::ISprite(int id, int left, int top, int right, int bottom,
	LPDIRECT3DTEXTURE9 tex
	, float origin_x, float origin_y) {
	this->m_id = id;
	this->m_left = left;
	this->m_top = top;
	this->m_right = right;
	this->m_bottom = bottom;
	this->m_texture = tex;

	this->m_origin.x = origin_x;
	this->m_origin.y = origin_y;
}

void ISprite::Draw(float x, float y, float alpha)
{
	IGraphic::GetInstance()->Draw(m_texture, x, y,
		m_left, m_top, m_right, m_bottom, m_origin.x, m_origin.y, alpha);
}

void ISprite::DrawWithFixedPosition(float x, float y, float alpha)
{
	IGraphic::GetInstance()->DrawWithFixedPosition(m_texture, x, y,
		m_left, m_top, m_right, m_bottom, alpha);
}

void ISprite::Draw(rgf::Vector position, float alpha)
{
	Draw(position.x, position.y, alpha);
}

void ISprite::DrawOverrideOrigin(float x, float y, float origin_x, float origin_y, float alpha)
{
	IGraphic::GetInstance()->Draw(m_texture, x, y,
		m_left, m_top, m_right, m_bottom, origin_x, origin_y, alpha);
}

void ISprite::DrawOverrideOriginWithFixedPosition(float x, float y, float origin_x, float origin_y, float alpha)
{
	IGraphic::GetInstance()->DrawWithFixedPosition(m_texture, x, y,
		m_left, m_top, m_right, m_bottom, origin_x, origin_y, alpha);
}

int ISprite::GetId()
{
	return m_id;
}

void ISprite::GetSize(int& width, int& height)
{
	width = m_right - m_left + 1;
	height = m_bottom - m_top + 1;
}
} //namespace rgf

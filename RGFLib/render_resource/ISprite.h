#pragma once
#include "render/IGraphic.h"

namespace rgf
{
/// <summary>
/// Main unit of rendering, contains info for drawing
/// </summary>
class ISprite
{
	int m_id;				// Sprite ID in the sprite database
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;

	rgf::Vector m_origin;

	LPDIRECT3DTEXTURE9 m_texture;
public:
	ISprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex
		, float origin_x = 0, float origin_y = 0);

	/// <param name="alpha">range 0 to 1</param>
	void Draw(float x, float y, float alpha = 1);
	/// <param name="alpha">range 0 to 1</param>
	void DrawWithFixedPosition(float x, float y, float alpha = 1);
	/// <param name="alpha">range 0 to 1</param>
	void Draw(rgf::Vector position, float alpha = 1);

	/// <param name="alpha">range 0 to 1</param>
	void DrawOverrideOrigin(float x, float y, float origin_x, float origin_y, float alpha = 1);
	/// <param name="alpha">range 0 to 1</param>
	void DrawOverrideOriginWithFixedPosition(float x, float y, float origin_x, float origin_y, float alpha = 1);

	int GetId();
	void GetSize(int& width, int& height);
};

typedef std::shared_ptr<ISprite> LPSprite;
} //namespace rgf
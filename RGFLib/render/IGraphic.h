#pragma once

#include <comdef.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "utils/Debug.h"
#include "render/ICamera.h"
#include "utils/Vector.h"

namespace rgf
{
/// <summary>
/// [singleton] in charge of draw, rendering
/// </summary>
class IGraphic
{
protected:
	HWND m_hWnd;									// Window handle
	//static CGraphic* __instance;

	LPDIRECT3D9 m_d3d = NULL;		// Direct3D handle
	LPDIRECT3DDEVICE9 m_d3ddev = NULL;	// Direct3D device object
	LPDIRECT3DSURFACE9 m_backBuffer = NULL;
	LPD3DXSPRITE m_spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 
protected:
	static std::shared_ptr<IGraphic> m_instance;
public:
	static std::shared_ptr<IGraphic> GetInstance();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return m_backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->m_spriteHandler; }

	int Init(HWND hwnd);
	LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath);

	/// <param name="alpha">range 0 to 1</param>
	void Draw(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom,
		float origin_x = 0, float origin_y = 0, float alpha = 1);

	/// <param name="alpha">range 0 to 1</param>
	void Draw(LPDIRECT3DTEXTURE9 texture, float x, float y,
		float origin_x = 0, float origin_y = 0, float alpha = 1);

	/// <param name="alpha">range 0 to 1</param>
	void DrawWithFixedPosition(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom, 
		float origin_x = 0, float origin_y = 0, float alpha = 1
	);

	/// <param name="alpha">range 0 to 1</param>
	void DrawWithTransformation(
		LPDIRECT3DTEXTURE9 texture, float x, float y,
		int left, int top, int right, int bottom, 
		float origin_x = 0, float origin_y = 0, float alpha = 1
	);
	void SetRenderData(
		D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling);

	//void Render(LPDIRECT3DTEXTURE9 texture);

	void End();
};
} //namespace rgf
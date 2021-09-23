#pragma once

#include <comdef.h>
#ifdef D3D9
#include <d3d9.h>
#include <d3dx9.h>
#else
#include <d3d10.h>
#include <D3DX10.h>
#endif

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

#ifdef D3D9
	LPDIRECT3D9 m_d3d = NULL;		// Direct3D handle
	LPDIRECT3DDEVICE9 m_d3ddev = NULL;	// Direct3D device object
	LPDIRECT3DSURFACE9 m_backBuffer = NULL;
	LPD3DXSPRITE m_spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 
#else
	
#endif

	static std::shared_ptr<IGraphic> m_instance;
public:
	static std::shared_ptr<IGraphic> GetInstance();

#ifdef D3D9
	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->m_d3ddev; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return m_backBuffer; }
	LPDIRECT3DTEXTURE9 LoadTexture( LPCWSTR texturePath );
	LPD3DXSPRITE GetSpriteHandler() { return this->m_spriteHandler; }

	int Init(HWND hwnd);

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

	void End();
#else
	ID3D10Texture2D* LoadTexture( LPCWSTR texturePath );

	int Init( HWND hwnd );

	/// <param name="alpha">range 0 to 1</param>
	void Draw(
		ID3D10Texture2D* texture, float x, float y,
		int left, int top, int right, int bottom,
		float origin_x = 0, float origin_y = 0, float alpha = 1 );

	/// <param name="alpha">range 0 to 1</param>
	void Draw( ID3D10Texture2D* texture, float x, float y,
			   float origin_x = 0, float origin_y = 0, float alpha = 1 );

	/// <param name="alpha">range 0 to 1</param>
	void DrawWithFixedPosition(
		ID3D10Texture2D* texture, float x, float y,
		int left, int top, int right, int bottom,
		float origin_x = 0, float origin_y = 0, float alpha = 1
	);

	/// <param name="alpha">range 0 to 1</param>
	void DrawWithTransformation(
		ID3D10Texture2D* texture, float x, float y,
		int left, int top, int right, int bottom,
		float origin_x = 0, float origin_y = 0, float alpha = 1
	);
	void SetRenderData(
		D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling );

	void End();
#endif
};
} //namespace rgf
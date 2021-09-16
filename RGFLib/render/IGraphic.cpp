#include "IGraphic.h"

namespace rgf
{
std::shared_ptr<IGraphic> IGraphic::m_instance = std::make_shared<IGraphic>(IGraphic());

std::shared_ptr<IGraphic> IGraphic::GetInstance()
{
    return m_instance;
}

int IGraphic::Init(HWND hwnd)
{
	this->m_hWnd = hwnd;

	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d == NULL)
	{
		MessageBox(hwnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	/*
	Set up parameter to create directx device
	*/
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(this->m_hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_d3ddev);

	if (m_d3ddev == NULL)
	{
		//OutputDebugString(L"[ERROR] CreateDevice failed\n");
		MessageBox(hwnd, L"Error CreateDevice failed", L"Error", MB_OK);
		return 0;
	}

	m_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	HRESULT result = D3DXCreateSprite(m_d3ddev, &m_spriteHandler);
	if (!SUCCEEDED(result))
	{
		MessageBox(hwnd, L"Error CreateSprite failed", L"Error", MB_OK);
		return 0;
	}

	OutputDebugString(L"[INFO] Init graphic done;\n");
	return 1;
}

LPDIRECT3DTEXTURE9 IGraphic::LoadTexture(LPCWSTR texturePath)
{
	if (texturePath == NULL)
	{
		return NULL;
	}
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
	if (result != D3D_OK)
	{
		//DebugOut(L"[ERROR] get image info failed. Result: %s\n", result);
		MessageBox(m_hWnd, L"Error get image info failed", L"Error", MB_OK);
		return NULL;
	}

	result = D3DXCreateTextureFromFileEx(
		m_d3ddev,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(251, 255, 0),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (!SUCCEEDED(result))
	{
		_com_error err(result);
		LPCTSTR errMsg = err.ErrorMessage();
		rgf::DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s; Error Code: %s\n", texturePath, errMsg);
		return NULL;
	}

	rgf::DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
	return texture;
}

void IGraphic::Draw(
	LPDIRECT3DTEXTURE9 texture, float x, float y, 
	int left, int top, int right, int bottom, float origin_x, float origin_y, float alpha)
{
	if (ICamera::GetInstance() != NULL)
	{
		DrawWithTransformation(texture, x, y, left, top, right, bottom, alpha);
		return;
	}

	// TODO check if rem codes work the same as DrawWithFixPosition
	/*
	D3DXMATRIX matrix;

	int opacity = alpha * 255;
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	D3DXVECTOR3 position(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	spriteHandler->Draw(texture, &r, &origin, &position, D3DCOLOR_RGBA(255, 255, 255, opacity));
	*/
	this->DrawWithFixedPosition(texture, x, y, left, top, right, bottom, alpha);
}

void IGraphic::Draw(LPDIRECT3DTEXTURE9 texture, float x, float y, float origin_x, float origin_y, float alpha)
{
	int opacity = alpha * 255;
	D3DXVECTOR3 position(x, y, 0);
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	m_spriteHandler->Draw(texture, NULL, &origin, &position,
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void IGraphic::DrawWithFixedPosition(LPDIRECT3DTEXTURE9 texture, float x, float y, 
	int left, int top, int right, int bottom, 
	float origin_x, float origin_y, float alpha)
{
	int opacity = alpha * 255;
	D3DXVECTOR3 position(x, y, 0);
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	m_spriteHandler->SetTransform(&matrix);

	m_spriteHandler->Draw(texture, &r, &origin, &position,
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void IGraphic::DrawWithTransformation(LPDIRECT3DTEXTURE9 texture, float x, float y, 
	int left, int top, int right, int bottom, 
	float origin_x, float origin_y, float alpha)
{
	int opacity = alpha * 255;
	int scale = ICamera::GetInstance()->GetScale();

	float width = right - left;
	float height = bottom - top;
	D3DXVECTOR2 center = D3DXVECTOR2((width / 2) * scale, (height / 2) * scale);
	D3DXVECTOR3 origin(origin_x, origin_y, 0);
	D3DXVECTOR2 translate = D3DXVECTOR2(x, y);
	D3DXVECTOR2 scaling = D3DXVECTOR2(scale, scale);
	float angle = 0;
	SetRenderData(center, translate, scaling);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		&D3DXVECTOR2(0, 0),
		NULL,
		&scaling,
		NULL,
		angle,
		&translate
	);

	m_spriteHandler->SetTransform(&matrix);
	D3DXVECTOR3 Pos(0, 0, 0);
	m_spriteHandler->Draw(texture, &r, &origin, &Pos,
		D3DCOLOR_RGBA(255, 255, 255, opacity));
}

void IGraphic::SetRenderData(D3DXVECTOR2& center, D3DXVECTOR2& translate, D3DXVECTOR2& scaling)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);

	rgf::Vector position = ICamera::GetInstance()->GetPosition();
	int scale = ICamera::GetInstance()->GetScale();

	mt._11 = scale;
	mt._22 = scale;
	mt._33 = scale;
	mt._44 = scale;

	mt._41 = -position.x * scale;
	mt._42 = -position.y * scale;
	D3DXVECTOR4 curTranslate;
	D3DXVECTOR4 curCenter;

	D3DXVec2Transform(&curCenter, &D3DXVECTOR2(center.x, center.y), &mt);

	D3DXVec2Transform(&curTranslate, &D3DXVECTOR2(translate.x, translate.y), &mt);

	center.x = curCenter.x;
	center.y = curCenter.y;
	translate.x = curTranslate.x;
	translate.y = curTranslate.y;
}

void IGraphic::End()
{
	m_d3d->Release();
	m_spriteHandler->Release();
	m_backBuffer->Release();
	m_d3ddev->Release();
}
} //namespace rgf
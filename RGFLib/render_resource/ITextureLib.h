#pragma once
#include <unordered_map>
#include <memory>
#ifdef D3D9
#include <d3dx9.h>
#else // D3D9
#include <D3DX10.h>
#endif

#include "render/IGraphic.h"

namespace rgf
{
/// <summary>
/// [singleton] store textures
/// </summary>
class ITextureLib
{
protected:
	static std::shared_ptr<ITextureLib> m_instance;

#ifdef D3D9
	std::unordered_map<int, LPDIRECT3DTEXTURE9> m_textures;
#else
	std::unordered_map<int, ID3D10Texture2D*> m_textures;
#endif
public:
	static std::shared_ptr<ITextureLib> GetInstance();

#ifdef D3D9
	void Add(int id, LPCWSTR filePath);
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int id);
#else
	void Add( int id, LPCWSTR filePath );
	ID3D10Texture2D* Get( unsigned int id );
#endif
};

} //namespace rgf
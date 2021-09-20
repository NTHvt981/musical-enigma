#pragma once
#include <unordered_map>
#include <memory>
#include <d3dx9.h>

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

	std::unordered_map<int, LPDIRECT3DTEXTURE9> m_textures;
public:
	static std::shared_ptr<ITextureLib> GetInstance();

	void Add(int id, LPCWSTR filePath);
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int id);
};

} //namespace rgf
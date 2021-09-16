#include "ITextureLib.h"

namespace rgf
{
std::shared_ptr<ITextureLib> ITextureLib::m_instance = NULL;

std::shared_ptr<ITextureLib> ITextureLib::GetInstance()
{
	if (m_instance == NULL) m_instance = std::make_shared<ITextureLib>(ITextureLib());
	return m_instance;
}

void ITextureLib::Add(int id, LPCWSTR filePath)
{
	LPDIRECT3DTEXTURE9 texture = IGraphic::GetInstance()->LoadTexture(filePath);
	m_textures[id] = texture;
}

void ITextureLib::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	throw("Function not implement");
}

LPDIRECT3DTEXTURE9 ITextureLib::Get(unsigned int id)
{
	return m_textures[id];
}
} //namespace rgf
#pragma once
#include <unordered_map>
#include <memory>
#include <d3dx9.h>

#include "ISprite.h"

namespace rgf
{
/// <summary>
/// [singleton] store sprites
/// </summary>
class ISpriteLib
{
private:
	static std::shared_ptr<ISpriteLib> m_instance;

	std::unordered_map<int, LPSprite> m_sprites;
public:
	static std::shared_ptr<ISpriteLib> GetInstance();

	void Add(LPSprite sprite);
	void Add(int id, int l, int t, int r, int b,
		LPDIRECT3DTEXTURE9 tex, float origin_x = 0, float origin_y = 0);
	LPSprite Get(unsigned int id);
};

} //namespace rgf
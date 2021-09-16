#include "ISpriteLib.h"

namespace rgf
{
std::shared_ptr<ISpriteLib> ISpriteLib::m_instance = NULL;

std::shared_ptr<ISpriteLib> ISpriteLib::GetInstance()
{
	if (m_instance == NULL) m_instance = std::make_shared<ISpriteLib>(ISpriteLib());
	return m_instance;
}

void ISpriteLib::Add(LPSprite sprite)
{
	m_sprites[sprite->GetId()] = sprite;
}

void ISpriteLib::Add(int id, int l, int t, int r, int b, LPDIRECT3DTEXTURE9 tex, float origin_x, float origin_y)
{
	LPSprite spr = std::make_shared<ISprite>(ISprite(id, l, t, r, b, tex, origin_x, origin_y));
	Add(spr);
}

LPSprite ISpriteLib::Get(unsigned int id)
{
	return m_sprites[id];
}
} //namespace rgf
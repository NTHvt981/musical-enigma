#pragma once
#include "game/IGame.h"
#include "render/IGraphic.h"
#include "render_resource/ISpriteLib.h"
#include "render_resource/ITextureLib.h"
#include "Constants.h"
#include "entity_impl/CBlock.h"
#include "entity/IEntityLib.h"

class CGame :
    public rgf::IGame
{
private:
    std::shared_ptr<CBlock> m_redBlock;
    std::shared_ptr<CBlock> m_yellowBlock;
    std::shared_ptr<CBlock> m_greenBlock;
    std::shared_ptr<CBlock> m_blueBlock;
public:
    CGame( HWND hWnd, HINSTANCE hInstance );
    // Inherited via IGame
    virtual void DuringRender() override;

    // Inherited via IGame
    virtual void Update( DWORD dt ) override;

    // Inherited via IGame
    virtual void LoadResources() override;
    virtual void LoadTextures() override;
    virtual void LoadSprites() override;

    // Inherited via IGame
    virtual void Destroy() override;
};


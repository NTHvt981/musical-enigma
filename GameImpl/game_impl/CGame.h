#pragma once
#include "IGame.h"
#include "IGraphic.h"
#include "ISpriteLib.h"
#include "ITextureLib.h"
#include "Constants.h"
#include "CBlock.h"
#include <IEntityLib.h>

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
};


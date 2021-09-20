#pragma once
#include <memory>
#include "entity/IEntity.h"
#include "render_resource/ISprite.h"
#include "render_resource/ISpriteLib.h"
#include "Constants.h"

class CBlock :
    public rgf::IEntity
{
private:
    std::shared_ptr<rgf::ISprite> m_sprite = NULL;
    rgf::Vector m_velocity;
    rgf::Vector m_speed;
    int m_spriteId;
public:
    CBlock( int sprite_id, const rgf::IGameInfo& info, int id = -1 );
    // Inherited via IEntity
    virtual void Init() override;
    virtual void Update( DWORD dt ) override;
    virtual void Render() override;
    virtual void Destroy() override;
    virtual int GetRenderLevel() override;
    virtual void ProcessMessage( std::shared_ptr<rgf::IMessage> message ) override;

public:
    void SetVelocity( const rgf::Vector i_speed );
};


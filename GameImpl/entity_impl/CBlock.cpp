#include "CBlock.h"

CBlock::CBlock( int sprite_id, const rgf::IGameInfo& info, int id )
    :IEntity(info, id), m_spriteId(sprite_id)
{
    m_position = rgf::Vector( 0, 0 );
    m_velocity = rgf::Vector( m_speed.x, m_speed.y );
}

void CBlock::Init()
{
    m_sprite = rgf::ISpriteLib::GetInstance()->Get( m_spriteId );
    this->SetSizeSameAsSprite( m_sprite.get() );
}

void CBlock::Update( DWORD dt )
{
    this->Move( m_velocity );
    if (m_position.x <= 0)
    {
        m_position.x = 0;
        m_velocity.x = m_speed.x;
    }
    else if (m_position.x + m_size.x > m_gameInfo->m_windowClientWidth)
    {
        m_position.x = m_gameInfo->m_windowClientWidth - m_size.x;
        m_velocity.x = -m_speed.x;
    }

    if (m_position.y <= 0)
    {
        m_position.y = 0;
        m_velocity.y = m_speed.y;
    }
    else if (m_position.y + m_size.y > m_gameInfo->m_windowClientHeight)
    {
        m_position.y = m_gameInfo->m_windowClientHeight - m_size.y;
        m_velocity.y = -m_speed.y;
    }
}

void CBlock::Render()
{
    m_sprite->Draw( m_position );
}

void CBlock::Destroy()
{
}

int CBlock::GetRenderLevel()
{
    return 0;
}

void CBlock::ProcessMessage( std::shared_ptr<rgf::IMessage> message )
{
}

void CBlock::SetVelocity(const rgf::Vector i_speed )
{
    m_velocity.Set( i_speed.x, i_speed.y );
    m_speed.Set( i_speed.x, i_speed.y );
}

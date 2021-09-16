#include "IEntity.h"

namespace rgf
{
IEntity::IEntity( const IGameInfo& info, int id ):IGObject(info, id)
{
}
void IEntity::SetSizeSameAsAnimation()
{
	//TODO implement IEntity::SetSizeSameAsAnimation()
}
void IEntity::SetSizeSameAsSprite( ISprite* sprite )
{
	int x, y;
	sprite->GetSize( x, y );
	m_size.Set( x, y );
}
void IEntity::UpdatePhysicBox()
{
	m_physicBox.left = m_position.x;
	m_physicBox.top = m_position.y;
	m_physicBox.right = m_position.x + m_size.x;
	m_physicBox.bottom = m_position.y + m_size.y;
}
void IEntity::SetPosition( const Vector i_position )
{
	m_position.Set( i_position.x, i_position.y );
}
void IEntity::Move( const Vector velocity )
{
	m_position = m_position + velocity;
}
} //namespace rgf
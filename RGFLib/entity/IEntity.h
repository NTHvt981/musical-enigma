#pragma once

#include "game_object/IGObject.h"
#include "utils/Box.h"
#include "utils/Vector.h"
#include "render_resource/ISprite.h"
#include "game/IGameInfo.h"

namespace rgf
{
//TODO implement collision in entity
class IEntity: public IGObject
{
public:
	IEntity( const IGameInfo& info, int id = -1 );
protected:
	Vector m_position;
	Vector m_size;
	/// <summary>
	/// For rendering
	/// </summary>
	Vector m_origin;
	/// <summary>
	/// calculate from position and size
	/// </summary>
	Box<float> m_physicBox;

protected:
	void SetSizeSameAsAnimation();
	void SetSizeSameAsSprite(ISprite *i_sprite);
	void UpdatePhysicBox();

public:
	void SetPosition( const Vector i_position );
	void Move( const Vector i_velocity );
};
} //namespace rgf
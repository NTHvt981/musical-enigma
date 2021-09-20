#pragma once
#include <memory>
#include <unordered_map>

#include "IEntity.h"
#include "game_object/IGObjectLib.h"

namespace rgf
{
class IEntityLib
{
protected:
	IEntityLib();
	static std::shared_ptr<IEntityLib> m_instance;

public:
	static std::shared_ptr<IEntityLib> GetInstance();
	void Add( std::shared_ptr<IEntity> const i_obj );
	void Remove( const int id );
	const int GetNewId();
};
} //namespace rgf
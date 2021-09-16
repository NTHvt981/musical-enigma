#include "IEntityLib.h"

namespace rgf
{
std::shared_ptr<IEntityLib> IEntityLib::m_instance = std::make_shared<IEntityLib>( IEntityLib() );

IEntityLib::IEntityLib()
{
}

std::shared_ptr<IEntityLib> IEntityLib::GetInstance()
{
    return m_instance;
}

void IEntityLib::Add( std::shared_ptr<IEntity> const i_obj )
{
    IGObjectLib::GetInstance()->Add( i_obj );
}

void IEntityLib::Remove( const int id )
{
    IGObjectLib::GetInstance()->Remove( id );
}

const int IEntityLib::GetNewId()
{
    return 0;
}
} //namespace rgf
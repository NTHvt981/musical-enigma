#include "IGObjectLib.h"

namespace rgf
{
std::shared_ptr<IGObjectLib> IGObjectLib::m_instance = std::make_shared<IGObjectLib>( IGObjectLib() );

IGObjectLib::IGObjectLib()
{
	const int temp = MAX_RENDER_LEVEL;
	m_renderObjects = std::vector<std::list<std::shared_ptr<IGObject>>>();
	m_renderObjects.resize( temp );
}

std::shared_ptr<IGObjectLib> IGObjectLib::GetInstance()
{
	return m_instance;
}
void IGObjectLib::Add( std::shared_ptr<IGObject> const i_obj )
{
	m_gameObjects[i_obj->GetId()] = i_obj;
	m_renderObjects[i_obj->GetRenderLevel()].push_back(i_obj);
}
void IGObjectLib::Remove( const int id )
{
	m_renderObjects[m_gameObjects[id]->GetRenderLevel()].remove( m_gameObjects[id] );
	m_gameObjects[id] = NULL;
}
const int IGObjectLib::GetNewId()
{
	m_countId++;
	return m_countId;
}
}//namespace rgf
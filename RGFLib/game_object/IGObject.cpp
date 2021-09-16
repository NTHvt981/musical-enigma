#include "IGObject.h"

namespace rgf
{
IGObject::IGObject( const IGameInfo& info, int id ): m_id(id), m_gameInfo(&info)
{
	if (id == -1)
	{
		throw("Please provide a legit id");
	}
}
void IGObject::UpdateEpilogue()
{
	ProcessMessages();
}
void IGObject::ProcessMessages()
{
	while (!m_messages.empty())
	{
		ProcessMessage( m_messages.front() );
		m_messages.pop();
	}
}
} //namespace rgf
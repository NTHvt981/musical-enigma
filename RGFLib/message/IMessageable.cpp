#include "IMessageable.h"
namespace rgf
{
void rgf::IMessageable::ProcessMessages()
{
	while (!m_messages.empty())
	{
		
	}
}

void IMessageable::ReceiveMessage( std::shared_ptr<rgf::IMessage> message )
{
	m_messages.push( message );
}
} // namespace rgf

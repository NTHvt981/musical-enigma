#pragma once
#include <queue>
#include "IMessage.h"

namespace rgf
{
class IMessageable
{
protected:
	std::queue<std::shared_ptr<rgf::IMessage>> m_messages = std::queue<std::shared_ptr<rgf::IMessage>>();

	virtual void ProcessMessages();
	virtual void ProcessMessage( std::shared_ptr<rgf::IMessage> message ) = 0;
	void SendMessage( const IMessageable* i_otherMesssageable, std::shared_ptr<rgf::IMessage> message ) const;

public:
	void ReceiveMessage( std::shared_ptr<IMessage> message );
};
} // namespace rgf


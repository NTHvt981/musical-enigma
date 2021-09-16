#pragma once
#include <memory>

#include "IData.h"

namespace rgf
{
class IGObject;	//don't include "IGObject.h"
enum EMessageTypes: int;

struct IMessage
{
	EMessageTypes m_type;
	LPData m_data;
	std::shared_ptr<IGObject> m_sender;
};

enum EMessageTypes
{
	Null,
	Num
};
} //namespace rgf
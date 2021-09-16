#pragma once
#include <memory>

namespace rgf
{
struct IData
{

};

struct DataInt: IData
{
	int Param;
};

typedef std::shared_ptr<IData> LPData;
} //namespace rgf
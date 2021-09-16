#pragma once
#include <memory>
#include <unordered_map>
#include <map>
#include <vector>

#include "IGObject.h"
#include "RgfConstants.h"

namespace rgf
{
/// <summary>
/// [singleton] manage game objects, add and get through id (int)
/// should only be include and access in game class
/// </summary>
class IGObjectLib
{
protected:
	IGObjectLib();
	static std::shared_ptr<IGObjectLib> m_instance;
	int m_countId = 0;
	std::unordered_map<int, std::shared_ptr<IGObject>> m_gameObjects = 
		std::unordered_map<int, std::shared_ptr<IGObject>>();
	std::vector<std::list<std::shared_ptr<IGObject>>> m_renderObjects;
	
public:
	static std::shared_ptr<IGObjectLib> GetInstance();
	void Add( std::shared_ptr<IGObject> const i_obj );
	void Remove(const int id);
	const int GetNewId();
};
}//namespace rgf

#pragma once
#include <d3dx9.h>
#include <memory>

#include "utils/Vector.h"
#include "utils/Box.h"

namespace rgf
{
/// <summary>
/// [singleton] rerender the game through camera lens of view
/// </summary>
class ICamera
{
protected:
	rgf::Vector m_position = rgf::Vector(0, 0);
	float m_width;
	float m_height;
	float m_scale;
	bool m_isOn;
	D3DXMATRIX m_matrix;

	/*	y
	  x o---------------------------o
		|				 |			|
		|	o-----------o|//inner.b	|
		|	|innerBound	||			|	outerBound
		|	o-----------ov			|
		|<-------------->			|
		|	//inner.r				|
		o---------------------------o
	*/

	//limit of camera position to the game world
	rgf::Box<float> m_outerBound;
	//limit of player position relative to camera rect
	rgf::Box<float> m_innerBound;

	static std::shared_ptr<ICamera> m_instance;
public:
	static std::shared_ptr<ICamera> GetInstance();
	static void SetInstance(ICamera& camera);
	static void SetInstance(std::shared_ptr<ICamera> camera);

	static D3DXMATRIX MirrorHorizontal(D3DXVECTOR3& vector);

	ICamera(float w, float h, float s = 1);

	void SetMatrix();
	void Transform(float x, float y, D3DXVECTOR3& new_pos);

	//these function should be called in game class rather than player class
	void Follow(float x, float y);
	void Follow(rgf::Vector pos);

	void FollowWithTransition(float x, float y);
	void FollowWithTransition(rgf::Vector pos);

	void FollowWithoutBound(float x, float y);

	void Move(float vx, float vy);

	rgf::Vector GetPosition();
	void GetLTRB(float& l, float& t, float& r, float& b);

	float GetScale();
	bool IsOn();
	void TurnOn();
	void TurnOff();

	void SetOuterBound(float l, float t, float r, float b);
	void GetOuterBound(float& l, float& t, float& r, float& b);
};

} //namespace rgf
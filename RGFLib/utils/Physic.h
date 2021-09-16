#pragma once
#include <limits>
#include <utility>

#include "Box.h"
#include "Vector.h"

namespace rgf
{
//vital functions for class entity to use
void SweptAABB(
	const float move_left, const float move_top, const float move_right, const float move_bottom,
	const float move_velocity_x, const float move_velocity_y,
	const float static_left, const float static_top, const float static_right, const float static_bottom,
	float& collide_time, float& normal_x, float& normal_y	
	//vector normal_x va normal_y vuong goc voi be mat xay ra va cham
);
void SweptAABB(
	const Box<float> i_moveObj,
	const Vector i_velocity,
	const Box<float> i_staticObj,
	float& o_collideTime, Vector &o_normal
);

void GetSweptBroadphaseBox(
	const float move_left, const float move_top, const float move_right, const float move_bottom,
	const float move_velocity_x, const float move_velocity_y,
	float& target_left, float& target_top, float& target_right, float& target_bottom
);
void GetSweptBroadphaseBox( const Box<float> i_moveObj,
							const Vector i_velocity, 
							Box<float> &o_result);

/// <returns>true is there is collision between to rectangle</returns>
bool AABBCheck(
	//left -> top -> right -> bottom
	const float left_1, const float top_1, const float right_1, const float bottom_1,
	const float left_2, const float top_2, const float right_2, const float bottom_2 );
bool AABBCheck(const Box<float> i_obj1, const Box<float> i_obj2);

//TODO implement Deflect later
void Deflect(
	const float old_x, const float old_y,
	float& new_x, float& new_y,
	const float velocity_x, const float velocity_y,
	const float collide_time, const float normal_x, const float normal_y
);

//TODO implement Push later
void Push(
	const float old_x, const float old_y,
	float& new_x, float& new_y,
	const float velocity_x, const float velocity_y,
	const float collide_time, const float normal_x, const float normal_y
);
void Slide(
	const float old_x, const float old_y,
	float& new_x, float& new_y,
	const float velocity_x, const float velocity_y,
	const float collide_time, const float normal_x, const float normal_y
);
} //namespace rgf


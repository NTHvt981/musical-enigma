#include "Physic.h"

void rgf::SweptAABB( 
	const float move_left, const float move_top, const float move_right, const float move_bottom, 
	const float move_velocity_x, const float move_velocity_y, 
	const float static_left, const float static_top, const float static_right, const float static_bottom, 
	float& collide_time, float& normal_x, float& normal_y )
{
	float entry_x, entry_y;
	float exit_x, exit_y;
	/*
	what is entry and exit, look at this
  move_l		 move_r	   static_l			static_r
	|	  move		|			|	 static		|
					<---entry--->
	<-------------------exit-------------------->
	this illustrate the horizontal axis
	the same can be said for the vertical axis
	*/

	if (move_velocity_x > 0.0f)
	{
		entry_x = static_left - move_right;
		exit_x = static_right - move_left;
	}
	else
	{
		entry_x = static_right - move_left;
		exit_x = static_left - move_right;
	}

	if (move_velocity_y > 0.0f)
	{
		entry_y = static_top - move_bottom;
		exit_y = static_bottom - move_top;
	}
	else
	{
		entry_y = static_bottom - move_top;
		exit_y = static_top - move_bottom;
	}

	// find time of collision and time of leaving for
	// each axis(if statement is to prevent divide by zero)
	float entry_time_x, entry_time_y;
	float exit_time_x, exit_time_y;

	//we will devide entry position to velocity to get the entry time
	//for x entry_x / velocity_x
	//what if velocity == 0 ? asign entry time to infinity
	//the same goes for exit time, exit position
	if (move_velocity_x == 0.0f)
	{
		entry_time_x = -std::numeric_limits<float>::infinity();
		exit_time_x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_x = entry_x / move_velocity_x;
		exit_time_x = exit_x / move_velocity_x;
	}

	if (move_velocity_y == 0.0f)
	{
		entry_time_y = -std::numeric_limits<float>::infinity();
		exit_time_y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entry_time_y = entry_y / move_velocity_y;
		exit_time_y = exit_y / move_velocity_y;
	}

	float entry_time = std::max( entry_time_x, entry_time_y );
	float exit_time = std::min( exit_time_x, exit_time_y );

	// if there was no collision
	if (entry_time > exit_time ||
		 entry_time_x < 0.0f && entry_time_y < 0.0f ||
		 entry_time_x > 1.0f || entry_time_y > 1.0f)
		//collide time return 0 -> no collision
	{
		normal_x = 0.0f;
		normal_y = 0.0f;
		collide_time = 1.0f;
	}
	else //I dont understand these line
	{
		if (entry_time_x > entry_time_y)
		{
			if (entry_x < 0.0f)
			{
				normal_x = 1.0f;
				normal_y = 0.0f;
			}
			else
			{
				normal_x = -1.0f;
				normal_y = 0.0f;
			}
		}
		else
		{
			if (entry_y < 0.0f)
			{
				normal_x = 0.0f;
				normal_y = 1.0f;
			}
			else
			{
				normal_x = 0.0f;
				normal_y = -1.0f;
			}
		}
		collide_time = entry_time;
	}
}

void rgf::SweptAABB( const Box<float> i_moveObj, 
					 const Vector i_velocity, 
					 const Box<float> i_staticObj, 
					 float& o_collideTime, 
					 Vector& o_normal )
{
	rgf::SweptAABB( i_moveObj.left, i_moveObj.top, i_moveObj.right, i_moveObj.bottom,
					i_velocity.x, i_velocity.y,
					i_staticObj.left, i_staticObj.top, i_staticObj.right, i_staticObj.bottom,
					o_collideTime, o_normal.x, o_normal.y );
}

void rgf::GetSweptBroadphaseBox(
	const float move_left, const float move_top, const float move_right, const float move_bottom, 
	const float move_velocity_x, const float move_velocity_y, 
	float& target_left, float& target_top, float& target_right, float& target_bottom )
{
	if (move_velocity_x > 0)
	{
		target_left = move_left;
		target_right = move_right + move_velocity_x;
	}
	else
	{
		target_left = move_left + move_velocity_x;
		target_right = move_right;
	}

	if (move_velocity_y > 0)
	{
		target_top = move_top;
		target_bottom = move_bottom + move_velocity_y;
	}
	else
	{
		target_top = move_top + move_velocity_y;
		target_bottom = move_bottom;
	}
}

void rgf::GetSweptBroadphaseBox( const Box<float> i_moveObj, 
								 const Vector i_velocity,
								 Box<float>& o_result )
{
	rgf::GetSweptBroadphaseBox( i_moveObj.left, i_moveObj.top, i_moveObj.right, i_moveObj.bottom,
								i_velocity.x, i_velocity.y,
								o_result.left, o_result.top, o_result.right, o_result.bottom );
}

bool rgf::AABBCheck(
		const float left_1, const float top_1, const float right_1, const float bottom_1, 
		const float left_2, const float top_2, const float right_2, const float bottom_2 )
{
	return !(
		right_1 <= left_2 ||
		right_2 <= left_1 ||
		bottom_1 <= top_2 ||
		bottom_2 <= top_1);
}

bool rgf::AABBCheck( const Box<float> i_obj1, const Box<float> i_obj2 )
{
	return rgf::AABBCheck( i_obj1.left, i_obj1.top, i_obj1.right, i_obj1.bottom,
						   i_obj2.left, i_obj2.top, i_obj2.right, i_obj2.bottom );
}

void rgf::Slide( const float old_x, const float old_y, 
				 float& new_x, float& new_y, 
				 const float velocity_x, const float velocity_y, 
				 const float collide_time, const float normal_x, const float normal_y )
{
	//the ideal is that we calculate the new position while keeping the old one
	new_x = old_x;
	new_y = old_y;

	new_x += velocity_x * collide_time;
	new_y += velocity_y * collide_time;

	float remaining_time = 1 - collide_time;

	//NOTE v_x * normal_y NOT v_x * normal_x
	float dotprod = (velocity_x * normal_y + velocity_y * normal_x) * remaining_time;

	float new_velocity_x = dotprod * normal_y;
	float new_velocity_y = dotprod * normal_x;

	//update position
	new_x += new_velocity_x;
	new_y += new_velocity_y;
}

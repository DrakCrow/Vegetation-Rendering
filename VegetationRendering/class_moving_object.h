#pragma once
#include "time.h"
#include "glm/glm.hpp"
#define init_Zom_velocity 1.0
#define init_human_velocity 10
#define Critical_distance 5  //The parameter to adjust Zombie's behavior
#define init_bullet_velocity 500
#define init_arrow_velocity 20
#define frame 10
int count = 0;//帧数

class moving_object {
private:
	int flag;
	float velocity;
	glm::vec3 direction;
	glm::vec3 place;
public:
	int get_flag() { return flag; }
	float get_velocity() { return velocity; }
	glm::vec3 get_place() { return place; }
	glm::vec3 get_Vector() { return direction; }

	void set_Vector(glm::vec3 v) { direction = v; }
	void set_position(glm::vec3 p) { place = p; }/**************重点标记，位置还没定*************/
	void set_flag(int a) { flag = a; }
	void set_velocity(float b) { velocity = b; }
	void decrease_flag() { flag--; }
	glm::vec3 get_direction(glm::vec3 v) { return place - v; }
	void update_position(float deltatime);				//update the position
};
class Zombie :public moving_object {
private:
	//arrow a;
public:
	Zombie() {
		set_flag(50);
		set_velocity(init_Zom_velocity);
	}
	//void update_zombie() {
	//	update_position();
	//	/*if (a.get_flag() != 0)
	//		a.update_position();*/
	//	/*if (count >= frame)
	//	{
	//	count == 0;
	//	if (a.get_flag() == 0)
	//	rand_new_arrow();
	//	}*/
	//}
	void update_Vector(glm::vec3 human_pos);//update the directions
	//void rand_new_arrow();
};
class bullet :public moving_object {							/**********************warning, direction and position have to be set at first**************************/
public:
	bullet() {
		set_flag(1);
		set_velocity(init_bullet_velocity);
	}
};
class arrow :public moving_object {
public:
	arrow() {
		set_flag(0);
		set_velocity(init_arrow_velocity);
	}
	//void init_glm::vec3(position human_pos);
};
class Human :public moving_object {
public:
	Human() {
		set_flag(3);
		set_velocity(init_human_velocity);
	}
};
void moving_object::update_position(float deltatime)
{
	place.x += velocity * direction.x * deltatime;
	place.z += velocity * direction.z * deltatime;
}
void Zombie::update_Vector(glm::vec3 human_pos)
{
	glm::vec3 dir;
	glm::vec3 turbu_dir;
	glm::vec3 v;
	srand((unsigned)time(NULL));
	//只定义x_y方向速度
	dir.x = human_pos.x - get_place().x;
	dir.z = human_pos.z - get_place().z;

	float temp = sqrt(dir.x * dir.x + dir.z * dir.z);
	dir.y = 0;
	turbu_dir.x = rand() % (abs((int)dir.x) + 1);
	turbu_dir.z = rand() % (abs((int)dir.z) + 1);
	turbu_dir.y = 0;

	dir.x = dir.x * Critical_distance / temp + turbu_dir.x;
	dir.z = dir.z * Critical_distance / temp + turbu_dir.z;
	temp = sqrt(dir.x * dir.x + dir.z * dir.z);
	v.x = dir.x / temp;
	v.z = dir.z / temp;
	set_Vector(v);
}

//void Zombie::rand_new_arrow()
//{
//	srand((unsigned)time(NULL));
//	if (rand() % 5 == 0)
//	{
//		a.set_flag(1);
//		a.set_position(get_place());
//		a.set_Vector(get_Vector());
//	}
//}
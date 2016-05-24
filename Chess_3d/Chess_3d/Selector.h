#pragma once
#include "Utils.h"

class Selector
{
	utils *s_util;
	IVolumeLightSceneNode *s_node;
public:
	Selector(utils *s_util,SColor color);
	void change_pos(vector3df new_pos);
	vector3df get_pos();
	void remove();
	~Selector();
};


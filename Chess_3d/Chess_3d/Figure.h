#pragma once
#include "Utils.h"
class Figure : public obj_3d
{
	utils *g_util;
	obj_3d *obj;
public:
	Figure(utils *g_util_);
	vector3df get_pos();
	~Figure();
};


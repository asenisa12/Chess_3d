#pragma once
#include "Utils.h"
class Figure : public obj_3d
{
	utils *g_util;
	obj_3d *obj;
	bool color;
public:
	Figure(utils *g_util_, bool color_);
	vector3df get_pos();
	bool get_color();
	virtual std::vector<vector3df> get_availableMoves(
		std::vector<Figure*> otherFigs) 
	{
		std::vector<vector3df> aa;
		return aa;
	};
	~Figure();
};


#pragma once
#include "Utils.h"
class Figure : public obj_3d
{
	utils *g_util;
	bool color;
protected:
	static const int MOVE = 2;
	int delim;
public:
	Figure(utils *g_util_, bool color_);
	vector3df get_pos();
	bool get_color();
	virtual std::vector<vector3df> get_availableMoves(
		std::vector<Figure*> otherFigs) = 0;
	~Figure();
};


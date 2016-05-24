#pragma once
#include "Figure.h"

class Pawn: public Figure
{
public:
	Pawn(utils *g_utils_, bool color, vector3df pos);
	std::vector<vector3df> get_availableMoves(
		std::vector<Figure*> otherFigs);
};


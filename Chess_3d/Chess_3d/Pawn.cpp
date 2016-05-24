#include "Pawn.h"



Pawn::Pawn(utils *g_utils_, bool color, vector3df pos)
	:Figure(g_utils_,color)
{
	set_pos(pos);
}

std::vector<vector3df> Pawn::get_availableMoves(
	std::vector<Figure*> otherFigs)
{
	std::vector<vector3df> positions;
	vector3df currentPos = node->getPosition();
	currentPos.Z += 2*SCALE;
	positions.push_back(currentPos);
	return positions;
}


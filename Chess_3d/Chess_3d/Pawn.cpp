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
	vector3df otherPos = node->getPosition();
	positions.push_back(otherPos);
	otherPos.Z += delim*MOVE*SCALE;
	positions.push_back(otherPos);
	
	for (auto fig : otherFigs)
	{
		if (fig->get_color() != get_color())
		{
			if (fig->get_pos().Z == otherPos.Z)
			{
				if (fig->get_pos().X == otherPos.X + delim*MOVE*SCALE ||
					fig->get_pos().X == otherPos.X - delim*MOVE*SCALE)
					positions.push_back(fig->get_pos());
			}
		}
	}
	return positions;
}


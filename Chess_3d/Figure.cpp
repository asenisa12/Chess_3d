#include "Figure.h"



Figure::Figure(utils *g_util_)
	:g_util(g_util_),obj_3d("resources/pawn.obj", "lightFalloff.png", SCALE/2, g_util_)
{
}

vector3df Figure::get_pos()
{
	return node->getPosition();
}

Figure::~Figure()
{
}

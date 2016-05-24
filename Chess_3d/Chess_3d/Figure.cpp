#include "Figure.h"



Figure::Figure(utils *g_util_, bool color_)
	:g_util(g_util_), obj_3d("resources/pawn.obj", SCALE / 1.5, g_util_), color(color_)
{
	if (color == SIDE::WHITE)set_texture("resources/white.bmp", g_util->driver);
		else set_texture("resources/black.bmp", g_util->driver);
}

vector3df Figure::get_pos()
{
	return node->getPosition();
}

bool Figure::get_color()
{
	return color;
}

Figure::~Figure()
{
}

#include "Board.h"

Selector *Board::selector=NULL;
utils *Board::g_util = NULL;
std::vector<Figure*> Board::figures;

Board::Board(utils *g_util_)
{
	g_util=g_util_;
	obj = new obj_3d("resources/board.obj", 
		"lightFalloff.png", SCALE, g_util_);

	selector = new Selector(g_util_, SColor(0, 0, 255, 255));
	selector->change_pos(vector3df(-7*5,0,-7*5));
	figures.push_back(new Figure(g_util_));
	figures.front()->set_pos(vector3df(7*5,0*5,-7*5));
}

void Board::update()
{
	sel_move.read_keys();
}

Board::~Board()
{
	delete selector;
	delete obj;
}

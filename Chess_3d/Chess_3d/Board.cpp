#include "Board.h"

Selector *Board::selector=NULL;
utils *Board::g_util = NULL;
std::vector<Figure*> Board::figures;

Board::Board(utils *g_util_)
{
	g_util=g_util_;
	obj = new obj_3d("resources/board.obj", SCALE, g_util_);

	selector = new Selector(g_util_, SColor(0, 0, 255, 255));
	selector->change_pos(vector3df(-7*5,0,-7*5));
	figures.push_back(new Pawn(g_util_, SIDE::BLACK, vector3df(7 * 5, 0 * 5, -7 * 5)));
}

bool Board::sel_handler::on_availablePos()
{
	if (sel_fig != NULL)
	{
		auto moves = sel_fig->get_availableMoves(figures);
		vector3df selpos = selector->get_pos();
		printf("%f %f %f \n", selpos.X, selpos.Y, selpos.Z);
		for (auto pos : moves)
			if (pos == selpos) return true;
	}
	return false;
}

void Board::sel_handler::read_keys()
{
	vector3df selpos = selector->get_pos();
	if (g_util->erec->IsKeyUp(irr::KEY_KEY_W))
		selpos.Z += MOVE*SCALE;
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_S))
		selpos.Z -= MOVE*SCALE;
	if (g_util->erec->IsKeyUp(irr::KEY_KEY_A))
		selpos.X -= MOVE*SCALE;
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_D))
		selpos.X += MOVE*SCALE;

	selector->change_pos(selpos);


	if (!selected)
		for (auto fig : figures)
		{
			if (fig->get_pos() == selector->get_pos() &&
				g_util->erec->IsKeyUp(irr::KEY_KEY_P))
			{
				printf("log: figure selected\n");
				sel_fig = fig;
				selected = true;
			}
		}
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_O) && on_availablePos())
	{
			printf("log: figure placed\n");
			sel_fig->set_pos(selpos);
			unselect();
		
	}


	g_util->erec->clear();
}


void Board::update()
{
	sel_handle.read_keys();
}

Board::~Board()
{
	delete selector;
	delete obj;
}

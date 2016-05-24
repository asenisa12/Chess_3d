#include "Board.h"

Selector *Board::selector=NULL;
utils *Board::g_util = NULL;
std::vector<Figure*> Board::figures;
ICameraSceneNode *Board::camera = NULL;
bool Board::playerOnMove=SIDE::WHITE;

Board::Board(utils *g_util_)
{
	g_util=g_util_;
	obj = new obj_3d("resources/board.obj", SCALE, g_util_);

	selector = new Selector(g_util_, SColor(0, 0, 100, 255));
	selector->change_pos(vector3df(-7*5,0,-7*5));
	for (int i = 0; i < 8; i++)
	{
		figures.push_back(new Pawn(g_util_, SIDE::WHITE, vector3df((7 - i * 2) * 5, 0 * 5, -7 * 5)));
		figures.push_back(new Pawn(g_util_, SIDE::BLACK, vector3df((7 - i * 2) * 5, 0 * 5, 7 * 5)));

	}

	camera = g_util->smgr->addCameraSceneNode();

	camera->setPosition(vector3df(0, 40, -80));
	camera->setTarget(vector3df(0, 5, 0));
}

bool Board::sel_handler::on_availablePos()
{
	if (sel_fig != NULL)
	{
		auto moves = sel_fig->get_availableMoves(figures);
		for (auto pos : moves)
			if (pos == selector->get_pos()) return true;
	}
	return false;
}

void Board::sel_handler::add_lights()
{
	if (sel_fig != NULL)
	{
		auto moves = sel_fig->get_availableMoves(figures);
		for (auto pos : moves)
		{
			sel_lights.push_back(new Selector(g_util, SColor(255, 255, 0, 0)));
			sel_lights.back()->change_pos(pos);
		}
	}
}

void Board::sel_handler::take_figure(vector3df pos)
{
	for (size_t i = 0; i < figures.size(); i++)
	{
		if (figures[i]->get_pos() == pos)
		{
			figures[i]->remove();
			figures.erase(figures.begin()+i);
			return;
		}
	}
}

void Board::sel_handler::switch_sides()
{
	vector3df campos = camera->getPosition();
	campos.Z *= -1;
	camera->setPosition(campos);

	if (playerOnMove == SIDE::BLACK) playerOnMove = SIDE::WHITE;
	else playerOnMove = SIDE::BLACK;
}

void Board::sel_handler::read_keys()
{
	vector3df selpos = selector->get_pos();
	int move = MOVE*SCALE*camera->getPosition().Z / -80;
	if (g_util->erec->IsKeyUp(irr::KEY_KEY_W))
		selpos.Z += move;
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_S))
		selpos.Z -= move;
	if (g_util->erec->IsKeyUp(irr::KEY_KEY_A))
		selpos.X -= move;
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_D))
		selpos.X += move;

	selector->change_pos(selpos);

	if (!selected)
		for (auto fig : figures)
		{
			if (fig->get_pos() == selector->get_pos() &&
				g_util->erec->IsKeyUp(irr::KEY_KEY_P) && playerOnMove == fig->get_color())
			{
				printf("log: figure selected\n");
				sel_fig = fig;
				selected = true;
				add_lights();
			}
		}
	else if (g_util->erec->IsKeyUp(irr::KEY_KEY_O) && on_availablePos())
	{
			printf("log: figure placed\n");
			if (selpos != sel_fig->get_pos())
			{
				take_figure(selpos);
				switch_sides();
				sel_fig->set_pos(selpos);
			}

			unselect();
			for (auto light : sel_lights)
				light->remove();
			sel_lights.clear();

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

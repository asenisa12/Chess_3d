#pragma once
#include "Utils.h"
#include "Figure.h"
#include "Selector.h"

class Board
{
	static const int MOVE = 1;
	static Selector *selector;
	static utils *g_util;
	static std::vector<Figure*> figures;
	obj_3d *obj;
	class sel_mover
	{
		bool selected;
		Figure *sel_fig;
	public: 
		sel_mover() 
		{
			sel_fig = NULL;
			selected = false;
		}
		void read_keys()
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
						g_util->erec->IsKeyUp(irr::KEY_KEY_O))
					{
						printf("Ludnica\n");
						sel_fig = fig;
						selected = true;
					}
				}
			else if (sel_fig->get_pos() != selector->get_pos() &&
				g_util->erec->IsKeyUp(irr::KEY_KEY_O))
			{
				sel_fig->set_pos(selpos);
				sel_fig = NULL;
				selected = false;
			}
			g_util->erec->clear();
		}
	}sel_move;
public:

	void update();
	Board(utils *g_util_);
	~Board();
};


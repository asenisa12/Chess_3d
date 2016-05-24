#pragma once
#include "Utils.h"
#include "Figure.h"
#include "Pawn.h"
#include "Selector.h"

extern bool playerOnMove;

class Board
{
	static const int MOVE = 1;
	static Selector *selector;
	static utils *g_util;
	static std::vector<Figure*> figures;
	obj_3d *obj;
	class sel_handler
	{
		bool selected;
		Figure *sel_fig;
		bool on_availablePos();
		void unselect()
		{
			printf("log: figure unselected\n");
			sel_fig = NULL;
			selected = false;
		}
	public: 
		sel_handler() 
		{
			unselect();
		}
		void read_keys();
	}sel_handle;
public:

	void update();
	Board(utils *g_util_);
	~Board();
};


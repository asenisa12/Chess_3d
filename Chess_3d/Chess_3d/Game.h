#pragma once
#include "Utils.h"
#include "Figure.h"
#include "Board.h"


class Game
{
private:
	EventReceiver *receiver;
	IrrlichtDevice *device;
	utils *g_util;
public:
	Game();
	void run();
	~Game();
};


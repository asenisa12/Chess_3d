#include "Game.h"



Game::Game()
{
	receiver = new EventReceiver();
	device = createDevice(EDT_OPENGL, dimension2d<u32>(1024, 720), 16,
		false, false, false, receiver);
	device->setWindowCaption(L"Chess");
	g_util = new utils(device, receiver);
	
}

Game::~Game()
{
	device->drop();
	delete receiver;
}

void Game::run()
{
	Board b(g_util);
	

	while (device->run())
	{
		if (device->isWindowActive())
		{
			b.update();
			g_util->driver->beginScene(true, true, SColor(100, 100, 100, 255));
			g_util->smgr->drawAll();
			g_util->driver->endScene();
		}
		else device->yield();
	}

}

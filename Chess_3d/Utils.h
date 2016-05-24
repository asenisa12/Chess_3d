#pragma once

#include <vector>
#include <irrlicht.h>
#include <string>


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

const int SCALE = 5;

enum SIDE {BLACK=0,WHITE=1};

class EventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		bool prevState;

		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			prevState = KeyIsDown[event.KeyInput.Key];
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.Key;
			if (prevState && !KeyIsDown[event.KeyInput.Key]);
			KeyIsUP[event.KeyInput.Key] = true;
		}

		return false;
	}

	virtual bool IsKeyUp(EKEY_CODE keyCode)
	{
		bool state = KeyIsUP[keyCode];
		KeyIsUP[keyCode] = false;
		return state;
	}
	virtual bool IsKeyDown(EKEY_CODE keyCode)
	{
		return KeyIsDown[keyCode];
	}

	EventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		{
			KeyIsDown[i] = false;
			KeyIsUP[i] = false;
		}
			
	}
	void clear()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsUP[i] = false;
	}

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool KeyIsUP[KEY_KEY_CODES_COUNT];
};

struct utils
{
	IrrlichtDevice *device;
	IVideoDriver *driver;
	ISceneManager *smgr;
	IGUIEnvironment *guienv;
	EventReceiver *erec;

	utils(IrrlichtDevice *device_, EventReceiver *rcv) :device(device_)
	{
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		guienv = device->getGUIEnvironment();
		erec = rcv;
	}

	utils(utils &other)
	{
		device= other.device;
		driver = other.driver;
		smgr = other.smgr;
		guienv = other.guienv;
	}
};

class obj_3d
{
protected:
	IAnimatedMesh *mesh;
	IAnimatedMeshSceneNode *node;
public:
	obj_3d(std::string meshpath, int scale, utils *util)
	{
		mesh = util->smgr->getMesh(meshpath.c_str());
		node = util->smgr->addAnimatedMeshSceneNode(mesh);
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(EMAT_STAND);
		}
		node->setScale(vector3df(scale, scale, scale));
	}
	void set_pos(vector3df new_pos) {
		node->setPosition(new_pos);
	}
	void set_texture(char *text_path, IVideoDriver *driver)
	{
		if(node)
			node->setMaterialTexture(0, driver->getTexture(text_path));
	}
};


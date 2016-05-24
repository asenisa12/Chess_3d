#include "Selector.h"



Selector::Selector(utils *s_util_, SColor color)
	:s_util(s_util_)
{
	s_node = s_util_->smgr->addVolumeLightSceneNode(
		0,-1,32,32,color,SColor(0,0,0,0));

	if (s_node)
	{
		s_node->setScale(core::vector3df(15.0f, 15.0f, 15.0f));
		core::array<video::ITexture*> textures;
		for (s32 g = 7; g > 0; --g)
		{
			core::stringc tmp;
			tmp = "resources/portal";
			tmp += g;
			tmp += ".bmp";
			video::ITexture* t = s_util->driver->getTexture(tmp.c_str());
			textures.push_back(t);
		}
		scene::ISceneNodeAnimator* glow = s_util->smgr->createTextureAnimator(textures, 150);
		s_node->addAnimator(glow);
		glow->drop();
	}
}


void Selector::change_pos(vector3df new_pos)
{
	s_node->setPosition(new_pos);
}

vector3df Selector::get_pos()
{
	return s_node->getPosition();
}

void Selector::remove()
{
	s_node->drop();
}
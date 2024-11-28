#include"maptry.h"


bool Maptest::init()
{
	if(!Scene::init())return false;
	l1 = Maplayer::create();
	this->addChild(l1);
	return true;
}


void Maplayer::setMap(int i) {
	for (int j = 0;j < 8;j++) {
		maps[j]->setVisible(false);
	}
	maps[i]->setVisible(true);
}
bool Maplayer::init() {
	if (!Layer::init())	return false;
	maps[0] = Sprite::create("mapresource/farm_ground.png");
	maps[1] = Sprite::create("mapresource/farm_ground_winter.png");
	maps[2] = Sprite::create("mapresource/farm_ground_nowater.png");
	maps[3] = Sprite::create("mapresource/froest.png");
	maps[4] = Sprite::create("mapresource/mine.png");
	maps[5] = Sprite::create("mapresource/sea.png");
	maps[6] = Sprite::create("mapresource/village_ground.png");
	maps[7] = Sprite::create("mapresource/village_ground_winter.png");
	for (int i = 0;i < 8;i++) {
		maps[i]->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
		this->addChild(maps[i]);
	}
	setMap(VILLAGE);
	return true;
}

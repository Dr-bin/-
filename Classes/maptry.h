#pragma once
#include"cocos2d.h"

USING_NS_CC;
const int FARM = 0;
const int FARM_WINTER = 1;
const int FARM_NOWATER = 2;
const int FROEST = 3;
const int MINE = 4;
const int SEA = 5;
const int VILLAGE = 6;
const int VILLAGE_WINTER = 7;
class Maplayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Maplayer);
	Sprite* maps[8];
	//使用setMap设置当前地图，参数见const int 表。
	void setMap(int i);
};
class Maptest :public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(Maptest);
	Maplayer* l1;
};

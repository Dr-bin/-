#pragma once
#include"cocos2d.h"
#include"Plantsandmineral.h"
#include"CharacterAnimation.h"
USING_NS_CC;
const int FARM = 0;
const int FARM_WINTER = 1;
const int FARM_NOWATER = 2;
const int FROEST = 3;
const int MINE = 4;
const int SEA = 5;
const int VILLAGE = 6;
const int VILLAGE_WINTER = 7;
const int winter = 1;

//房子
class House : public Node {
public:
	virtual bool init();
	CREATE_FUNC(House);
	Sprite* house;
};
// 地图节点类，定义了基本的地图节点属性和方法
class MapNode :public Node
{
public:
	virtual bool init();
	CREATE_FUNC(MapNode);
	Sprite* ground;
	int need_rand = 1;
	
};

// 农场地图类，继承自地图节点，增加了季节变化和植物数组的属性
class FarmMap :public MapNode
{
public:
	virtual bool init();
	CREATE_FUNC(FarmMap);
	Plant* tree[15];
	int plantpos[15][2];
	void changeSeason(int season);
	int nowSeason = 0;
	House* house;
private:
	Texture2D* winter;
	Texture2D* nowater;
};

// 森林地图类，继承自地图节点，包含植物数组
class ForestMap :public MapNode
{
public:
	virtual bool init();
	CREATE_FUNC(ForestMap);
	Plant* tree[30];
	int plantpos[30][2];
};

// 矿山地图类，继承自地图节点，定义矿物数组
class MineMap :public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(MineMap);
	Mineral* mineral[50];
	int mineralpos[50][2];

};

class SeaMap:public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(SeaMap);
	
};

class VillageMap:public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(VillageMap);
	House* house[4];
	int nowSeason = 0;
	Texture2D* winter;
	Plant* tree[8];
	void setSeason(int season);
};

// 地图层类，负责管理多个地图节点
class MapLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MapLayer);
	MapNode* maps[5];
	//使用setMap设置当前地图，参数见const int 表。
	void setMap(int map);
    MapNode* currentMap;
};

// 地图测试类，继承自场景类，包含地图层
class Maptest :public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(Maptest);
	MapLayer* l1;
}; 



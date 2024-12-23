#pragma once
#include"cocos2d.h"
#include"Plantsandmineral.h"
#include"CharacterAnimation.h"
#include"guidepost.h"
#include"GameTime.h"
#include"menus.h"
#include"TimeBoard.h"
#include <cstdlib> // 包含rand()函数
#include <ctime>   // 包含time()函数

USING_NS_CC;
const int FARM = 0;
const int FOREST = 1;
const int MINE = 2;
const int SEA = 3;
const int VILLAGE = 4;
/*地图使用方式：
* 先删掉头文件的最后一个函数
* 再在创建场景时按这种方式创建;
* auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
*然后给scene加一个MapLayer对象即可
*/

/*地图切换方式
* 对MapLayer对象使用setMap方法即可，参数见const int 表。
*/

class AnimalManager;

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
	ItemBag* bag;

	int need_rand = 1;
	int nowmap = 0;
	void setEdgebox(int x1, int y1, int x2, int y2);
	CharacterAnimation* ch;
	void onMouseDown(EventMouse* event);
	guidepost* guide;
	CharacterAnimation* player;

private:
	EventListenerMouse* mouseListener;
};

// 农场地图类，继承自地图节点，增加了季节变化和植物数组的属性
class FarmMap :public MapNode
{
public:
	virtual bool init();
	CREATE_FUNC(FarmMap);
	AnimalManager* animals;
	void switchseason(int season);
	float switchtime = SEASON_TIME;
	void update(float dt)override;
	float timeSinceLastSeasonChange = 0.0f;
	void drawcropfence();
	void drawanimalfence();
	void createCollisionWall(int x1, int y1, int x2, int y2);
	void drawtree();
	Plant* treeincropfence[40];
	Plant* treeoutcropfence[10];
	int croptreenum = 0;
	int outcroptreenum = 10;
	int landstatus[15][15] = { 1 };
	Crop* allcrop[225];
	int cropnum = 0;


	void onMouseDown(EventMouse* event, int nowtool);
	int nowSeason = 0;
	House* house;
private:
	Texture2D* winter;
	Texture2D* nowater;
	Texture2D* spring;

	EventListenerMouse* mouseListener;
	Plant* checkcropPlantNode(EventMouse* event, int* number);
	Crop* checkcropNode(EventMouse* event, int* number);
};

// 森林地图类，继承自地图节点，包含植物数组
class ForestMap :public MapNode
{
public:
	virtual bool init();
	CREATE_FUNC(ForestMap);
	Plant* tree[30];
	int plantpos[30][2];
	int plantnum;
	void onMouseDown(EventMouse* event);
	EventListenerMouse* mouseListener;
	Plant* checkPlantNode(EventMouse* event, int* number);
};

// 矿山地图类，继承自地图节点，定义矿物数组
class MineMap :public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(MineMap);
	Mineral* mineral[50];
	int minenum = 0;
	int mineralpos[50][2];
	void onMouseDown(EventMouse* event);
	Mineral* checkMineNode(EventMouse* event, int* number);
private:
	EventListenerMouse* mouseListener;
};

class SeaMap :public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(SeaMap);
	Sprite* coconuttree[12];
	PhysicsBody* treebody[12];
};

class VillageMap :public MapNode {
public:
	virtual bool init();
	CREATE_FUNC(VillageMap);
	House* house[4];

	void switchseason(int season);
	float switchtime = SEASON_TIME;
	void update(float dt)override;
	float timeSinceLastSeasonChange = 0.0f;
	int nowSeason = 0;

	Texture2D* winter;
	Texture2D* spring;
	Plant* tree[12];
	void setSeason(int season);
};

// 地图层类，负责管理多个地图节点
class MapLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MapLayer);
	friend class MapNode;
	Vector<MapNode*> maps;
	//使用setMap设置当前地图，参数见const int 表。
	void setMap(int map);
	MapNode* currentMap;
	TimeBoard* timeboard;
	CharacterAnimation* ch;
	int i = 0;
};
#pragma once
#include"cocos2d.h"
#include"Plantsandmineral.h"
#include"CharacterAnimation.h"
USING_NS_CC;
const int FARM = 0;
const int FOREST = 1;
const int MINE = 2;
const int SEA = 3;
const int VILLAGE = 4;
/*��ͼʹ�÷�ʽ��
* ��ɾ��ͷ�ļ������һ������
* ���ڴ�������ʱ�����ַ�ʽ����;
* auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
*Ȼ���scene��һ��MapLayer���󼴿�
*/

/*��ͼ�л���ʽ
* ��MapLayer����ʹ��setMap�������ɣ�������const int ��
*/



//����
class House : public Node {
public:
	virtual bool init();
	CREATE_FUNC(House);
	
	Sprite* house;
};
// ��ͼ�ڵ��࣬�����˻����ĵ�ͼ�ڵ����Ժͷ���
class MapNode :public Node
{
public:
	virtual bool init();
	CREATE_FUNC(MapNode);
	Sprite* ground;
	int need_rand = 1;
	void setEdgebox(int x1, int y1, int x2, int y2);
	
};

// ũ����ͼ�࣬�̳��Ե�ͼ�ڵ㣬�����˼��ڱ仯��ֲ�����������
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

// ɭ�ֵ�ͼ�࣬�̳��Ե�ͼ�ڵ㣬����ֲ������
class ForestMap :public MapNode
{
public:
	virtual bool init();
	CREATE_FUNC(ForestMap);
	Plant* tree[30];
	int plantpos[30][2];
};

// ��ɽ��ͼ�࣬�̳��Ե�ͼ�ڵ㣬�����������
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

// ��ͼ���࣬�����������ͼ�ڵ�
class MapLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MapLayer);
	MapNode* maps[5];
	//ʹ��setMap���õ�ǰ��ͼ��������const int ��
	void setMap(int map);
    MapNode* currentMap;
};


static Scene* createMapScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = MapLayer::create();
	layer->setMap(5);
	scene->addChild(layer);
	return scene;
}




#pragma once
#include"cocos2d.h"
#include"menus.h"
#include"maptry.h"
USING_NS_CC;

class GameScene :public Scene
{
public:
	Scene* createScene();
	CREATE_FUNC(GameScene);
	void OnMouseDown(Event* event,CharacterAnimation* character);
	virtual bool init();
	Scene* scene;
	MapLayer* map_layer;
	ItemLayer* item_layer;
};
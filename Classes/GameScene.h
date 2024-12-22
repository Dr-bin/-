#pragma once
#include"cocos2d.h"
#include"menus.h"
#include"maptry.h"
#include"PopupBase.h"
USING_NS_CC;

class GameScene :public Scene
{
public:
	Scene* createScene();
	CREATE_FUNC(GameScene);
	void OnMouseDown(EventMouse* event,CharacterAnimation* character);
	virtual bool init();
	Scene* scene;
	MapLayer* map_layer;
	ItemLayer* item_layer;
	
};
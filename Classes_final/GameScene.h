#pragma once
#include"cocos2d.h"
#include"Cook.h"
#include"maptry.h"
#include"PopupBase.h"
#include"LevelTree.h"
USING_NS_CC;

class GameScene :public Scene
{
public:
	Scene* createScene();
	CREATE_FUNC(GameScene);
	void OnMouseDown(EventMouse* event, CharacterAnimation* character);
	virtual bool init();
	Scene* scene;
	MapLayer* map_layer;
	ItemLayer* item_layer;

};
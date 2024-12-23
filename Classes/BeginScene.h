#pragma once
#include "cocos2d.h"
#include"GameScene.h"

USING_NS_CC;

class BeginScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(BeginScene);
    Sprite* background;
    Sprite* title;
    Sprite* board1;
    Sprite* board2;
    Label* start;
    Label* exit;

    void onMouseDown(EventMouse* event);
};
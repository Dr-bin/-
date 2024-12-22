#pragma

#ifndef MYSCENE_H__
#define MYSCENE_H__

#include "cocos2d.h"
#include"Plantsandmineral.h"
#include"maptry.h"
#include"Box2D/Box2D.h"
//#include"MouseKeyboardListener.h"
using namespace std;
USING_NS_CC;

class MyScene : public Scene
{
public:
    static MyScene* createScene();

    virtual bool init()override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual void onEnter()override;

    // implement the "static create()" method manually
    CREATE_FUNC(MyScene);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(EventMouse* event);
    void onMouseUp(EventMouse* event);
    void onMouseMove(EventMouse* event);
    void onMouseScroll(EventMouse* event);
    void update(float deltaTime);
    Scene* myscene;
    Label* _infoLabel;
    Plant* _tree = nullptr;
    Mineral* _stone = nullptr;
    Label* _label = nullptr;
    int** farmland;
    int gridwidth = 96;
    int gridheight = 54;
};
#endif // MYSCENE_H__

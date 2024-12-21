#pragma once

//这是个弹窗基类，实现一个外框加一个右上角的关闭键

#ifndef __BASEPOP__
#define __BASEPOP__

#include "cocos2d.h"
USING_NS_CC;

class BasePopup : public Node
{
public:
    static BasePopup* getCurrentPopup();
    static void closeCurrentPopup();

    virtual bool init();
    CREATE_FUNC(BasePopup);

    virtual void show(); 
    virtual void hide();

protected:
    Sprite* popupContainer;
    //Sprite* background;//这个背景是如果要改成点击背景关闭的话需要用到的变量，忽略就行
    Sprite* closeBtnBg;
    Label* closeBtnLabel;//关闭弹窗按键
    Node* contentArea;//这是子类弹窗需要添加到的节点！！！！！！！！！！！
    EventKeyboard::KeyCode stimulateKey;//弹窗激活按键，需要在子类中定义

    static BasePopup* currentPopup;

    virtual void onShow() {};//请在这个函数里放你子类的自定义的呈现！！！！！！！！！！！
    virtual void onHide() {};

    //bool onTouchBegan(Touch* touch, Event* event);
    //void onTouchEnded(Touch* touch, Event* event);
};


#endif // __BASEPOP__
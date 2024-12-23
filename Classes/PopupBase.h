#pragma once

//这是个弹窗基类，实现一个外框加一个右上角的关闭键

#ifndef __BASEPOP__
#define __BASEPOP__

#include "cocos2d.h"
#include"menus.h"
USING_NS_CC;

class PopupBase : public Node
{
public:
    static PopupBase* getCurrentPopup();
    static void closeCurrentPopup();

    virtual bool init();
    CREATE_FUNC(PopupBase);

    virtual void show(); 
    virtual void hide();
    EventKeyboard::KeyCode stimulateKey;//弹窗激活按键，需要在子类中定义
protected:
    Sprite* popupContainer;
    //Sprite* background;//这个背景是如果要改成点击背景关闭的话需要用到的变量，忽略就行
    Sprite* closeBtnBg;
    Label* closeBtnLabel;//关闭弹窗按键
    Node* contentArea;//这是子类弹窗需要添加到的节点！！！！！！！！！！！
   

    static PopupBase* currentPopup;

    virtual void onShow() {};//请在这个函数里放你子类的自定义的呈现！！！！！！！！！！！
    virtual void onHide() {};

    //bool onTouchBegan(Touch* touch, Event* event);
    //void onTouchEnded(Touch* touch, Event* event);
};

class PopupShop :public PopupBase
{
public:
    bool init();
    CREATE_FUNC(PopupShop);
    void onShow();
    void onHide();
    ItemBag* itemBag;
    EventListenerMouse* _mouse;
    Vector<ShopBox*> shopBoxs;
    void setShopBoxs(int tags[5]);
    void OnMouseDown(EventMouse* event);
    int tags[5] = { 1,2,3,4,12 };
    void changeTags(int tags[5]){
        for (int i = 0; i < 5; i++) {
            this->tags[i] = tags[i];
       }
     }
};

#endif // __BASEPOP__
#pragma once

//���Ǹ��������࣬ʵ��һ������һ�����ϽǵĹرռ�

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
    EventKeyboard::KeyCode stimulateKey;//�������������Ҫ�������ж���
protected:
    Sprite* popupContainer;
    //Sprite* background;//������������Ҫ�ĳɵ�������رյĻ���Ҫ�õ��ı��������Ծ���
    Sprite* closeBtnBg;
    Label* closeBtnLabel;//�رյ�������
    Node* contentArea;//�������൯����Ҫ��ӵ��Ľڵ㣡��������������������
   

    static PopupBase* currentPopup;

    virtual void onShow() {};//����������������������Զ���ĳ��֣���������������������
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
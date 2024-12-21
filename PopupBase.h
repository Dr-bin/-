#pragma once

//���Ǹ��������࣬ʵ��һ������һ�����ϽǵĹرռ�

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
    //Sprite* background;//������������Ҫ�ĳɵ�������رյĻ���Ҫ�õ��ı��������Ծ���
    Sprite* closeBtnBg;
    Label* closeBtnLabel;//�رյ�������
    Node* contentArea;//�������൯����Ҫ��ӵ��Ľڵ㣡��������������������
    EventKeyboard::KeyCode stimulateKey;//�������������Ҫ�������ж���

    static BasePopup* currentPopup;

    virtual void onShow() {};//����������������������Զ���ĳ��֣���������������������
    virtual void onHide() {};

    //bool onTouchBegan(Touch* touch, Event* event);
    //void onTouchEnded(Touch* touch, Event* event);
};


#endif // __BASEPOP__
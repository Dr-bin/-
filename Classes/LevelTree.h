#pragma once

#include "cocos2d.h"
#include "PopupBase.h"
#include "DataProvider.h"

USING_NS_CC;
#define maxEX 100.0

//�������ʾ�ȼ��;����õĵ���������ʹ����Ҫ�õ�DataProvider��ȡCharater����Ϣ��
//����Ҫ�ڽ�ɫ��ʵ����⿴������ڿ��������ֲ�Ϳ�����������������ļ�¼
//Ҫ����DataProviderһ��4��С�����飬��û�иĳɸ��õ����ͣ����Դ�Сֻ��Ϊ4

//����������
class LevelTree : public PopupBase
{
public:
	static LevelTree* create() {//exΪ���澭�������
        auto ret = new (std::nothrow) LevelTree();
        if (ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
        return ret;
	}

    bool init();

    //void updataEX(int* e) {�����ã�ûɾ
    //    for (int i = 0; i < 4; i++)
    //        ex[i] = e[i];
    //    return;
    //}

    virtual void onShow();
    virtual void onHide();

private:
    float startx = 0;
    float starty = 0;
    float dy = 0;
    float times[4] = { 0 };
    int* ex = NULL;
    Size fSize;

};


bool LevelTree::init() {

    if (!PopupBase::init())
    {
        return false;
    }

    stimulateKey = EventKeyboard::KeyCode::KEY_L;

    Sprite* LevelBackGround = Sprite::create("level.png");
    Sprite* fill = Sprite::create("redfill.png");

    auto BoardSize = LevelBackGround->getContentSize();
    fSize = fill->getContentSize();

    startx = -BoardSize.width / 2.7;
    starty = BoardSize.height / 2.5;
    dy = BoardSize.height / 3.8;

    onShow();

    contentArea->setScale(1.0f);

    return true;
}

void LevelTree::onShow()
{
    Sprite* LevelBackGround = Sprite::create("level.png");
    Sprite* fill1 = Sprite::create("redfill.png");
    Sprite* fill2 = Sprite::create("redfill.png");
    Sprite* fill3 = Sprite::create("redfill.png");
    Sprite* fill4 = Sprite::create("redfill.png");

    auto BoardSize = LevelBackGround->getContentSize();
    fSize = fill1->getContentSize();

    contentArea->addChild(LevelBackGround);
    contentArea->addChild(fill1);
    contentArea->addChild(fill2);
    contentArea->addChild(fill3);
    contentArea->addChild(fill4);

    ex = DataProvider::getInstance()->getEXData();
    for (int i = 0; i < 4; i++)
        times[i] = float(ex[i] / maxEX) * 3.7f;

    fill1->setScale(times[0], 0.2f);
    fill2->setScale(times[1], 0.2f);
    fill3->setScale(times[2], 0.2f);
    fill4->setScale(times[3], 0.2f);

    float x1 = startx + fSize.width / 2 * times[0];//��ʼλ�ü��ϱ��ĳ��ȵ�һ��
    float x2 = startx + fSize.width / 2 * times[1];
    float x3 = startx + fSize.width / 2 * times[2];
    float x4 = startx + fSize.width / 2 * times[3];

    fill1->setPosition(x1, starty);
    fill2->setPosition(x2, starty - dy);
    fill3->setPosition(x3, starty - 2 * dy);
    fill4->setPosition(x4, starty - 3 * dy);

    auto Poptitle = Label::createWithSystemFont("Level Tree", "Garamond", 36);
    Poptitle->setPosition(0.0f, 2.3 * dy);
    contentArea->addChild(Poptitle);

    return;
}

void LevelTree::onHide()
{
    contentArea->removeAllChildren();
    return;
}

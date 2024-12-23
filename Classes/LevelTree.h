#pragma once

#include "cocos2d.h"
#include "PopupBase.h"
#include "DataProvider.h"

USING_NS_CC;
#define maxEX 100.0

//这个是显示等级和经验用的弹窗，具体使用需要用到DataProvider获取Charater的信息，
//具体要在角色里实现烹饪次数，挖矿次数，种植和砍树次数，钓鱼次数的记录
//要传给DataProvider一个4大小的数组，我没有改成更好的类型，所以大小只能为4

//经验树弹窗
class LevelTree : public PopupBase
{
public:
	static LevelTree* create() {//ex为储存经验的数组
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

    //void updataEX(int* e) {测试用，没删
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



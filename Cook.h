#pragma once

#include "ItemLayer.h"
#include "PopupBase.h"

class Cook : public PopupBase
{
public:
    static Cook* create() {//ex为储存经验的数组
        auto ret = new (std::nothrow) Cook();
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

    virtual void onShow();
    virtual void onHide();

    bool isinpos(Vec2& p, float x1, float x2, float y1, float y2) {
        if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2)
            return true;
        return false;
    }

    ItemBag* bag;

private:

    SquareBox* cook_origin1;
    SquareBox* cook_origin2;
    SquareBox* cook_origin3;
    SquareBox* cook_result;
    Sprite* uptocookBt;
    Sprite* mixBt;
    EventListenerTouchOneByOne* touchListener_1;

};


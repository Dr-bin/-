#include "ItemLayer.h"
#include "Cook.h"

// ItemLayer类的初始化方法
bool ItemLayer::init()
{
    if (!Layer::init())
        return false;
    item_bag = ItemBag::create();
    this->addChild(item_bag);

    auto COOK = Cook::create();
    COOK->stimulateKey = EventKeyboard::KeyCode::KEY_C;
    COOK->bag = item_bag;
    this->addChild(COOK);

    return true;
}


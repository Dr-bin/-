#pragma once

#include "menus.h"

//游戏内物品栏层
class ItemLayer :public Layer
{
public:
	CREATE_FUNC(ItemLayer);
	virtual bool init();
	ItemBag* item_bag;

};


#pragma once

#include "menus.h"

//��Ϸ����Ʒ����
class ItemLayer :public Layer
{
public:
	CREATE_FUNC(ItemLayer);
	virtual bool init();
	ItemBag* item_bag;

};


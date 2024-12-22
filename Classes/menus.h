#pragma once
#include"cocos2d.h"
#include"maptry.h"
USING_NS_CC;
//物品栏标签
const int ItemNullTag = -1;
const int ItemAxeTag = 1;
const int ItemHoeTag = 2;
const int ItemPickTag = 3;
const int ItemBucketTag = 4;
const int ItemPotatoSeedTag = 5;
const int ItemPotatoTag = 6;
const int ItemCarrotTag = 7;
const int ItemCarrotSeedTag = 8;
const int ItemPumpkinSeedTag = 9;
const int ItemPumpkinTag = 10;
const int ItemMilkTag = 11;
const int ItemFishingRodTag = 12;
const int ItemFish1Tag=13;
const int ItemFish2Tag=14;
const int ItemFish3Tag=15;


/*使用方法：新建一个ItemLayer到scene中
* Item类为物品栏物品的基类，新物品需要继承Item类并实现自己的init函数，并在init函数中添加自己的sprite和label
ItemBag的addItems函数添加物品，getItem函数获取物品，selectItem函数选择物品，serchItem函数搜索物品，removeItem函数删除物品，onMouseDown函数响应鼠标点击事件
新物品的tag请从13开始*/

//物品栏内容物
class Item :public Node
{
public:
	CREATE_FUNC(Item);
	virtual bool init();
	void updateNum(int num);
	void changelabel(std::string str);
	Sprite* item;
	std::string name;
	Label* num_label;
	int tag;
	int num;
	int sell_price;
	int buy_price;
};
//物品栏斧子d
class ItemAxe :public Item
{
public:
	CREATE_FUNC(ItemAxe);
	virtual bool init();
};
//物品栏锄头
class ItemHoe :public Item
{
public:
	CREATE_FUNC(ItemHoe);
	virtual bool init();
};
//物品栏镐
class ItemPick :public Item
{
public:
	CREATE_FUNC(ItemPick);
	virtual bool init();
};
//物品栏桶
class ItemBucket :public Item
{
public:
	CREATE_FUNC(ItemBucket);
	virtual bool init();
};
//物品栏土豆种子
class ItemPotatoSeed :public Item
{
public:
	CREATE_FUNC(ItemPotatoSeed);
	virtual bool init();
};
//物品栏土豆
class ItemPotato :public Item
{
public:
	CREATE_FUNC(ItemPotato);
	virtual bool init();
};
//物品栏胡萝卜
class ItemCarrot:public Item
{
public:
	CREATE_FUNC(ItemCarrot);
	virtual bool init();
};
//物品栏胡萝卜种子
class ItemCarrotSeed:public Item
{
public:
	CREATE_FUNC(ItemCarrotSeed);
	virtual bool init();
};
//物品栏南瓜种子
class ItemPumpkinSeed :public Item
{
public:
	CREATE_FUNC(ItemPumpkinSeed);
	virtual bool init();
};
//物品栏南瓜
class ItemPumpkin :public Item
{
public:
	CREATE_FUNC(ItemPumpkin);
	virtual bool init();
};
//物品栏牛奶
class ItemMilk :public Item
{
public:
	CREATE_FUNC(ItemMilk);
	virtual bool init();
};
//物品栏钓鱼竿
class ItemFishingRod :public Item
{
public:
	CREATE_FUNC(ItemFishingRod);
	virtual bool init();
};
//物品栏鱼
class ItemFish1 :public Item
{
public:
	CREATE_FUNC(ItemFish1);
	virtual bool init();
};
class ItemFish2 :public Item
{
public:
	CREATE_FUNC(ItemFish2);
	virtual bool init();
};
class ItemFish3 :public Item
{
public:
	CREATE_FUNC(ItemFish3);
	virtual bool init();
};
//菜单框
class Menubox :public Node
{
public:
	CREATE_FUNC(Menubox);
	virtual bool init();
	Sprite* box;
};

//方形菜单框
class SquareBox:public Menubox
{
public:
	CREATE_FUNC(SquareBox);
	virtual bool init();
	Item* content;//内容物
	int contentTag;
	void addContent(Item* item);
	void removeContent();
	int getContentTag();
};

//物品栏

class ItemBag :public Node
{
public:
	CREATE_FUNC(ItemBag);
	virtual bool init();
	Vector<SquareBox*> square_boxes;
	int now_select;
	int money;
	Label* money_label;
	void updateMoney(int money);
	Item* getNowItem();
	Sprite* cur;
	Item* getItem(int tag);
	void addItem(int tag,int num);
	void removeItem(int pos, int num);
	void selectItem(int pos);
	int serchItem(int tag);
	int onMouseDown(EventMouse* event, CharacterAnimation* player);
};



//游戏内物品栏层
class ItemLayer :public Layer
{
public:
	CREATE_FUNC(ItemLayer);
	virtual bool init();
	ItemBag* item_bag;

};

class ShopBox :public SquareBox {
public:
	CREATE_FUNC(ShopBox);
	virtual bool init();
	void addProduction(Item* item);
	int tag;
	Sprite* buy_button;
	Sprite* sell_button;
	void onMouseDown(EventMouse* event,ItemBag* item_bag);
	ItemBag* item_bag;
};

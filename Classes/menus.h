#pragma once
#include"cocos2d.h"
#include"maptry.h"
USING_NS_CC;
//��Ʒ����ǩ
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


/*ʹ�÷������½�һ��ItemLayer��scene��
* Item��Ϊ��Ʒ����Ʒ�Ļ��࣬����Ʒ��Ҫ�̳�Item�ಢʵ���Լ���init����������init����������Լ���sprite��label
ItemBag��addItems���������Ʒ��getItem������ȡ��Ʒ��selectItem����ѡ����Ʒ��serchItem����������Ʒ��removeItem����ɾ����Ʒ��onMouseDown������Ӧ������¼�
����Ʒ��tag���13��ʼ*/

//��Ʒ��������
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
//��Ʒ������d
class ItemAxe :public Item
{
public:
	CREATE_FUNC(ItemAxe);
	virtual bool init();
};
//��Ʒ����ͷ
class ItemHoe :public Item
{
public:
	CREATE_FUNC(ItemHoe);
	virtual bool init();
};
//��Ʒ����
class ItemPick :public Item
{
public:
	CREATE_FUNC(ItemPick);
	virtual bool init();
};
//��Ʒ��Ͱ
class ItemBucket :public Item
{
public:
	CREATE_FUNC(ItemBucket);
	virtual bool init();
};
//��Ʒ����������
class ItemPotatoSeed :public Item
{
public:
	CREATE_FUNC(ItemPotatoSeed);
	virtual bool init();
};
//��Ʒ������
class ItemPotato :public Item
{
public:
	CREATE_FUNC(ItemPotato);
	virtual bool init();
};
//��Ʒ�����ܲ�
class ItemCarrot:public Item
{
public:
	CREATE_FUNC(ItemCarrot);
	virtual bool init();
};
//��Ʒ�����ܲ�����
class ItemCarrotSeed:public Item
{
public:
	CREATE_FUNC(ItemCarrotSeed);
	virtual bool init();
};
//��Ʒ���Ϲ�����
class ItemPumpkinSeed :public Item
{
public:
	CREATE_FUNC(ItemPumpkinSeed);
	virtual bool init();
};
//��Ʒ���Ϲ�
class ItemPumpkin :public Item
{
public:
	CREATE_FUNC(ItemPumpkin);
	virtual bool init();
};
//��Ʒ��ţ��
class ItemMilk :public Item
{
public:
	CREATE_FUNC(ItemMilk);
	virtual bool init();
};
//��Ʒ�������
class ItemFishingRod :public Item
{
public:
	CREATE_FUNC(ItemFishingRod);
	virtual bool init();
};
//��Ʒ����
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
//�˵���
class Menubox :public Node
{
public:
	CREATE_FUNC(Menubox);
	virtual bool init();
	Sprite* box;
};

//���β˵���
class SquareBox:public Menubox
{
public:
	CREATE_FUNC(SquareBox);
	virtual bool init();
	Item* content;//������
	int contentTag;
	void addContent(Item* item);
	void removeContent();
	int getContentTag();
};

//��Ʒ��

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



//��Ϸ����Ʒ����
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

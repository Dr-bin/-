#pragma once

#include "GameItem.h"
USING_NS_CC;

#define INVENTORY_SIZE 8//设物品栏大小为8

class Inventory : public cocos2d::Node
{
public:
    static Inventory* create(const Vec2& position);

    virtual bool init(const Vec2& position);

    int getNumOfHand(){ return _inhand; }
    GameItem* getInHandGameItem() { return _GameItem[getNumOfHand()]; }//获取手中物品的信息
    bool addGameItem(GameItem* GameItem);//增加物品栏中物品
    bool removeGameItem(int id);//移除物品栏中物品
    bool haveEmptyPos(int& p);//检测有没有空位置
    int getGameItemPosById(int id, int p = 0) const;//通过物品id获取物品在物品栏中p以后的位置,遍历结束若没有则返回物品栏大小
    int getGameItemCountByPos(int pos) const;//获取物品栏某位置物品数量

    // 展示物品栏
    void displayGameItems() const;

private:
    int _inhand;
    GameItem* _GameItem[INVENTORY_SIZE];
    bool _valid[INVENTORY_SIZE];//表示物品栏第几个位置有没有东西

};

Inventory* Inventory::create(const Vec2& position) {
    auto ret = new (std::nothrow) Inventory();
    if (ret && ret->init(position))
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

bool Inventory::init(const Vec2& position) {
    auto drawNode = DrawNode::create();
    this->addChild(drawNode);

    drawNode->drawRect(Vec2(0, 0), position,Color4F::BLUE);
    return true;
}

int Inventory::getGameItemPosById(int id, int p) const {
    while (p < INVENTORY_SIZE) {
        if (_GameItem[p]->getId() == id)
            return p;
        p++;
    }
    return p;
}

bool Inventory::addGameItem(GameItem* GameItem)
{
    int pos = 0;//物品栏的第几个位置
    while (true) {
        pos = getGameItemPosById(GameItem->getId(), pos);
        if (pos < INVENTORY_SIZE) {//如果找到同类
            if (_GameItem[pos]->getCount() < _GameItem[pos]->getMaxStack()) {//如果该物品还没达到最大
                _GameItem[pos]->addCount(GameItem->getCount());//合并两个的数量
                delete GameItem;//合并数量之后删除原来的对象
                return true;
            }
            continue;//达到最大则继续找
        }
        else//如果没有未满同类
            break;
    }
    if (haveEmptyPos(pos)) {//如果有空位置
        _GameItem[pos] = GameItem;//将该对象的指针放入数组中空位置
        _valid[pos] = true;
    }
    else //无空位
        return false;
}

//这里不是删除！是移除
bool Inventory::removeGameItem(int pos)
{
    if (pos >= 0 && pos < INVENTORY_SIZE)
    {
        if (_valid[pos]) {
            _valid[pos] = 0;
            return true;
        }
    }
    return false;
}

bool Inventory::haveEmptyPos(int& p)
{
    for (int i = 0; i < INVENTORY_SIZE; i++)
        if (!_valid[i]) {
            p = i;
            return true;
        }
    return false;
}

int Inventory::getGameItemCountByPos(int pos) const
{
    if (_valid[pos])
        return _GameItem[pos]->getCount();
    return 0;
}

//展示物品栏函数
void Inventory::displayGameItems() const
{
    
}
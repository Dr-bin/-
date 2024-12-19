#pragma once

#include "cocos2d.h"
USING_NS_CC;

//物品基类
class GameItem : public cocos2d::Node
{
public:
    static const int INVALID_ID = -1;

    GameItem();
    virtual ~GameItem();

    //放物品使用动画和进行交互逻辑
    virtual void func(){}

    virtual bool init(int id, const std::string& name, const std::string& iconPath, int maxStack);

    int getId() const { return _id; }
    const std::string& getName() const { return _name; }
    const std::string& getIconPath() const { return _iconPath; }
    int getMaxStack() const { return _maxStack; }
    int getCount() const { return _count; }

    void setCount(int count);
    void addCount(int amount);

    // Create a sprite representation of the GameItem
    cocos2d::Sprite* createIconSprite() const;

private:
    int _id;
    std::string _name;//物品名
    std::string _iconPath;//物品图标路径
    int _maxStack;//最大堆叠数
    int _count;
};

// Implementation
GameItem::GameItem()
    : _id(INVALID_ID), _maxStack(1), _count(1)
{
}

GameItem::~GameItem()
{
}

bool GameItem::init(int id, const std::string& name, const std::string& iconPath, int maxStack)
{
    _id = id;
    _name = name;
    _iconPath = iconPath;
    _maxStack = maxStack;
    return true;
}

void GameItem::setCount(int count)
{
    if (count < 0) _count = 0;
    else if (count > _maxStack) _count = _maxStack;
    else _count = count;
}

void GameItem::addCount(int amount)
{
    int newCount = _count + amount;
    if (newCount < 0) _count = 0;
    else if (newCount > _maxStack) _count = _maxStack;
    else _count = newCount;
}

cocos2d::Sprite* GameItem::createIconSprite() const
{
    auto sprite = cocos2d::Sprite::create(_iconPath);
    if (sprite)
    {
        // Optionally set sprite properties here
    }
    return sprite;
}
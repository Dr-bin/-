#pragma once
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
//原生植物类，四个季节有四个显示
class Plant : public cocos2d::Node
{
public:

    // 创建植物实例
    static Plant* create(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    // 初始化植物
    bool init(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    void updateSeasons(float dt);
    // 更新植物的季节显示
    void switchSeason(int season);
    // 减少生命值
    void damage(int amount);
private:
    Sprite* _spriteSpring;
    Sprite* _spriteSummer;
    Sprite* _spriteAutumn;
    Sprite* _spriteWinter;
    Sprite* _currentSprite; // 当前显示的精灵
    int _health;
    int _currentSeason;
    float switchtime = 1.0f;    //季节更替的时间
    bool _isTregger;
    // 树倒下和消失的动画
    void fallDownAndDisappear();
    // 移除自身的函数
    void removeThis();
};
//矿石类，可以被开采
class Mineral : public cocos2d::Node 
{
public:
    // 创建矿石实例
    static Mineral* create(const string& spriteFile);
    // 初始化矿石
    bool init(const string& spriteFile);
    // 减少生命值
    void damage(int amount);
private:
    Sprite* _sprite;
    int _health;
    int _state;    //矿石的状态，0为被破坏，1为完整
    // 开采矿石
    void Disappear();
    //移除自身
    void removeThis();
};
//作物类，可以成长
class Crop : public cocos2d::Node
{
public:
    //创建作物实例
    static Crop* create(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite);
    //初始化作物
    bool init(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite);
    //设置成长状态函数
    void setgrow(bool if_grow)
    {
        ifgrow = if_grow;
    }
    //更新作物状态
    void updatastage(float dt);
    //转换作物状态
    void switchstage();
private:
    Sprite* _seedSprite;
    Sprite* _youngSprite;
    Sprite* _matureSprite;
    Sprite* _deadSprite;
    Sprite* _currentSprite;
    int _growthstage;
    int _health;
    float switchtime = 10.0f;
    bool ifgrow;    //是否为成长状态
    bool ifripe;    //是否成熟
    bool ifwithered;   //是否枯萎
    void Disappear();
    void Pick();
    void removeThis();
};

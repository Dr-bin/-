#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace std;
USING_NS_CC;

class stillobject :public Node
{
public:
    int identity;
};
//原生植物类，四个季节有四个显示
class Plant : public stillobject
{
public:
    // 创建植物实例
    static Plant* create(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    // 初始化植物
    bool init(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    void update(float dt)override;
    // 更新植物的季节显示
    void switchSeason(int season);
    // 减少生命值
    void damage(int amount);
    PhysicsBody* body;
    Sprite* _spriteSpring;
    Sprite* _spriteSummer;
    Sprite* _spriteAutumn;
    Sprite* _spriteWinter;
    Sprite* _currentSprite; // 当前显示的精灵
    int _health;
    int _currentSeason;
    float switchtime = 5.0f;    //季节更替的时间
    float timeSinceLastSeasonChange = 0.0f;
    bool _isTregger;
    // 树倒下和消失的动画
    void fallDownAndDisappear();
    // 移除自身的函数
    void removeThis();
    void setScale(float scale) 
    {
        // 调用基类的setScale方法进行缩放
        Node::setScale(scale);
        // 更新缩放因子
        _scaleFactor *= scale;
    }
    Size getcontentSize();
private:
    Size _originalContentSize; // 原始内容大小
    float _scaleFactor; // 缩放因子
};
//矿石类，可以被开采
class Mineral : public stillobject
{
public:
    // 创建矿石实例
    static Mineral* create(const string& spriteFile);
    // 初始化矿石
    bool init(const string& spriteFile);
    // 减少生命值
    void damage(int amount);
    void setScale(float scale)
    {
        // 调用基类的setScale方法进行缩放
        Node::setScale(scale);
        // 更新缩放因子
        _scaleFactor *= scale;
    }
    Size getcontentSize();
    int _state;    //矿石的状态，0为被破坏，1为完整
private:
    Sprite* _sprite;
    int _health;
    Size _originalContentSize; // 原始内容大小
    float _scaleFactor; // 缩放因子
    // 开采矿石
    void Disappear();
    //移除自身
    void removeThis();
};
//作物类，可以成长
class Crop : public stillobject
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
    void setScale(float scale)
    {
        // 调用基类的setScale方法进行缩放
        Node::setScale(scale);
        // 更新缩放因子
        _scaleFactor *= scale;
    }
    //更新作物状态
    void update(float dt);
    //转换作物状态
    void switchstage();
    Size getcontentSize();
    //得到灌溉后加速成长
    void plusspeed()
    {
        growspeed = 2;
        irrigatetime = 3.1;
    }
    //被摧毁
    void damage();
    //获取作物状态
    int getstage();
    void Pick();
    void setifgrow(bool a)
    {
        ifgrow = a;
    }
private:
    Sprite* _seedSprite;
    Sprite* _youngSprite;
    Sprite* _matureSprite;
    Sprite* _finalSprite;
    Sprite* _currentSprite;
    Sprite* _deadSprite;
    float timeSince = 0.0f;
    int _growthstage;
    int _health;
    float switchtime = 10.0f;
    bool ifgrow;    //是否为成长状态
    int growspeed;    //成长速度
    bool ifripe;    //是否成熟
    bool ifwithered;   //是否枯萎
    float irrigatetime = 0.0;
    void Disappear();
    void removeThis();
    void switchwithered();
    Size _originalContentSize; // 原始内容大小
    float _scaleFactor; // 缩放因子
};

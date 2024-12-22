#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace std;
USING_NS_CC;
class guidepost :public Node
{
public:
    // 创建路标实例
    static guidepost* create(int id);
    bool init(int id);
    int getidentity();
    void move();
    void update(float dt);
    Size getcontentSize();
    void setScale(float scale)
    {
        // 调用基类的setScale方法进行缩放
        Node::setScale(scale);
        // 更新缩放因子
        _scaleFactor *= scale;
    }
private:
    int identity;
    float time = 0.0f;
    Sprite* guide;
    Size _originalContentSize; // 原始内容大小
    float _scaleFactor; // 缩放因子
};
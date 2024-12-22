#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"
using namespace std;
USING_NS_CC;
class guidepost :public Node
{
public:
    // ����·��ʵ��
    static guidepost* create(int id);
    bool init(int id);
    int getidentity();
    void move();
    void update(float dt);
    Size getcontentSize();
    void setScale(float scale)
    {
        // ���û����setScale������������
        Node::setScale(scale);
        // ������������
        _scaleFactor *= scale;
    }
private:
    int identity;
    float time = 0.0f;
    Sprite* guide;
    Size _originalContentSize; // ԭʼ���ݴ�С
    float _scaleFactor; // ��������
};
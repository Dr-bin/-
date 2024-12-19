#pragma once

#include "GameItem.h"
USING_NS_CC;

#define INVENTORY_SIZE 8//����Ʒ����СΪ8

class Inventory : public cocos2d::Node
{
public:
    static Inventory* create(const Vec2& position);

    virtual bool init(const Vec2& position);

    int getNumOfHand(){ return _inhand; }
    GameItem* getInHandGameItem() { return _GameItem[getNumOfHand()]; }//��ȡ������Ʒ����Ϣ
    bool addGameItem(GameItem* GameItem);//������Ʒ������Ʒ
    bool removeGameItem(int id);//�Ƴ���Ʒ������Ʒ
    bool haveEmptyPos(int& p);//�����û�п�λ��
    int getGameItemPosById(int id, int p = 0) const;//ͨ����Ʒid��ȡ��Ʒ����Ʒ����p�Ժ��λ��,����������û���򷵻���Ʒ����С
    int getGameItemCountByPos(int pos) const;//��ȡ��Ʒ��ĳλ����Ʒ����

    // չʾ��Ʒ��
    void displayGameItems() const;

private:
    int _inhand;
    GameItem* _GameItem[INVENTORY_SIZE];
    bool _valid[INVENTORY_SIZE];//��ʾ��Ʒ���ڼ���λ����û�ж���

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
    int pos = 0;//��Ʒ���ĵڼ���λ��
    while (true) {
        pos = getGameItemPosById(GameItem->getId(), pos);
        if (pos < INVENTORY_SIZE) {//����ҵ�ͬ��
            if (_GameItem[pos]->getCount() < _GameItem[pos]->getMaxStack()) {//�������Ʒ��û�ﵽ���
                _GameItem[pos]->addCount(GameItem->getCount());//�ϲ�����������
                delete GameItem;//�ϲ�����֮��ɾ��ԭ���Ķ���
                return true;
            }
            continue;//�ﵽ����������
        }
        else//���û��δ��ͬ��
            break;
    }
    if (haveEmptyPos(pos)) {//����п�λ��
        _GameItem[pos] = GameItem;//���ö����ָ����������п�λ��
        _valid[pos] = true;
    }
    else //�޿�λ
        return false;
}

//���ﲻ��ɾ�������Ƴ�
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

//չʾ��Ʒ������
void Inventory::displayGameItems() const
{
    
}
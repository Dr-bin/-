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
//ԭ��ֲ���࣬�ĸ��������ĸ���ʾ
class Plant : public stillobject
{
public:
    // ����ֲ��ʵ��
    static Plant* create(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    // ��ʼ��ֲ��
    bool init(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    void update(float dt)override;
    // ����ֲ��ļ�����ʾ
    void switchSeason(int season);
    // ��������ֵ
    void damage(int amount);
    PhysicsBody* body;
    Sprite* _spriteSpring;
    Sprite* _spriteSummer;
    Sprite* _spriteAutumn;
    Sprite* _spriteWinter;
    Sprite* _currentSprite; // ��ǰ��ʾ�ľ���
    int _health;
    int _currentSeason;
    float switchtime = 5.0f;    //���ڸ����ʱ��
    float timeSinceLastSeasonChange = 0.0f;
    bool _isTregger;
    // �����º���ʧ�Ķ���
    void fallDownAndDisappear();
    // �Ƴ�����ĺ���
    void removeThis();
    void setScale(float scale) 
    {
        // ���û����setScale������������
        Node::setScale(scale);
        // ������������
        _scaleFactor *= scale;
    }
    Size getcontentSize();
private:
    Size _originalContentSize; // ԭʼ���ݴ�С
    float _scaleFactor; // ��������
};
//��ʯ�࣬���Ա�����
class Mineral : public stillobject
{
public:
    // ������ʯʵ��
    static Mineral* create(const string& spriteFile);
    // ��ʼ����ʯ
    bool init(const string& spriteFile);
    // ��������ֵ
    void damage(int amount);
    void setScale(float scale)
    {
        // ���û����setScale������������
        Node::setScale(scale);
        // ������������
        _scaleFactor *= scale;
    }
    Size getcontentSize();
    int _state;    //��ʯ��״̬��0Ϊ���ƻ���1Ϊ����
private:
    Sprite* _sprite;
    int _health;
    Size _originalContentSize; // ԭʼ���ݴ�С
    float _scaleFactor; // ��������
    // ���ɿ�ʯ
    void Disappear();
    //�Ƴ�����
    void removeThis();
};
//�����࣬���Գɳ�
class Crop : public stillobject
{
public:
    //��������ʵ��
    static Crop* create(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite);
    //��ʼ������
    bool init(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite);
    //���óɳ�״̬����
    void setgrow(bool if_grow)
    {
        ifgrow = if_grow;
    }
    void setScale(float scale)
    {
        // ���û����setScale������������
        Node::setScale(scale);
        // ������������
        _scaleFactor *= scale;
    }
    //��������״̬
    void update(float dt);
    //ת������״̬
    void switchstage();
    Size getcontentSize();
    //�õ���Ⱥ���ٳɳ�
    void plusspeed()
    {
        growspeed = 2;
        irrigatetime = 3.1;
    }
    //���ݻ�
    void damage();
    //��ȡ����״̬
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
    bool ifgrow;    //�Ƿ�Ϊ�ɳ�״̬
    int growspeed;    //�ɳ��ٶ�
    bool ifripe;    //�Ƿ����
    bool ifwithered;   //�Ƿ��ή
    float irrigatetime = 0.0;
    void Disappear();
    void removeThis();
    void switchwithered();
    Size _originalContentSize; // ԭʼ���ݴ�С
    float _scaleFactor; // ��������
};

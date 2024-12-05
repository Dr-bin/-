#pragma once
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
//ԭ��ֲ���࣬�ĸ��������ĸ���ʾ
class Plant : public cocos2d::Node
{
public:

    // ����ֲ��ʵ��
    static Plant* create(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    // ��ʼ��ֲ��
    bool init(const string& springSprite, const string& summerSprite,
        const string& autumnSprite, const string& winterSprite);
    void updateSeasons(float dt);
    // ����ֲ��ļ�����ʾ
    void switchSeason(int season);
    // ��������ֵ
    void damage(int amount);
private:
    Sprite* _spriteSpring;
    Sprite* _spriteSummer;
    Sprite* _spriteAutumn;
    Sprite* _spriteWinter;
    Sprite* _currentSprite; // ��ǰ��ʾ�ľ���
    int _health;
    int _currentSeason;
    float switchtime = 1.0f;    //���ڸ����ʱ��
    bool _isTregger;
    // �����º���ʧ�Ķ���
    void fallDownAndDisappear();
    // �Ƴ�����ĺ���
    void removeThis();
};
//��ʯ�࣬���Ա�����
class Mineral : public cocos2d::Node 
{
public:
    // ������ʯʵ��
    static Mineral* create(const string& spriteFile);
    // ��ʼ����ʯ
    bool init(const string& spriteFile);
    // ��������ֵ
    void damage(int amount);
private:
    Sprite* _sprite;
    int _health;
    int _state;    //��ʯ��״̬��0Ϊ���ƻ���1Ϊ����
    // ���ɿ�ʯ
    void Disappear();
    //�Ƴ�����
    void removeThis();
};
//�����࣬���Գɳ�
class Crop : public cocos2d::Node
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
    //��������״̬
    void updatastage(float dt);
    //ת������״̬
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
    bool ifgrow;    //�Ƿ�Ϊ�ɳ�״̬
    bool ifripe;    //�Ƿ����
    bool ifwithered;   //�Ƿ��ή
    void Disappear();
    void Pick();
    void removeThis();
};

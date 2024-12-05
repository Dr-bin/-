#pragma once
#include "cocos2d.h"

USING_NS_CC;

// ʹ��ʾ��
// ����ĳ�������ĳ�������У�
// MC = CharacterAnimation::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MC); // ��������һ���̳���Node������
// MC�ǳ������д�����һ����Ա���������;���CharacterAnimation*

class CharacterAnimation : public Sprite
{
public:
    // ��Ա���������ڴ洢�����;���
    Sprite* CharacterD = nullptr;
    Sprite* CharacterL = nullptr;
    Sprite* CharacterU = nullptr;
    Sprite* CharacterR = nullptr;
    Sprite* CharacterDstop = nullptr;
    Sprite* CharacterLstop = nullptr;
    Sprite* CharacterUstop = nullptr;
    Sprite* CharacterRstop = nullptr;

    static CharacterAnimation* create(const std::string& plistFile, float frameDuration, float scale, const Vec2& position)
    {
        auto ret = new (std::nothrow) CharacterAnimation();
        if (ret && ret->init(plistFile, frameDuration, scale, position))
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

    bool init(const std::string& plistFile, float frameDuration, float scale, const Vec2& position)
    {
        if (!Node::init())
        {
            return false;
        }

        // ��ȡSpriteFrameCacheʵ������Ӿ���֡
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile(plistFile);

        // �����洢SpriteFrameָ�������
        Vector<SpriteFrame*> rightFrames;
        Vector<SpriteFrame*> downFrames;
        Vector<SpriteFrame*> leftFrames;
        Vector<SpriteFrame*> upFrames;


        // Ϊÿһ֡�������Ʋ���ӵ�������
        char name[15];
        for (int i = 1; i <= 4; ++i)
        {
            sprintf(name, "AMoveD-%d.png", i);
            downFrames.pushBack(cache->getSpriteFrameByName(name));
        }
        for (int i = 1; i <= 4; ++i)
        {
            sprintf(name, "AMoveR-%d.png", i);
            rightFrames.pushBack(cache->getSpriteFrameByName(name));
        }
        for (int i = 1; i <= 4; ++i)
        {
            sprintf(name, "AMoveU-%d.png", i);
            upFrames.pushBack(cache->getSpriteFrameByName(name));
        }
        for (int i = 1; i <= 4; ++i)
        {
            sprintf(name, "AMoveL-%d.png", i);
            leftFrames.pushBack(cache->getSpriteFrameByName(name));
        }

        // ����������Ϊÿ������
        auto downAnimation = Animation::createWithSpriteFrames(downFrames, frameDuration);
        auto rightAnimation = Animation::createWithSpriteFrames(rightFrames, frameDuration);
        auto leftAnimation = Animation::createWithSpriteFrames(leftFrames, frameDuration);
        auto upAnimation = Animation::createWithSpriteFrames(upFrames, frameDuration);

        // ��������������Ϊÿ������
        auto downAnimate = Animate::create(downAnimation);
        auto rightAnimate = Animate::create(rightAnimation);
        auto leftAnimate = Animate::create(leftAnimation);
        auto upAnimate = Animate::create(upAnimation);

        // �������鲢��ӵ���ǰ�ڵ㣨����������ࣩ
        CharacterD = Sprite::createWithSpriteFrameName("AMoveD-1.png");
        this->addChild(CharacterD);
        CharacterL = Sprite::createWithSpriteFrameName("AMoveL-1.png");
        this->addChild(CharacterL);
        CharacterU = Sprite::createWithSpriteFrameName("AMoveU-1.png");
        this->addChild(CharacterU);
        CharacterR = Sprite::createWithSpriteFrameName("AMoveR-1.png");
        this->addChild(CharacterR);

        CharacterDstop = Sprite::createWithSpriteFrameName("AMoveD-1.png");
        this->addChild(CharacterDstop);
        CharacterLstop = Sprite::createWithSpriteFrameName("AMoveL-1.png");
        this->addChild(CharacterLstop);
        CharacterUstop = Sprite::createWithSpriteFrameName("AMoveU-1.png");
        this->addChild(CharacterUstop);
        CharacterRstop = Sprite::createWithSpriteFrameName("AMoveR-1.png");
        this->addChild(CharacterRstop);

        CharacterD->setVisible(false);
        CharacterL->setVisible(false);
        CharacterU->setVisible(false);
        CharacterR->setVisible(false);
        CharacterLstop->setVisible(false);
        CharacterUstop->setVisible(false);
        CharacterRstop->setVisible(false);


        // ���þ����λ�á����ű����Ͷ���
        CharacterL->setPosition(position);
        CharacterD->setPosition(position);
        CharacterU->setPosition(position);
        CharacterR->setPosition(position);
        CharacterDstop->setPosition(position);
        CharacterLstop->setPosition(position);
        CharacterUstop->setPosition(position);
        CharacterRstop->setPosition(position);

        CharacterL->setScale(scale);
        CharacterD->setScale(scale);
        CharacterU->setScale(scale);
        CharacterR->setScale(scale);
        CharacterDstop->setScale(scale);
        CharacterLstop->setScale(scale);
        CharacterUstop->setScale(scale);
        CharacterRstop->setScale(scale);

        CharacterD->runAction(RepeatForever::create(downAnimate));
        CharacterL->runAction(RepeatForever::create(leftAnimate));
        CharacterU->runAction(RepeatForever::create(upAnimate));
        CharacterR->runAction(RepeatForever::create(rightAnimate));

        return true;
    }

    void StopMove()
    {
        //CharacterD->setVisible(false);
        //CharacterL->setVisible(false);
        //CharacterU->setVisible(false);
        //CharacterR->setVisible(false);
        //CharacterDstop->setVisible(false);
        //CharacterLstop->setVisible(false);
        //CharacterUstop->setVisible(false);
        //CharacterRstop->setVisible(false);

        //switch (dir)
        //{
        //    case 1:
        //        CharacterDstop->setVisible(true);
        //        break;
        //    case 2:
        //        CharacterLstop->setVisible(true);
        //        break;
        //    case 3:
        //        CharacterUstop->setVisible(true);
        //        break;
        //    case 4:
        //        CharacterRstop->setVisible(true);
        //        break;
        //    default:
        //        break;
        //}

        if (CharacterD->isVisible()) {
            CharacterD->setVisible(false);
            CharacterDstop->setVisible(true);
        }
        else if (CharacterL->isVisible()) {
            CharacterL->setVisible(false);
            CharacterLstop->setVisible(true);
        }
        else if (CharacterU->isVisible()) {
            CharacterU->setVisible(false);
            CharacterUstop->setVisible(true);
        }
        else if (CharacterR->isVisible()) {
            CharacterR->setVisible(false);
            CharacterRstop->setVisible(true);
        }
        

        return;
    }

    //dir=1,2,3,4:��������
    void Move(int dir)
    {

        CharacterD->setVisible(false);
        CharacterL->setVisible(false);
        CharacterU->setVisible(false);
        CharacterR->setVisible(false);
        CharacterDstop->setVisible(false);
        CharacterLstop->setVisible(false);
        CharacterUstop->setVisible(false);
        CharacterRstop->setVisible(false);

        switch (dir)
        {
            case 1:
                CharacterD->setVisible(true);
                break;
            case 2:
                CharacterL->setVisible(true);
                break;
            case 3:
                CharacterU->setVisible(true);
                break;
            case 4:
                CharacterR->setVisible(true);
                break;
            default:
                break;
        }
        
        return;
    }

};


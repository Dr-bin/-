#pragma once
#include "cocos2d.h"

USING_NS_CC;

#if 1

class CharacterAnimation : public Node
{
public:
    // ��Ա���������ڴ洢�����;���
    bool isMoving = 0;

    Animation* downAnimation = nullptr;
    Animation* rightAnimation = nullptr;
    Animation* leftAnimation = nullptr;
    Animation* upAnimation = nullptr;

    Animate* downAnimate = nullptr;
    Animate* rightAnimate = nullptr;
    Animate* leftAnimate = nullptr;
    Animate* upAnimate = nullptr;

    Sprite* Character = nullptr;

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
        downAnimation = Animation::createWithSpriteFrames(downFrames, frameDuration);
        rightAnimation = Animation::createWithSpriteFrames(rightFrames, frameDuration);
        leftAnimation = Animation::createWithSpriteFrames(leftFrames, frameDuration);
        upAnimation = Animation::createWithSpriteFrames(upFrames, frameDuration);

        // ��������������Ϊÿ������
        downAnimate = Animate::create(downAnimation);
        rightAnimate = Animate::create(rightAnimation);
        leftAnimate = Animate::create(leftAnimation);
        upAnimate = Animate::create(upAnimation);

        // �������鲢��ӵ���ǰ�ڵ㣨����������ࣩ
        Character = Sprite::createWithSpriteFrameName("AMoveD-1.png");
        this->addChild(Character);

        // ���þ����λ�á����ű����Ͷ���
        Character->setPosition(position);
        Character->setScale(scale);
        //AMoveL();

        return true;
    }

    //���ô˺�����Ҫ��һ������Ҳ����wasd����һ���������������Ҫ��֤��wasd��������ֵ�һ��
    void StopMove(int dir)
    {
        Character->stopAction(downAnimate);
        isMoving = 0;
        return;
    }

    void AMoveL()
    {
        CCLOG("0x%p", this);
        isMoving = 1;
        Character->runAction(RepeatForever::create(leftAnimate));
        return;
    }

};

// ʹ��ʾ��
// ����ĳ�������ĳ�������У�
// auto MovableCharacter = MovableCharacter::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MovableCharacter); // ��������һ���̳���Node������


#endif



//// CharacterAnimation.h
//#ifndef CHARACTERANIMATION_H
//#define CHARACTERANIMATION_H
//
//#include "cocos2d.h"
//
//class CharacterAnimation : public Node
//{
//public:
//    static CharacterAnimation* create(Sprite* characterSprite, const std::string& animationNamePrefix, int numberOfFrames, float frameInterval);
//
//    bool init(Sprite* characterSprite, const std::string& animationNamePrefix, int numberOfFrames, float frameInterval);
//
//    void playAnimation();
//    void stopAnimation();
//    bool isAnimationPlaying() const;
//
//private:
//    Sprite* _characterSprite;
//    Animation* _animation;
//    Animate* _animateAction;
//    bool _isPlaying;
//};
//
//#endif // CHARACTERANIMATION_H
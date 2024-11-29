#pragma once
#include "cocos2d.h"

USING_NS_CC;

#if 1

class CharacterAnimation : public Node
{
public:
    // 成员变量，用于存储动画和精灵
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

        // 获取SpriteFrameCache实例并添加精灵帧
        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile(plistFile);

        // 创建存储SpriteFrame指针的向量
        Vector<SpriteFrame*> rightFrames;
        Vector<SpriteFrame*> downFrames;
        Vector<SpriteFrame*> leftFrames;
        Vector<SpriteFrame*> upFrames;


        // 为每一帧生成名称并添加到向量中
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

        // 创建动画（为每个方向）
        downAnimation = Animation::createWithSpriteFrames(downFrames, frameDuration);
        rightAnimation = Animation::createWithSpriteFrames(rightFrames, frameDuration);
        leftAnimation = Animation::createWithSpriteFrames(leftFrames, frameDuration);
        upAnimation = Animation::createWithSpriteFrames(upFrames, frameDuration);

        // 创建动画动作（为每个方向）
        downAnimate = Animate::create(downAnimation);
        rightAnimate = Animate::create(rightAnimation);
        leftAnimate = Animate::create(leftAnimation);
        upAnimate = Animate::create(upAnimation);

        // 创建精灵并添加到当前节点（即这个管理类）
        Character = Sprite::createWithSpriteFrameName("AMoveD-1.png");
        this->addChild(Character);

        // 设置精灵的位置、缩放比例和动画
        Character->setPosition(position);
        Character->setScale(scale);
        //AMoveL();

        return true;
    }

    //调用此函数需要给一个方向，也就是wasd其中一个，而且这个函数要保证是wasd中最后松手的一个
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

// 使用示例
// 在你的场景或层的某个方法中：
// auto MovableCharacter = MovableCharacter::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MovableCharacter); // 假设你在一个继承自Node的类中


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
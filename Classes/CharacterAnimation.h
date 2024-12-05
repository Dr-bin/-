#pragma once
#include "cocos2d.h"

USING_NS_CC;

// 使用示例
// 在你的场景或层的某个方法中：
// MC = CharacterAnimation::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MC); // 假设你在一个继承自Node的类中
// MC是场景类中创建的一个成员变量，类型就是CharacterAnimation*

class CharacterAnimation : public Sprite
{
public:
    // 成员变量，用于存储动画和精灵
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
        auto downAnimation = Animation::createWithSpriteFrames(downFrames, frameDuration);
        auto rightAnimation = Animation::createWithSpriteFrames(rightFrames, frameDuration);
        auto leftAnimation = Animation::createWithSpriteFrames(leftFrames, frameDuration);
        auto upAnimation = Animation::createWithSpriteFrames(upFrames, frameDuration);

        // 创建动画动作（为每个方向）
        auto downAnimate = Animate::create(downAnimation);
        auto rightAnimate = Animate::create(rightAnimation);
        auto leftAnimate = Animate::create(leftAnimation);
        auto upAnimate = Animate::create(upAnimation);

        // 创建精灵并添加到当前节点（即这个管理类）
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


        // 设置精灵的位置、缩放比例和动画
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

    //dir=1,2,3,4:下左上右
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


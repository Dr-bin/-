//#include "CharacterAnimation.h"
//#include "cocos2d.h"
//
//USING_NS_CC;
//
//CharacterAnimation* CharacterAnimation::create(Sprite* characterSprite, const std::string& animationNamePrefix, int numberOfFrames, float frameInterval)
//{
//    auto ret = new (std::nothrow) CharacterAnimation();
//    if (ret && ret->init(characterSprite, animationNamePrefix, numberOfFrames, frameInterval))
//    {
//        ret->autorelease();
//        return ret;
//    }
//    else
//    {
//        delete ret;
//        ret = nullptr;
//        return nullptr;
//    }
//}
//
//bool CharacterAnimation::init(Sprite* characterSprite, const std::string& animationNamePrefix, int numberOfFrames, float frameInterval)
//{
//    _characterSprite = characterSprite;
//    _isPlaying = false;
//
//    // 加载动画
//    Vector<SpriteFrame*> animationFrames;
//    for (int i = 1; i <= numberOfFrames; ++i)
//    {
//        auto frameName = StringUtils::format("%s-%d.png", animationNamePrefix.c_str(), i);//名字只写-前面的
//        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
//        if (frame)
//        {
//            animationFrames.pushBack(frame);
//        }
//        else
//        {
//            CCLOG("Failed to load animation frame: %s", frameName.c_str());
//            return false;
//        }
//    }
//
//    // 创建动画
//    _animation = Animation::createWithSpriteFrames(animationFrames, frameInterval);
//    _animateAction = Animate::create(_animation);
//
//    return true;
//}
//
//void CharacterAnimation::playAnimation()
//{
//    if (_characterSprite && !_isPlaying)
//    {
//        _characterSprite->runAction(RepeatForever::create(_animateAction));
//        _isPlaying = true;
//    }
//}
//
//void CharacterAnimation::stopAnimation()
//{
//    if (_characterSprite && _isPlaying)
//    {
//        _characterSprite->stopAction(_animateAction);
//        _isPlaying = false;
//    }
//    // Note: In this simple example, we didn't actually tag the action. In a real-world scenario, you should tag the action
//    // when you run it so that you can stop it later by tag. For simplicity, we'll omit this here.
//    // Instead, you might want to use a different method to stop the animation, such as keeping a reference to the action
//    // and calling `_characterSprite->stopAction(_animateAction);`.
//}
//
//bool CharacterAnimation::isAnimationPlaying() const
//{
//    return _isPlaying;
//}

#include "CharacterAnimation.h"

CharacterAnimation* CharacterAnimation::create(const std::string& plistFile, float frameDuration, float scale, const Vec2& position)
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

bool CharacterAnimation::init(const std::string& plistFile, float frameDuration, float scale, const Vec2& position)
{
    if (!Node::init())
    {
        return false;
    }

    // 获取SpriteFrameCache实例并添加精灵帧
    cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile(plistFile);
    Acache = AnimationCache::getInstance();

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

    Acache->addAnimation(downAnimation, "moveDown");
    Acache->addAnimation(rightAnimation, "moveRight");
    Acache->addAnimation(leftAnimation, "moveLeft");
    Acache->addAnimation(upAnimation, "moveUp");
    Chara = Sprite::createWithSpriteFrameName("AMoveD-2.png");
    Chara->setPosition(position);
    Chara->setScale(scale);
    this->addChild(Chara);

    // 创建动画动作（为每个方向）
    auto downAnimate = Animate::create(downAnimation);
    auto rightAnimate = Animate::create(rightAnimation);
    auto leftAnimate = Animate::create(leftAnimation);
    auto upAnimate = Animate::create(upAnimation);

    //以下是监听器部分,注释部分还没有实际功能
    auto keyboardListener = EventListenerKeyboard::create();
    //auto mouseListener = EventListenerMouse::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(CharacterAnimation::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CharacterAnimation::onKeyReleased, this);
    //mouseListener->onMouseDown = CC_CALLBACK_1(CharacterAnimation::onMouseDown, this);
    //mouseListener->onMouseUp = CC_CALLBACK_1(CharacterAnimation::onMouseUp, this);
    //mouseListener->onMouseMove = CC_CALLBACK_1(CharacterAnimation::onMouseMove, this);
    //mouseListener->onMouseScroll = CC_CALLBACK_1(CharacterAnimation::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    this->scheduleUpdate();//每帧调用update


    return true;
}

void CharacterAnimation::Move(int dir) {
    if (MoveDir)//如果在移动就不动
        return;
    switch (dir)
    {
        case 1:
            MoveDir = 1;
            Chara->runAction(RepeatForever::create(Animate::create(Acache->getAnimation("moveUp"))));
            break;
        case 2:
            MoveDir = 2;
            Chara->runAction(RepeatForever::create(Animate::create(Acache->getAnimation("moveDown"))));
            break;
        case 3:
            MoveDir = 3;
            Chara->runAction(RepeatForever::create(Animate::create(Acache->getAnimation("moveLeft"))));
            break;
        case 4:
            MoveDir = 4;
            Chara->runAction(RepeatForever::create(Animate::create(Acache->getAnimation("moveRight"))));
            break;
        default:
            break;
    }

    return;
}
void CharacterAnimation::StopMove(){
    if (!MoveDir)
        return;
    Chara->stopAllActions();
    switch (MoveDir)
    {
        case 1:
            Chara->setSpriteFrame(cache->getSpriteFrameByName("AMoveU-2.png"));
            break;
        case 2:
            Chara->setSpriteFrame(cache->getSpriteFrameByName("AMoveD-2.png"));
            break;
        case 3:
            Chara->setSpriteFrame(cache->getSpriteFrameByName("AMoveL-2.png"));
            break;
        case 4:
            Chara->setSpriteFrame(cache->getSpriteFrameByName("AMoveR-2.png"));
            break;
        default:
            break;
    }
    MoveDir = 0;
    return;
}

void CharacterAnimation::update(float delta)
{
    WASDisP_num = 0;
    WASDisP_num += isKeySPressed;
    WASDisP_num += isKeyAPressed;
    WASDisP_num += isKeyWPressed;
    WASDisP_num += isKeyDPressed;
    if (WASDisP_num != 1) {//多于两个按键按下或无按下按键时停止不动
        this->StopMove();
        return;
    }
    //上下左右
    if (isKeyWPressed) {
        this->Move(1);
        this->runAction(MoveBy::create(0.1f, Vec2(0, 3)));
    }
    if (isKeySPressed) {
        this->Move(2);
        this->runAction(MoveBy::create(0.1f, Vec2(0, -3)));
    }
    if (isKeyAPressed) {
        this->Move(3);
        this->runAction(MoveBy::create(0.1f, Vec2(-3, 0)));
    }
    if (isKeyDPressed) {
        this->Move(4);
        this->runAction(MoveBy::create(0.1f, Vec2(3, 0)));
    }
    return;
}

void CharacterAnimation::onMouseDown(EventMouse* event)
{
    EventMouse::MouseButton button = event->getMouseButton();
    auto location = event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
        isMouseButtonLeftPressed = true;
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = true;
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void CharacterAnimation::onMouseUp(EventMouse* event)
{
    EventMouse::MouseButton button = event->getMouseButton();
    auto location = event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
        isMouseButtonLeftPressed = false;
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = false;
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void CharacterAnimation::onMouseMove(EventMouse* event)
{
    auto location = event->getLocation();
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void CharacterAnimation::onMouseScroll(EventMouse* event)
{
    MouseScrollX = event->getScrollX();
    MouseScrollY = event->getScrollX();
}
void CharacterAnimation::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    bool state = true;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        isKeyWPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        isKeySPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        isKeyAPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        isKeyDPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
        isKeySPACEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        isKeyESCAPEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
        isKeyENTERPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
        isKeyBACKSPACEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_0)
        isKey_0_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_1)
        isKey_1_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_2)
        isKey_2_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_3)
        isKey_3_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_4)
        isKey_4_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_5)
        isKey_5_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_6)
        isKey_6_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_7)
        isKey_7_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_8)
        isKey_8_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_9)
        isKey_9_Pressed = state;
}
void CharacterAnimation::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    bool state = false;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        isKeyWPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        isKeySPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        isKeyAPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        isKeyDPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
        isKeySPACEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
        isKeyESCAPEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
        isKeyENTERPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
        isKeyBACKSPACEPressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_0)
        isKey_0_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_1)
        isKey_1_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_2)
        isKey_2_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_3)
        isKey_3_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_4)
        isKey_4_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_5)
        isKey_5_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_6)
        isKey_6_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_7)
        isKey_7_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_8)
        isKey_8_Pressed = state;
    if (keyCode == EventKeyboard::KeyCode::KEY_9)
        isKey_9_Pressed = state;
}
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

Vec2 CharacterAnimation::getCharacterPosition() {
    return this->CharacterD->getPosition();
}

bool CharacterAnimation::init(const std::string& plistFile, float frameDuration, float scale, const Vec2& position)
{
    if (!Node::init())
    {
        return false;
    }
    body = PhysicsBody::createBox(Size(30, 30));
    this->setPhysicsBody(body);
    body->setRotationEnable(false);
    body->setPositionOffset(Vec2(position.x, position.y-20));
    body->setCollisionBitmask(0x00000001);
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
    //CharacterDstop->setVisible(false);
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


    //以下是监听器部分,注释部分还没有实际功能
    auto keyboardListener = EventListenerKeyboard::create();
    auto mouseListener = EventListenerMouse::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(CharacterAnimation::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CharacterAnimation::onKeyReleased, this);
    //mouseListener->onMouseDown = CC_CALLBACK_1(CharacterAnimation::onMouseDown, this);
    //mouseListener->onMouseUp = CC_CALLBACK_1(CharacterAnimation::onMouseUp, this);
    //mouseListener->onMouseMove = CC_CALLBACK_1(CharacterAnimation::onMouseMove, this);
    //mouseListener->onMouseScroll = CC_CALLBACK_1(CharacterAnimation::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    auto contactlistener=EventListenerPhysicsContact::create();
    contactlistener->onContactBegin = CC_CALLBACK_1(CharacterAnimation::onContactBegin, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactlistener, this);
    this->scheduleUpdate();//每帧调用update


    return true;
}

bool CharacterAnimation::onContactBegin(PhysicsContact& contact)
{
    this->StopMove();
    log("onContactBegin");
    return true;
}
void CharacterAnimation::Move(int dir) {

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
            CharacterU->setVisible(true);
            break;
        case 2:
            CharacterD->setVisible(true);
            break;
        case 3:
            CharacterL->setVisible(true);
            break;
        case 4:
            CharacterR->setVisible(true);
            break;
        default:
            break;
    }
    return;
}
void CharacterAnimation::StopMove()
{
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
    this->body->setVelocity(Vec2(0, 0));
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
        this->runAction(MoveBy::create(0.01f, Vec2(0, 4.0)));
    }
    if (isKeySPressed) {
        this->Move(2);
        this->runAction(MoveBy::create(0.01f, Vec2(0, -4.0)));
    }
    if (isKeyAPressed) {
        this->Move(3);
        this->runAction(MoveBy::create(0.01f, Vec2(-4.0, 0)));
    }
    if (isKeyDPressed) {
        this->Move(4);
        this->runAction(MoveBy::create(0.01f, Vec2(4.0, 0)));
    }
    return;
}


void CharacterAnimation::onMouseDown(EventMouse* event)
{

    EventMouse::MouseButton button = event->getMouseButton();
    auto locate= event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
        isMouseButtonLeftPressed = true;
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = true;
   
   
    auto x = event->getCursorX();
    auto y = event->getCursorY();
    if(!(x>=680 && x<=1160 && y>=180 && y<=225))
       useTool();
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

char CharacterAnimation::get_facing()
{
    try {
        if (CharacterD->isVisible()||CharacterDstop->isVisible())
            return 'D';
        else if (CharacterL->isVisible()||CharacterLstop->isVisible())
            return 'L';
        else if (CharacterU->isVisible()||CharacterUstop->isVisible())
            return 'U';
        else if (CharacterR->isVisible()||CharacterRstop->isVisible())
            return 'R';
    }
    catch (...) {
        log("error");
        return 'N';
    }
    return 0;
}

void CharacterAnimation::useAxeToLeft() {
    auto axe = Sprite::create("tools/axe.png");
    axe->setScale(0.8);
    axe->setPosition(this->getCharacterPosition().x-20, this->getCharacterPosition().y-10);
    auto axeRotate = RotateBy::create(0.3, -50);
    auto axeRemove = RemoveSelf::create();
    auto seq = Sequence::create(axeRotate, axeRemove, nullptr);
    this->addChild(axe);
    axe->runAction(seq);
    this->axeTimes++;
}
void CharacterAnimation::useAxeToRight() {
    auto axe = Sprite::create("tools/axe.png");
   axe->setScaleX(-0.8);
    axe->setScaleY(0.8);
    axe->setPosition(this->getCharacterPosition().x+20, this->getCharacterPosition().y-10);
    auto axeRotate = RotateBy::create(0.3, 50);
    auto axeRemove = RemoveSelf::create();
    auto seq = Sequence::create(axeRotate, axeRemove, nullptr);
    this->addChild(axe);
    axe->runAction(seq);
    axeTimes++;
}

void CharacterAnimation::usePickToLeft()
{
    auto pick = Sprite::create("tools/pick.png");
    pick->setScale(0.8);
    pick->setPosition(this->getCharacterPosition().x-20, this->getCharacterPosition().y-10);
    auto pickRotate = RotateBy::create(0.3, -50);
    auto pickRemove = RemoveSelf::create();
    auto seq = Sequence::create(pickRotate, pickRemove, nullptr);
    this->addChild(pick);
    pick->runAction(seq);
    pickTimes++;
}

void CharacterAnimation::usePickToRight()
{
    auto pick = Sprite::create("tools/pick.png");
    pick->setScaleX(-0.8);
    pick->setScaleY(0.8);
    pick->setPosition(this->getCharacterPosition().x+20, this->getCharacterPosition().y-10);
    auto pickRotate = RotateBy::create(0.3, 50);
    auto pickRemove = RemoveSelf::create();
    auto seq = Sequence::create(pickRotate, pickRemove, nullptr);
    this->addChild(pick);
    pick->runAction(seq);
    pickTimes++;
}

void CharacterAnimation::useHoeToLeft()
{
    auto hoe = Sprite::create("tools/hoe.png");
    hoe->setScale(0.8);
    hoe->setPosition(this->getCharacterPosition().x-20, this->getCharacterPosition().y-10);
    auto hoeRotate = RotateBy::create(0.3, -50);
    auto hoeRemove = RemoveSelf::create();
    auto seq = Sequence::create(hoeRotate, hoeRemove, nullptr);
    this->addChild(hoe);
    hoe->runAction(seq);
    hoeTimes++;
}

void CharacterAnimation::useHoeToRight()
{
    auto hoe = Sprite::create("tools/hoe.png");
    hoe->setScaleX(-0.8);
    hoe->setScaleY(0.8);
    hoe->setPosition(this->getCharacterPosition().x+20, this->getCharacterPosition().y-10);
    auto hoeRotate = RotateBy::create(0.3, 50);
    auto hoeRemove = RemoveSelf::create();
    auto seq = Sequence::create(hoeRotate, hoeRemove, nullptr);
    this->addChild(hoe);
    hoe->runAction(seq);
    hoeTimes++;
}
void CharacterAnimation::fetchWaterToLeft()
{
    auto water = Sprite::create("tools/bucket.png");
    water->setScale(0.8);
    water->setPosition(this->getCharacterPosition().x-20, this->getCharacterPosition().y-10);
    auto waterRotate = RotateBy::create(0.3, -50);
    auto waterRemove = RemoveSelf::create();
    auto seq = Sequence::create(waterRotate, waterRemove, nullptr);
    this->addChild(water);
    water->runAction(seq);
}

void CharacterAnimation::fetchWaterToRight()
{
    auto water = Sprite::create("tools/bucket.png");
    water->setScaleX(-0.8);
    water->setScaleY(0.8);
    water->setPosition(this->getCharacterPosition().x+20, this->getCharacterPosition().y-10);
    auto waterRotate = RotateBy::create(0.3, 50);
    auto waterRemove = RemoveSelf::create();
    auto seq = Sequence::create(waterRotate, waterRemove, nullptr);
    this->addChild(water);
    water->runAction(seq);
}

void CharacterAnimation::fishingToLeft()
{
    auto fishing = Sprite::create("tools/fishing_rod.png");
    fishing->setScale(1.2);
    fishing->setPosition(this->getCharacterPosition().x-20, this->getCharacterPosition().y-10);
    auto fishingRotate = RotateBy::create(0.3, -50);
    auto fishingRemove = RemoveSelf::create();
    auto seq = Sequence::create(fishingRotate, fishingRemove, nullptr);
    this->addChild(fishing);
    fishing->runAction(seq);
    fishTimes++;
}

void CharacterAnimation::fishingToRight()
{
    auto fishing = Sprite::create("tools/fishing_rod.png");
    fishing->setScaleX(-1.2);
    fishing->setScaleY(1.2);
    fishing->setPosition(this->getCharacterPosition().x+20, this->getCharacterPosition().y-10);
    auto fishingRotate = RotateBy::create(0.3, 50);
    auto fishingRemove = RemoveSelf::create();
    auto seq = Sequence::create(fishingRotate, fishingRemove, nullptr);
    this->addChild(fishing);
    fishing->runAction(seq);
    fishTimes++;
}

void CharacterAnimation::useTool()
{
    char facing = get_facing();
    if (facing == 'D' || facing == 'L') {
        switch (this->now_item) {
        case 1:
            useAxeToLeft();
            exp[2]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        case 2:
            useHoeToLeft();
            exp[0]++;
            DataProvider::getInstance()->setEXData(exp);
       
            break;
        case 3:
            usePickToLeft();
            exp[1]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        case 4:
            fetchWaterToLeft();
            break;
        case 12:
            fishingToLeft();
            exp[3]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        default:
            break;
        }
    }
    else if (facing == 'U' || facing == 'R') {
        switch (this->now_item) {
        case 1:
            useAxeToRight();
            exp[2]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        case 2:
            useHoeToRight();
            exp[0]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        case 3:
            usePickToRight();
            exp[1]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        case 4:
            fetchWaterToRight();
            break;
        case 12:
            fishingToRight();
            exp[3]++;
            DataProvider::getInstance()->setEXData(exp);
            break;
        default:
            break;
        }
    }
}




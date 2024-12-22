#include "NPC.h"


bool NPC::init(Vec2 startPosition) {
    if (!Node::init())
        return false;
    scheduleUpdate();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_plistFile);

    setImages();
    createAnimations();

    _startPosition = startPosition;
    _currentPosition = _startPosition;
    _isAlive = true;

    _moveUpSprite->setVisible(false);
    _moveLeftSprite->setVisible(false);
    _moveDownSprite->setVisible(false);

    //设置大小为两倍
    _moveUpSprite->setScale(2.0);
    _moveLeftSprite->setScale(2.0);
    _moveDownSprite->setScale(2.0);
    _moveRightSprite->setScale(2.0);

    addChild(_moveRightSprite);
    addChild(_moveUpSprite);
    addChild(_moveLeftSprite);
    addChild(_moveDownSprite);

    MaxFriendshipLevel = 4;
    _currentSprite = _moveRightSprite;
    _moveCount = 0;
    _isAlive = true;
    _currentFrame = 0;
    auto label0 = Label::createWithSystemFont("Hello, Cocos2d-x!", "Arial", FRONTSIZE);
    label0->setVisible(false);
    this->addChild(label0);
    labels.pushBack(label0);

    auto label1 = Label::createWithSystemFont("NICE TO MEET YOU!", "Arial", FRONTSIZE);
    label1->setVisible(false);
    this->addChild(label1);
    labels.pushBack(label1);

    auto label2 = Label::createWithSystemFont("HONEY，LOVE YOU~", "Arial", FRONTSIZE);
    label2->setVisible(false);
    this->addChild(label2);
    labels.pushBack(label2);

    auto label3 = Label::createWithSystemFont("DEAR,TO PLAY STARDEW VALLEY!", "Arial", FRONTSIZE);
    label3->setVisible(false);
    this->addChild(label3);
    labels.pushBack(label3);
    _currentLabel = label0;
    return true;
}

int getRandomRepeatTime()
{
    return rand() % 3 + 3;
}

void NPC::moveAround() {

    CCLOG("npc %s friendship:%f, time:%d",getNPCName().c_str(), friendship, _currentFrame);
    /*if (_moveCount >= maxMoveCount) {
        return;
    }*/
    static Vec2 distance;
    static int repeatTime1, repeatTime2;
    float animationDuraion = 4 * delayPerUnit;
    if (_moveCount % 4 == 0) {
        repeatTime1 = getRandomRepeatTime(); // 生成随机重复次数
        repeatTime2 = getRandomRepeatTime();
        float randomX = animationDuraion * repeatTime1 * speed; // 生成随机距离
        float randomY = animationDuraion * repeatTime2 * speed;
        distance = Vec2(randomX, randomY);
    }

    std::string direction;
    Vec2 moveDistance;
    auto wait = DelayTime::create(getRandomWaitTime());
    int repeatTimes = 1;
    switch (_moveCount % 4) {
        case 0:
            direction = "right";
            moveDistance = Vec2(distance.x, 0);
            repeatTimes = repeatTime1;
            _currentSprite = _moveRightSprite;
            _currentSprite->setPosition(_currentPosition);
            break;
        case 1:
            direction = "up";
            moveDistance = Vec2(0, distance.y);
            repeatTimes = repeatTime2;
            _currentSprite = this->_moveUpSprite;
            _currentSprite->setPosition(_currentPosition);
            break;
        case 2:
            direction = "left";
            moveDistance = Vec2(-distance.x, 0);
            repeatTimes = repeatTime1;
            _currentSprite = _moveLeftSprite;
            _currentSprite = _moveLeftSprite;
            _currentSprite->setPosition(_currentPosition);
            break;
        case 3:
            direction = "down";

            moveDistance = Vec2(0, -distance.y);
            repeatTimes = repeatTime2;
            _currentSprite = _moveDownSprite;
            _currentSprite->setPosition(_currentPosition);
            break;
    }

    // 停止动画
    auto stopAnimation = CallFunc::create([&]() {
        //CCLOG("stop animation");
        this->stopAllActions();
        _currentSprite->setVisible(false);
        });
    // 开始动画
    auto  startAnimation = CallFunc::create([&]() {
        //CCLOG("start animation");
        _currentSprite->setVisible(true);
        });

    std::string type = getNPCName();
    auto animation = _animationCache->getAnimation(type + "-" + direction);
    auto moveAction = MoveBy::create(animationDuraion * repeatTimes, moveDistance);
    auto animateAction = Repeat::create(Animate::create(animation), repeatTimes);
    auto spawnAction = Spawn::create(moveAction, animateAction, nullptr);
    //auto spawnAction = moveAction;

    auto moveSequence = Sequence::create(startAnimation, spawnAction, wait, stopAnimation, CallFunc::create([this]() { moveAround(); }), nullptr);

    _currentSprite->runAction(moveSequence->clone());
    _currentPosition += moveDistance;
    _moveCount++;
}

void NPC::setImages() {
    int pos = _plistFile.find_last_of('.');
    if (-1 == pos) return;
    std::string prefix = _plistFile.substr(0, pos);

    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(_plistFile);
    int frameCount = dict["frames"].asValueMap().size();
    if (frameCount == 0) return;

    for (int i = 0; i < frameCount; ++i) {
        std::string index = std::to_string(i); // 根据帧命名调整格式
        std::string frameName = prefix + "-" + index + ".png";
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            _images.pushBack(frame);
        }
    }
}

void NPC::createAnimations() {
    _animationCache = AnimationCache::getInstance();
    std::string type = getNPCName();
    // 创建上方向动画
    Vector<SpriteFrame*> upFrames;
    for (int i = 8; i <= 11; i++) {
        upFrames.pushBack(_images.at(i));
    }
    _moveUpSprite = Sprite::createWithSpriteFrame(_images.at(8));
    _animationCache->addAnimation(Animation::createWithSpriteFrames(upFrames, 0.2f, 1), type + "-up");
    // 创建下方向动画
    Vector<SpriteFrame*> downFrames;
    for (int i = 0; i <= 3; i++) {
        downFrames.pushBack(_images.at(i));
    }
    _moveDownSprite = Sprite::createWithSpriteFrame(_images.at(0));
    _animationCache->addAnimation(Animation::createWithSpriteFrames(downFrames, 0.2f, 1), type + "-down");

    // 创建左方向动画
    Vector<SpriteFrame*> leftFrames;
    for (int i = 12; i <= 15 && i < _images.size(); i++) {
        leftFrames.pushBack(_images.at(i));
    }
    _moveLeftSprite = Sprite::createWithSpriteFrame(_images.at(12));
    _animationCache->addAnimation(Animation::createWithSpriteFrames(leftFrames, 0.2f, 1), type + "-left");

    // 创建右方向动画
    Vector<SpriteFrame*> rightFrames;
    for (int i = 4; i <= 7; i++) {
        rightFrames.pushBack(_images.at(i));
    }
    _moveRightSprite = Sprite::createWithSpriteFrame(_images.at(4));
    _animationCache->addAnimation(Animation::createWithSpriteFrames(rightFrames, 0.2f, 1), type + "-right");

    // 创建趴下动画
    Vector<SpriteFrame*> lieDownFrames;
    for (int i = 16; i <= 19 && i < _images.size(); i++) {
        lieDownFrames.pushBack(_images.at(i));
    }
    _animationCache->addAnimation(Animation::createWithSpriteFrames(lieDownFrames, 0.2f), type + "-lieDown");
}

void NPC::addFriendship(int value) {
    friendship += value;
    friendship = clamp(friendship, 0., (double)MaxFriendshipLevel * FRIENDSHIP_PER_LEVEL);
    friendshipLevel = static_cast<int>(friendship / FRIENDSHIP_PER_LEVEL);
    if (friendshipLevel > 5) friendshipLevel = 5;
    updateRelationship();
}

void NPC::subtractFriendship(int value) {
    friendship -= value;
    friendship = clamp(friendship, 0., (double)MaxFriendshipLevel * FRIENDSHIP_PER_LEVEL);
    friendshipLevel = static_cast<int>(friendship / FRIENDSHIP_PER_LEVEL);
    if (friendshipLevel > 5) friendshipLevel = 5;
    updateRelationship();
}

void NPC::updateRelationship(bool isGiveFlower ) {
    if (friendshipLevel <= 2)
        _relationshipStatus = RelationshipStatus::Neutral;
    else if (friendshipLevel <= 8)
        _relationshipStatus = RelationshipStatus::Friend;
    else if (friendshipLevel <= 10)
        if (isGiveFlower)
        _relationshipStatus = RelationshipStatus::Lover;
    else
        _relationshipStatus = RelationshipStatus::Married;
}



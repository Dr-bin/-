#include"guidepost.h"
guidepost* guidepost::create(int identity)
{
    guidepost* guide = new guidepost();
    if (guide && guide->init(identity))
    {
        guide->autorelease();
        return guide;
    }
    CC_SAFE_DELETE(guide);
    return nullptr;
}

bool guidepost::init(int id)
{
    if (!Node::init())
        return false;
    if (id == 1)
        guide = Sprite::create("arrow/left.png");
    else if (id == 2)
        guide = Sprite::create("arrow/right.png");
    else if (id == 3)
        guide = Sprite::create("arrow/up.png");
    else if (id == 4)
        guide = Sprite::create("arrow/down.png");
    if (guide)
    {
        guide->setVisible(true);
        addChild(guide);
        identity = id;
        scheduleUpdate();
        _originalContentSize = guide->getContentSize();
        return true;
    }
    return false;
}

int guidepost::getidentity()
{
    return identity;
}
void guidepost::update(float dt)
{
    time += dt;
    if (time >= 1.0)
    {
        time = 0.0;
        move();
    }
}
void guidepost::move()
{
    auto toright = MoveBy::create(0.5f, Vec2(40, 0));
    auto toleft = MoveBy::create(0.5f, Vec2(-40, 0));
    auto toup = MoveBy::create(0.5f, Vec2(0, 40));
    auto todown = MoveBy::create(0.5f, Vec2(0, -40));
    auto leftse = Sequence::create(toleft, toright, nullptr);
    auto rightse = Sequence::create(toright, toleft, nullptr);
    auto upse = Sequence::create(toup, todown, nullptr);
    auto downse = Sequence::create(todown, toup, nullptr);
    if (identity == 1)
        guide->runAction(leftse);
    else if (identity == 2)
        guide->runAction(rightse);
    else if (identity == 3)
        guide->runAction(upse);
    else if (identity == 4)
        guide->runAction(downse);
}
Size guidepost::getcontentSize()
{
    // 返回缩放后的内容大小
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}
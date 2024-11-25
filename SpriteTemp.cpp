#include "SpriteTemp.h"

bool SpriteScene::init()
{
    if(!Scene::init())return false;
    Sprite* gamer = Sprite::create("Harvey_Winter.png");
    this->addChild(gamer);
    gamer->setScale(1.8f);
    gamer->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
    return true;
}

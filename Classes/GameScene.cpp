#include "GameScene.h"
#include"PopupBase.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    this->scene = Scene::createWithPhysics();
    this->scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    this->scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    item_layer = ItemLayer::create();

    auto shop1 = PopupShop::create();
    shop1->stimulateKey=EventKeyboard::KeyCode::KEY_M;
    item_layer->addChild(shop1);
    

    
    this->scene->addChild(item_layer, 500);

    map_layer = MapLayer::create();
    this->scene->addChild(map_layer, 100);
    map_layer->setMap(0);
    for (int i = 0; i < 5; i++) {
        map_layer->maps.at(i)->player = map_layer->ch;
    }
    //this->addChild(this->scene);
    auto mouse_listener = EventListenerMouse::create();
    mouse_listener->onMouseDown = CC_CALLBACK_1(ItemBag::onMouseDown, this->item_layer->item_bag,this->map_layer->ch);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse_listener, scene);
    return this->scene;
}




bool GameScene::init()
{
    if (!Scene::init())
        return false;
    return true;
}
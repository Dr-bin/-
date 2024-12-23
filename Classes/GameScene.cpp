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
    shop1->itemBag = item_layer->item_bag;
    shop1->stimulateKey=EventKeyboard::KeyCode::KEY_M;
    item_layer->addChild(shop1);
    
    auto shop2 = PopupShop::create();
    shop2->itemBag = item_layer->item_bag;
    shop2->stimulateKey = EventKeyboard::KeyCode::KEY_N;
    int shop2tags[5] = { 5,6,7,8,9 };
    shop2->changeTags(shop2tags);
    item_layer->addChild(shop2);

    auto shop3 = PopupShop::create();
    shop3->itemBag = item_layer->item_bag;
    shop3->stimulateKey = EventKeyboard::KeyCode::KEY_B;
    int shop3tags[5] = { 10,11,12,13,14 };
    shop3->changeTags(shop3tags);
    item_layer->addChild(shop3);

    Cook *cook = Cook::create();
    cook->bag = item_layer->item_bag;
    item_layer->addChild(cook,5000000);


    LevelTree* level_tree = LevelTree::create();
    item_layer->addChild(level_tree);


    this->scene->addChild(item_layer, 500);

    map_layer = MapLayer::create();
    map_layer->setMap(0);
    this->scene->addChild(map_layer, 100);
    for (int i = 0; i < 5; i++) {
        map_layer->maps.at(i)->player = map_layer->ch;
        map_layer->maps.at(i)->bag = item_layer->item_bag;
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
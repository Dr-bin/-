
#include "cocos2d.h"
#include"MyScene.h"
#include"Plantsandmineral.h"
#include"global_variable.h"
#include"maptry.h"
//#include"MouseKeyboardListener.h"

USING_NS_CC;
using namespace std;
//鼠标的回调函数
void MyScene::onMouseDown(EventMouse* event)
{
    EventMouse::MouseButton button = event->getMouseButton();
    auto location = event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
    {
        isMouseButtonLeftPressed = true;
        auto location = event->getLocation();
        EventMouse* e = (EventMouse*)event;
        float mouseX = e->getCursorX();
        float mouseY = e->getCursorY();
        // 计算方格索引
        int gridX = static_cast<int>(mouseX/ 50);
        int gridY = static_cast<int>(mouseY / 50);
        _label->setString(StringUtils::format("Mouse Position: X: %d, Y: %d",gridX,gridY));
#if 0
        if (farmland[gridY][gridX])
        {
            auto Tree_1 = Plant::create("tree1_spring.png", "tree1_summer.png", "tree1_fall.png", "tree1_winter.png");
            if (Tree_1 == nullptr)
                problemLoading("'tree1'");

            else
            {
                Tree_1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - Tree_1->getContentSize().height));
                this->addChild(Tree_1, 1);
            }
        }
#endif
    }
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = true;
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;  
}
void MyScene::onMouseUp(EventMouse* event)
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
void MyScene::onMouseMove(EventMouse* event)
{
    auto location = event->getLocation();
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void MyScene::onMouseScroll(EventMouse* event)
{
    MouseScrollX = event->getScrollX();
    MouseScrollY = event->getScrollX();
}
//键盘的回调函数
void MyScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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
    {
        isKeySPACEPressed = state;
        _tree->damage(1);
    }
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
void MyScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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
MyScene* MyScene::createScene()
{
    return create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyScene::init()
{
    farmland = new int* [gridheight];
    for (int i = 0; i < gridheight; ++i) {
        farmland[i] = new int[gridwidth]();
    }
    for (int i = 0; i < gridheight; ++i) {
        for (int j = 0; j < gridwidth; ++j) {
            farmland[i][j] = 0; // 初始化为可耕种
        }
    }
#if 1
    myscene = createWithPhysics();
    auto mymap = MapLayer::create();
    myscene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    myscene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    myscene->addChild(mymap);
    Director::getInstance()->runWithScene(myscene);
#endif
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MyScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
    auto label_xy = Label::createWithTTF("x:0;y:0", "fonts/Marker Felt.ttf", 24);
    label_xy->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height-50));

    // add the label as a child to this layer
    this->addChild(label_xy, 1);
    _label = label_xy;
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
#if 1
    auto Tree_1 = Plant::create("tree1_spring.png", "tree1_summer.png", "tree1_fall.png", "tree1_winter.png");
    if (Tree_1 == nullptr)
        problemLoading("'tree1'");
    else
    {
        Tree_1->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2-Tree_1->getContentSize().height));
        this->addChild(Tree_1, 1);
        
    }
#if 1
    auto Tree_2 = Plant::create("tree1_spring.png", "tree1_summer.png", "tree1_fall.png", "tree1_winter.png");
    if (Tree_2 == nullptr)
        problemLoading("'tree2'");
    else
    {
        Tree_2->setPosition(Vec2(origin.x + visibleSize.width / 2+40, origin.y + visibleSize.height / 2 - Tree_2->getContentSize().height));
        this->addChild(Tree_2, 1);
    }
    auto Tree_3 = Plant::create("tree1_spring.png", "tree1_summer.png", "tree1_fall.png", "tree1_winter.png");
    if (Tree_3 == nullptr)
        problemLoading("'tree3'");
    else
    {
        Tree_3->setPosition(Vec2(origin.x + visibleSize.width / 2+80, origin.y + visibleSize.height / 2 - Tree_3->getContentSize().height));
        this->addChild(Tree_3, 1);
    }
#endif 
#endif
#if 1
    auto stone = Mineral::create("tree1_spring.png");
    if (stone == nullptr)
        problemLoading("'stone'");
    else
    {
        stone->setPosition(Vec2(300,300));
        this->addChild(stone,1);
    }
    _stone = stone;
#endif
    _infoLabel = Label::createWithTTF("I LOVE WMJ", "fonts/Marker Felt.ttf", 20);
    _infoLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
    this->addChild(_infoLabel);
    auto keyboardListener = EventListenerKeyboard::create();
    auto mouseListener = EventListenerMouse::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MyScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MyScene::onKeyReleased, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(MyScene::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(MyScene::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(MyScene::onMouseMove, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(MyScene::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    return true;
}

void MyScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
void MyScene::onEnter() 
{
    Scene::onEnter();
    this->scheduleUpdate();
}
void MyScene::update(float deltaTime) 
{
    if (isKeyDPressed&&!isKeyAPressed&&!isKeyWPressed&&!isKeySPressed) 
    {
        auto toRight = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(2, 0)); // 向右移动
        _stone->runAction(toRight);
    }
    if (!isKeyDPressed && !isKeyAPressed && !isKeyWPressed && isKeySPressed)
    {
        auto toDown = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(0, -2)); // 向下移动
        _stone->runAction(toDown);
    }
    if (!isKeyDPressed && isKeyAPressed && !isKeyWPressed && !isKeySPressed)
    {
        auto toLeft = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(-2, 0)); // 向左移动
        auto toLeftl = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(-2, 0));
        _stone->runAction(toLeft);
    }
    if (!isKeyDPressed && !isKeyAPressed && isKeyWPressed && !isKeySPressed)
    {
        auto toUp = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(0, 2)); // 向上移动
        _stone->runAction(toUp);
    }
}



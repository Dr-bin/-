#include "BeginScene.h"
#include"PopupBase.h"
bool BeginScene::init()
{
	if (!Scene::init())
	return false;
	/*北京*/
	background = Sprite::create("beginscene/background.png");
	background->setScale(1.5);
	background->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(background,0);
	/*选项*/
	board1=Sprite::create("beginscene/board.png");
	board1->setPosition(700,100);
	this->addChild(board1,1);
	start = Label::create();
	start->setSystemFontSize(30);
	start->setString("START");
	start->setPosition(700, 100);
	this->addChild(start,2);
	board2=Sprite::create("beginscene/board.png");
	board2->setPosition(1200,100);
	this->addChild(board2,1);
	exit = Label::create();
	exit->setSystemFontSize(30);
	exit->setString("EXIT");
	exit->setPosition(1200, 100);
	this->addChild(exit,2);
	/*题头*/
	title=Sprite::create("beginscene/title.png");
	title->setScale(1.5);
	title->setPosition(Director::getInstance()->getVisibleSize().width / 2, 800);
	this->addChild(title,1);
	auto mouselistener = EventListenerMouse::create();
	mouselistener->onMouseDown = CC_CALLBACK_1(BeginScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, this);
	/**/
	auto pop =PopupBase::create();
	pop->stimulateKey=EventKeyboard::KeyCode::KEY_ENTER;
	this->addChild(pop,1000);
	return true;
	
}

void BeginScene::onMouseDown(EventMouse* event)
{
	int x = event->getCursorX();
	int y = event->getCursorY();
	if (x > 600 && x < 800 && y > 25 && y < 175)
	{
		auto gamescene = GameScene::create();
		Director::getInstance()->replaceScene(gamescene->createScene());
	}
}

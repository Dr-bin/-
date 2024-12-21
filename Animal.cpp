#include"Animal.h"


#include "Animal.h"

bool Animal::init(Vec2 startPosition)
{
	if (!Node::init())
		return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_plistFile);

	// 导入动画和精灵
	setImages();
	createAnimations();

	/*_startPosition = Vec2(Director::getInstance()->getVisibleSize() / 2);*/
	_startPosition = startPosition;
	_currentPosition = _startPosition;
	_isAlive = 1;

	// 设置可见
	_moveUpSprite->setVisible(false);
	_moveLeftSprite->setVisible(false);
	_moveDownSprite->setVisible(false);

	addChild(_moveRightSprite);
	addChild(_moveUpSprite);
	addChild(_moveLeftSprite);
	addChild(_moveDownSprite);

	_currentSprite = _moveRightSprite;
	_moveCount = 0;
	_isAlive = 1;
	//this->schedule(CC_SCHEDULE_SELECTOR(Animal::moveAround), 4.0f, 8, 0);
	return true;
}

void Animal::setImages()
{
	int pos = _plistFile.find_last_of('.');
	if (-1 == pos) return;
	std::string prefix = _plistFile.substr(0, pos);

	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(_plistFile);
	int frameCount = dict["frames"].asValueMap().size();
	if (frameCount == 0) return;

	for (int i = 0; i < frameCount; ++i)
	{
		std::string index = std::to_string(i); // 根据帧命名调整格式
		std::string frameName = prefix + "-" + index + ".png";
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		if (frame) {
			_images.pushBack(frame);
			//CCLOG("add frame %s", frameName.c_str());
		}
	}
}

void Animal::createAnimations()
{
	_animationCache = AnimationCache::getInstance();
	std::string type = getAnimalType();
	// 创建上方向动画
	Vector<SpriteFrame*> upFrames;
	for (int i = 8; i <= 11; i++) {
		upFrames.pushBack(_images.at(i));
	}
	_moveUpSprite = Sprite::createWithSpriteFrame(_images.at(8));
	_animationCache->addAnimation(Animation::createWithSpriteFrames(upFrames, delayPerUnit, 1), type+ "-" +"up");
	// 创建下方向动画
	Vector<SpriteFrame*> downFrames;
	for (int i = 0; i <= 3; i++) {
		downFrames.pushBack(_images.at(i));
	}
	_moveDownSprite = Sprite::createWithSpriteFrame(_images.at(0));
	_animationCache->addAnimation(Animation::createWithSpriteFrames(downFrames, delayPerUnit, 1), type + "-" + "down");

	// 创建左方向动画
	Vector<SpriteFrame*> leftFrames;
	for (int i = 12; i <= 15 && i < _images.size(); i++) {
		leftFrames.pushBack(_images.at(i));
	}
	_moveLeftSprite = Sprite::createWithSpriteFrame(_images.at(12));
	_animationCache->addAnimation(Animation::createWithSpriteFrames(leftFrames, delayPerUnit, 1), type + "-" + "left");

	// 创建右方向动画
	Vector<SpriteFrame*> rightFrames;
	for (int i = 4; i <= 7; i++) {
		rightFrames.pushBack(_images.at(i));
	}
	_moveRightSprite = Sprite::createWithSpriteFrame(_images.at(4));
	_animationCache->addAnimation(Animation::createWithSpriteFrames(rightFrames, delayPerUnit, 1), type + "-" + "right");

	// 创建趴下动画
	Vector<SpriteFrame*> lieDownFrames;
	for (int i = 16; i <= 19 && i < _images.size(); i++) {
		lieDownFrames.pushBack(_images.at(i));
	}
	_animationCache->addAnimation(Animation::createWithSpriteFrames(lieDownFrames, delayPerUnit), "lieDown");

	// 创建睡觉动画（没有必要）
	Vector<SpriteFrame*> sleepFrames;
	for (int i = 20; i <= 21 && i < _images.size(); i++) {
		sleepFrames.pushBack(_images.at(i));
	}
	_animationCache->addAnimation(Animation::createWithSpriteFrames(sleepFrames, delayPerUnit), "sleep");
}

int Animal::getRandomRepeatTime() {
	return rand() % 3 + 1;
}

float Animal::getRandomWaitTime()
{
	std::random_device rd;  // 用于生成随机种子
	std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法

	// 创建一个分布对象，指定范围
	std::uniform_real_distribution<> dis(0.5f, 3.0f);
	// 生成随机数
	return (float)dis(gen);
}

Vec2 Animal::getRandomDistance(Vec2 currentPosition, const std::string& direction)
{
	std::random_device rd;  // 用于生成随机种子
	std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法
	if (direction == "right") {
		std::uniform_real_distribution<> dis(0.0f, _width-currentPosition.x);
		return Vec2(dis(gen), 0);
	}
	else if (direction == "up") {
		std::uniform_real_distribution<> dis(0.0f, _height-currentPosition.y);
		return Vec2(0, dis(gen));
	}
	else if (direction == "left") {
		std::uniform_real_distribution<> dis(0.0f, currentPosition.x);
		return Vec2(-dis(gen), 0);
	}
	else if (direction == "down") {
		std::uniform_real_distribution<> dis(0.0f, currentPosition.y);
		return Vec2(0, -dis(gen));
	}
	return Vec2(0, 0);
}


void Animal::moveAround() {
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
		CCLOG("stop animation");
		this->stopAllActions();
		_currentSprite->setVisible(false);
		});
	// 开始动画
	auto  startAnimation = CallFunc::create([&]() {
		CCLOG("start animation");
		_currentSprite->setVisible(true);
		});

	std::string type = getAnimalType();
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




//Dog
//bool Dog::init(Vec2 startPosition)
//{
//	if (!Node::init())
//		return false;
//
//	_plistFile = "dog.plist";
//	Animal::init();
//	return true;
//
//}
//Dog* Dog::create(Vec2 startPosition) {
//	Dog* dog = new Dog();
//	if (dog && dog->init(startPosition))
//	{
//		dog->autorelease();
//		return dog;
//	}
//	delete dog;
//	return nullptr;
//}
//
////Cat
//bool Cat::init(Vec2 startPosition)
//{
//	if (!Node::init())
//		return false;
//
//	_plistFile = "cat.plist";
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(_plistFile);
//	//导入动画和精灵
//	setImages();
//	createAnimations();
//
//	_startPosition = startPosition;
//	_currentPosition = _startPosition;
//	_isAlive = 1;
//
//	//设置可见
//	_moveRightSprite->setVisible(false);
//	_moveUpSprite->setVisible(false);
//	_moveLeftSprite->setVisible(false);
//	_moveDownSprite->setVisible(false);
//
//	addChild(_moveRightSprite);
//	addChild(_moveUpSprite);
//	addChild(_moveLeftSprite);
//	addChild(_moveDownSprite);
//
//}
//Cat* Cat::create(Vec2 startPosition) {
//	Cat* cat = new Cat();
//	if (cat && cat->init(startPosition))
//	{
//		cat->autorelease();
//		return cat;
//	}
//	delete cat;
//	return nullptr;
//}

//Chicken


Chicken* Chicken::create(Vec2 startPosition) {
	Chicken* chicken = new Chicken();
	if (chicken && chicken->init(startPosition))
	{
		chicken->autorelease();
		return chicken;
	}
	delete chicken;
	return nullptr;
}

//Rabbit


Rabbit* Rabbit::create(Vec2 startPosition) {
	Rabbit* rabbit = new Rabbit();
	if (rabbit && rabbit->init(startPosition))
	{
		rabbit->autorelease();
		return rabbit;
	}
	delete rabbit;
	return nullptr;
}

//Sheep

Sheep* Sheep::create(Vec2 startPosition) {
	Sheep* sheep = new Sheep();
	if (sheep && sheep->init(startPosition))
	{
		sheep->autorelease();
		return sheep;
	}
	delete sheep;
	return nullptr;
}

//Cow


Cow* Cow::create(Vec2 startPosition) {
	Cow* cow = new Cow();
	if (cow && cow->init(startPosition))
	{
		cow->autorelease();
		return cow;
	}
	delete cow;
	return nullptr;
}


//Dog
Dog* Dog::create(Vec2 startPosition)
{
	Dog* dog = new Dog();
	if (dog && dog->init(startPosition))
	{
		dog->autorelease();
		return dog;
	}
	delete dog;
	return nullptr;
}

//Cat
Cat* Cat:: create(Vec2 startPosition)
{
	Cat* cat = new Cat();
	if (cat && cat->init(startPosition))
	{
		cat->autorelease();
		return cat;
	}
	delete cat;
	return nullptr;
}


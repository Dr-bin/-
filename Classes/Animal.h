#pragma once
#pragma once

#include<algorithm>
#include <vector>
#include "cocos2d.h"


USING_NS_CC;

#define delayPerUnit 0.2f
#define moveVelocity 10.0f
#define maxMoveCount 20
#define speed 10.0f
const double MAX_FRIEENDSHIP = 1000;
const double MIN_FRIEENDSHIP = 0;
const double MAX_MOOD = 255;
const double MIN_MOOD = 0;
const int  TOTAL_FRAME_DAY = 50;//24*60*60*60

#ifndef ANIMAL_H
#define ANIMAL_H

template <typename T>
T clamp(T value, T min_value, T max_value) {
	return value < min_value ? min_value : (value > max_value ? max_value : value);
}

class Animal : public Node
{
protected:
	std::string _plistFile;
	Vector<SpriteFrame*> _images;
	AnimationCache* _animationCache;
	Sprite* _moveRightSprite;
	Sprite* _moveUpSprite;
	Sprite* _moveLeftSprite;
	Sprite* _moveDownSprite;
	Sprite* _currentSprite;
	Vec2 _startPosition;
	Vec2 _currentPosition;

	bool _isMature; // 是否成熟
	bool _isAlive;
	bool _isFeed;
	int _currentFrame;
	int _moveCount;
	double friendship;     // 友谊值，范围0-1000
	int friendshipLevel;// 友谊等级，0-5颗心，每颗心200点友谊值

public:
	virtual bool init(Vec2 startPosition);//初始化函数，设置精灵和动画的加载
   // 每日更新
	Sprite* getCurrentSprite() { return _currentSprite; }
	Vec2 getCurrentPosition() { return _currentSprite->getPosition(); }
	virtual std::string getAnimalType() const = 0;
	virtual void feed() = 0;
	virtual void update(float dt) = 0;
	void moveAround();
	void setImages();
	void createAnimations();
	float getRandomWaitTime();
	int getRandomRepeatTime();
	//Vec2 getRandomDistance(Vec2 currentPosition, const std::string& directio);
	bool isAlive() { return _isAlive; }
	bool isMature() { return _isMature; }
	AnimationCache* getAnimationCache() { return _animationCache; }

};

#endif // ANIMAL_H



class Livestock : public Animal
{
protected:
	int price;          // 价格
	double mood;           // 心情值，范围0-255


	int feedDays; // 喂养天数
	int matureDays; // 成熟天数

	int lastFeedTime; // 上次喂食的时间
	bool _isProduceProduct; // 是否生产产品
	std::vector<std::string> products; // 产品列表

public:
	virtual bool init()
	{
		if (!Node::init()) {
			return false;
		}
		mood = 150;
		friendship = 500;
		friendshipLevel = 2;
		feedDays = 0;
		matureDays = 0;
		_isMature = false;
		lastFeedTime = 0;
		_isProduceProduct = false;

		// 初始化特有的属性或执行其它初始化逻辑
		return true;
	}


	//获取产品
	std::string getProduct(int &num)  {
		int productNum = products.size();
		
		num = productNum;
		if (productNum == 0) {
			return "NULL";
		}
		else {
			//物品栏置零
			std::string name = products[0];
			products.clear();
			return name;
		}

			
		
	}
	//获取价格
	int getPrice() const {
		return int(price * (1 + 0.1 * friendshipLevel));
	}

	//处理心情值与友谊值
	double getMood() const { return mood; }
	void setMood(int value) { mood = clamp(value, 0, 255); }
	double getFriendship() const { return friendship; }
	void setFriendship(int value) { friendship = clamp(value, 0, 1000); }
	int getFriendshipLevel() const { return friendshipLevel; }
	void updateFriendshipLevel() {
		friendshipLevel = (int)friendship / 200;
		friendshipLevel = clamp(friendshipLevel, 0, 5);
	}
	double calculateMoodAdjustment(int mood)		//计算心情值调整值
	{
		if (mood <= 100) {
			return mood - 100;
		}
		else if (mood > 100 && mood <= 200) {
			return 0;
		}
		else {
			return 1.5;
		}
	}
	void addMood(int value) {
		mood += value;
		mood = clamp(mood, MIN_MOOD, MAX_MOOD);
	}
	void subtractMood(int value) {
		mood -= value;
		mood = clamp(mood, MIN_MOOD, MAX_MOOD);
	}
	void addFriendship(int value) {
		friendship += value;
		friendship = clamp(friendship, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
		updateFriendshipLevel();
	}
	void subtractFriendship(int value) {
		friendship -= value;
		friendship = clamp(friendship, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
		updateFriendshipLevel();
	}

	// 喂养TODO:接口 获取人物喂养逻辑
	virtual void feed() {
		if (_isFeed)return;
		_isFeed = true;
		friendship = clamp(friendship + 50, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
		mood = clamp(mood + 10,MIN_MOOD, MAX_MOOD);
	}

	void onFeed() {
		addMood(10);
		addFriendship(50);
		this->stopAllActions();
		std::string type = getAnimalType();
		auto startAnimation = CallFunc::create([&]() {
			this->stopAllActions();
			});
		auto animation = _animationCache->getAnimation(type + "-" + "lieDown");
		auto lieDown = Repeat::create(Animate::create(animation), 1);
		auto delay = DelayTime::create(0.5f);
		auto sequence = Sequence::create(startAnimation, lieDown, delay, CallFunc::create([this]() { moveAround(); }), nullptr);
		this->runAction(sequence->clone());

	}


	// 每日更新
	virtual void update(float dt) {
		_currentFrame++;
		if (!_isMature) {
			if (_isFeed)
				feedDays++;
			if (feedDays >= matureDays) {
				_isMature = true;  // 成熟
			}
		}
		produceProduct();
		//降低心情值和友谊值		
		if (_currentFrame == TOTAL_FRAME_DAY && !_isFeed) {
			mood = clamp(mood - 20, MIN_MOOD, MAX_MOOD);
			friendship = clamp(friendship - 50, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
		}
		//更新我的帧数记录
		if (_currentFrame >= TOTAL_FRAME_DAY) {
			_currentFrame = 0;
			_isFeed = false;
			_isProduceProduct = false;
		}
	}

	virtual void produceProduct() = 0; // 每日生产产品的逻辑

};

// Cow类

class Cow :public Livestock
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;

		_plistFile = "cow.plist";
		price = 1000;
		Animal::init(startPosition);
		return true;
	}
	static Cow* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Cow";
	}
	void produceProduct() override {
		if (!_isMature) return;
		if (_isFeed == 0) return;
		
		if (!_isProduceProduct) {
			products.push_back("Milk");
			 _isProduceProduct= true;
			// 检查是否产出大牛奶(高级动物产品)
			if (friendship >= 200) {
				double score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
				double random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
				if (score > random) {
					products.push_back("Milk");
					products.push_back("Milk");
				}
			}
		}
	}

private:

};



//class Livestock : public Animal
//{
//public:
//	int mood;
//	int friendship;
//	virtual bool init()
//	{
//		if (!Animal::init())
//			return false;
//		 //家畜特有的初始化
//		return true;
//	}
//protected:
//
//};

class Sheep : public Livestock {
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		_plistFile = "sheep.plist";
		price = 500;
		Animal::init(startPosition);
		return true;
	}
	static Sheep* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Sheep";
	}
	void produceProduct() override {
		if (!_isMature) return;
		if(!_isFeed)
			return;
		if (!_isProduceProduct) {
			products.push_back("Fur");
			_isProduceProduct = true;
			if (friendship >= 200) {
				double score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
				double random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
				if (score > random) {
					products.push_back("Fur");
					products.push_back("Fur");
				}
			}
		}
		
	}

};

//#ifndef __CHICKEN_H__
//#define __CHICKEN_H__

class Chicken : public Livestock
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		_plistFile = "chicken.plist";
		price = 200;
		Animal::init(startPosition);
		return true;
	}
	static Chicken* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Chicken";
	}
	void produceProduct() override {
		if (!_isMature) return;
        if(!_isFeed)
            return;
		if (!_isProduceProduct) {
			products.push_back("Egg");
			_isProduceProduct = true;
			// 检查是否产出大鸡蛋
			if (friendship >= 200) {
				double score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
				double random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
				if (score > random) {
					products.push_back("Egg");
					products.push_back("Egg");
				}
			}
		}
	}

};

//#endif // __CHICKEN_H__

class Rabbit : public Livestock
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		_plistFile = "rabbit.plist";
		price = 700;
		Animal::init(startPosition);
		return true;
	}
	static Rabbit* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Rabbit";
	}
	void produceProduct() override
	{
		if (!_isMature) return;
		if (!_isFeed) return;
		if (!_isProduceProduct) {
			products.push_back("Meat");
			_isProduceProduct = true;
			if (friendship >= 200) {
				double score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
				double random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
				if (score > random) {
					products.push_back("Meat");
					products.push_back("Meat");
				}
			}
		}
	}

};




class Pet :public Animal
{
public:

	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		return true;
	}

	void interact() {
		friendship = clamp(friendship + 30, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
	}


	virtual void update(float dt) {
		if (_currentFrame == TOTAL_FRAME_DAY && !_isFeed)
			friendship = clamp(friendship - 25, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);
		if (_currentFrame >= TOTAL_FRAME_DAY)
		{
			_currentFrame = 0;
			_isFeed = false;
		}
	}

	//喂养
	virtual void feed() {
		if (_isFeed) return;
		_isFeed = true;
		friendship = clamp(friendship + 50, MIN_FRIEENDSHIP, MAX_FRIEENDSHIP);

	}

	void onFeed(int currentTime) {
		this->stopAllActions();
		std::string type = getAnimalType();
		auto animation = _animationCache->getAnimation(type + "-" + "lieDown");
		auto lieDown = Repeat::create(Animate::create(animation), 1);
		auto delay = DelayTime::create(0.5f);
		auto callFunc = CallFunc::create(CC_CALLBACK_0(Animal::moveAround, this));
		auto sequence = Sequence::create(lieDown, delay, callFunc, nullptr);
		this->runAction(sequence->clone());

	}


};

class Dog : public Pet
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		_plistFile = "dog.plist";
		Animal::init(startPosition);
	}
	static Dog* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Dog";
	}
};



class Cat : public Pet
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		_plistFile = "cat.plist";
		Animal::init(startPosition);
		return true;
	}
	static Cat* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Cat";
	}
};


class GameScene : public Layer
{
public:
	static Scene* createScene()
	{
		auto scene = Scene::create();
		auto layer = Layer::create();

		//// 创建并添加 dog
		//auto dog = Dog::create(Vec2(300, 200));
		//if (dog)
		//{
		//	layer->addChild(dog);
		//	dog->moveAround();
		//}
		//// 创建并添加 chicken
		//auto chicken = Chicken::create(Vec2(100, 200));
		//if (chicken)
		//{
		//	layer->addChild(chicken);
		//	chicken->moveAround();
		//}

		//// 创建并添加 cat
		//auto cat = Cat::create(Vec2(100, 100));
		//if (cat)
		//{
		//	layer->addChild(cat);
		//	cat->moveAround();
		//}

		//// 创建并添加 sheep
		//auto sheep = Sheep::create(Vec2(30, 50));
		//if (sheep)
		//{
		//	layer->addChild(sheep);
		//	sheep->moveAround();
		//}

		//// 创建并添加 cow
		//auto cow = Cow::create(Vec2(50, 150));
		//auto cow2 = Cow::create(Vec2(90, 120));
		//if (cow)
		//{
		//	layer->addChild(cow);
		//	layer->addChild(cow2);
		//	cow->moveAround();
		//	cow2->moveAround();
		//}

		// 创建并添加 rabbit
		auto rabbit = Rabbit::create(Vec2(70, 200));
		if (rabbit)
		{
			layer->addChild(rabbit);
			rabbit->moveAround();
		}
		scene->addChild(layer);

		return scene;
	}


};




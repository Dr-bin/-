#pragma once
#pragma once
#include "cocos2d.h"
#include<algorithm>
#include <vector>
#include "cocos2d.h"


USING_NS_CC;

#define delayPerUnit 0.2f
#define moveVelocity 10.0f
#define maxMoveCount 20
#define speed 10.0f



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

	
	bool _isAlive;
	int _moveCount;
	float _width = 500;					//������Χ
	float _height = 500;					//������Χ

public:
	virtual bool init(Vec2 startPosition) ;//��ʼ�����������þ���Ͷ����ļ���
	virtual void dailyUpdate(int currentTime) = 0;    // ÿ�ո���
	virtual std::string getAnimalType() const= 0;
	void moveAround();
	void setImages();
	void createAnimations();
	float getRandomWaitTime();
	int getRandomRepeatTime();
	Vec2 getRandomDistance(Vec2 currentPosition,const std::string& directio);
	bool isAlive(){ return _isAlive; }
	AnimationCache* getAnimationCache() { return _animationCache; }

};

#endif // ANIMAL_H



class Livestock : public Animal
{
protected:
	int price;          // �۸�
	int mood;           // ����ֵ����Χ0-255
	int friendship;     // ����ֵ����Χ0-1000
	int friendshipLevel;// ����ȼ���0-5���ģ�ÿ����200������ֵ

	int feedDays; // ι������
	int matureDays; // ��������
	bool isMature; // �Ƿ����
	int lastFeedTime; // �ϴ�ιʳ��ʱ��
	int lastProductionTime; // �ϴ�����ʱ��
	std::vector<std::string> products; // ��Ʒ�б�

public:
	virtual bool init() 
	{
		if (!Node::init()) {
			return false;
		}

		// �����Ƴ����캯���еĳ�ʼ���߼���ת���˴�
		mood = 150;
		friendship = 500;
		friendshipLevel = 2;
		feedDays = 0;
		matureDays = 0;
		isMature = false;
		lastFeedTime = 0;
		lastProductionTime = 0;

		// ��ʼ�����е����Ի�ִ��������ʼ���߼�
		return true;
	}

	//��ȡ�۸�
	int getPrice() const {
		return price*(1+0.1*friendshipLevel);
	}

	//��������ֵ������ֵ
	int getMood() const { return mood; }
	void setMood(int value) { mood = clamp(value, 0, 255); }
	int getFriendship() const { return friendship; }
	void setFriendship(int value) { friendship = clamp(value, 0, 1000); }
	int getFriendshipLevel() const { return friendshipLevel; }
	void updateFriendshipLevel() {
		friendshipLevel = friendship / 200;
		friendshipLevel = clamp(friendshipLevel, 0, 5);
	}
	float calculateMoodAdjustment(int mood)		//��������ֵ����ֵ
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
		mood = clamp(mood, 0, 255);
	}
	void subtractMood(int value) {
		mood -= value;
		mood = clamp(mood, 0, 255);
	}
	void addFriendship(int value) {
		friendship += value;
		friendship = clamp(friendship, 0, 1000);
		updateFriendshipLevel();
	}
	void subtractFriendship(int value) {
		friendship -= value;
		friendship = clamp(friendship, 0, 1000);
		updateFriendshipLevel();
	}

	// ι��TODO:�ӿ� ��ȡ����ι���߼�
	void feed(int currentTime) {
		if (currentTime - lastFeedTime < 24 * 60) return;
		lastFeedTime = currentTime;
		friendship = clamp(friendship + 50, 0, 1000);
		mood = clamp(mood + 10, 0, 255);
		onFeed(currentTime);
	}	

	void onFeed(int currentTime)  {
		addMood(10);
		addFriendship(50);
		this->stopAllActions();
		std::string type = getAnimalType();
		auto animation = _animationCache->getAnimation(type + "-" + "lieDown");
		auto lieDown = Repeat::create(Animate::create(animation), 1);
		auto delay = DelayTime::create(0.5f);
		auto callFunc = CallFunc::create(CC_CALLBACK_0(Animal::moveAround, this));
		auto sequence = Sequence::create(lieDown, delay, callFunc, nullptr);
		this->runAction(sequence);

	}


	// ÿ�ո���
	virtual void dailyUpdate(int currentTime)  {
		if (!isMature) {
			feedDays++;
			if (feedDays >= matureDays) {
				isMature = true;  // ����
			}
		}
		//��������ֵ������ֵ
		int daysPassed = (currentTime - lastFeedTime) / (24 * 60);
		if (daysPassed >= 1) {
			mood = clamp(mood - 20 * daysPassed, 0, 255);
			friendship = clamp(friendship - 50 * daysPassed, 0, 1000);
			lastFeedTime = currentTime;
		}
	}

	virtual void produceProduct(int currentTime) = 0; // ÿ��������Ʒ���߼�

};

// Cow��

class Cow :public Livestock
{
public:
	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;

		_plistFile = "cow.plist";
		price = 1000;
		Animal::init( startPosition);
		return true;
	}
	static Cow* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Cow";
	}
	void produceProduct(int currentTime) override {
		if (!isMature) return;
		if (lastFeedTime == 0) return;
		int daysSinceLastProduction = (currentTime - lastProductionTime) / (24 * 60);
		if (daysSinceLastProduction >= 1) {
			products.push_back("Milk");
			lastProductionTime = currentTime;
			// ����Ƿ������ţ��(�߼������Ʒ)
			if (friendship >= 200) {
				float score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
				float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				if (score > random) {
					products.push_back("Milk");
					products.push_back("Milk");
				}
			}
		}
	}
	
private:
	
};
//class Cow : public Livestock
//{
//public:
//	virtual void dailyUpdate() override {
//		subtractMood(20);
//		subtractFriendship(5);
//		// �����߼�...
//	}
//};


//class Livestock : public Animal
//{
//public:
//	int mood;
//	int friendship;
//	virtual bool init()
//	{
//		if (!Animal::init())
//			return false;
//		 //�������еĳ�ʼ��
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
		Animal::init( startPosition);
		return true;
	}
	static Sheep* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Sheep";
	}
	void produceProduct(int currentTime) override {
		if (!isMature) return;
		if (lastFeedTime == 0) return;
		int daysSinceLastProduction = (currentTime - lastProductionTime) / (24 * 60);
		if (daysSinceLastProduction >= 3 && mood > 70) {
			products.push_back("Cur");
			lastProductionTime = currentTime;
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
		Animal::init( startPosition);
		return true;
	}
	static Chicken* create(Vec2 startPosition);
	std::string getAnimalType() const  { 
		return "Chicken";
	}
	  void produceProduct(int currentTime) override {
        if (!isMature) return;
        if (lastFeedTime == 0) return;
        int daysSinceLastProduction = (currentTime - lastProductionTime) / (24 * 60);
        if (daysSinceLastProduction >= 1) {
            products.push_back("Egg");
            lastProductionTime = currentTime;
            // ����Ƿ�����󼦵�
            if (friendship >= 200) {
                float score = (friendship + mood * calculateMoodAdjustment(mood)) / 1200;
                float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
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
		Animal::init( startPosition);
		return true;
	}
	static Rabbit* create(Vec2 startPosition);
	std::string getAnimalType() const {
		return "Rabbit";
	}
	void produceProduct(int currentTime) override
	{
		if (!isMature) return;
		if (lastFeedTime == 0) return;
		int daysSinceLastProduction = (currentTime - lastProductionTime) / (24 * 60);
		if (daysSinceLastProduction >= 4) {
			products.push_back("Fur");
			if (friendship >= 200) {
				float score = (friendship + mood * calculateMoodAdjustment(mood)) / 5000 + 0.10;
				float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
				if (score > random) {
					products.push_back("RabbitFoot");
				}
			}
			lastProductionTime = currentTime;

		}
	};
};




class Pet :public Animal
{
private:

	int friendship;
	int lastFeedTime; // �ϴ�ιʳ��ʱ��
public:

	virtual bool init(Vec2 startPosition)
	{
		if (!Node::init())
			return false;
		return true;
	}

	 void feed() {
		friendship = clamp(friendship + 50, 0, 1000);
	}

	 void interact() {
		friendship = clamp(friendship + 30, 0, 1000);
	}

	 
	virtual void dailyUpdate(int currentTime) {
		int hoursPassed = currentTime / 60;

		friendship = clamp(friendship - (hoursPassed * 5), 0, 1000);
	}


	int getFriendship() const { return friendship; }
	void setFriendship(int f) { friendship = clamp(f, 0, 1000); }
	//ι��
	void feed(int currentTime) {
		if (currentTime - lastFeedTime < 24 * 60) return;
		lastFeedTime = currentTime;
		friendship = clamp(friendship + 50, 0, 1000);
		onFeed(currentTime);
	}

	void onFeed(int currentTime) {
		this->stopAllActions();
		std::string type = getAnimalType();
		auto animation = _animationCache->getAnimation(type + "-" + "lieDown");
		auto lieDown = Repeat::create(Animate::create(animation), 1);
		auto delay = DelayTime::create(0.5f);
		auto callFunc = CallFunc::create(CC_CALLBACK_0(Animal::moveAround, this));
		auto sequence = Sequence::create(lieDown, delay, callFunc, nullptr);
		this->runAction(sequence);

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

		// ��������� dog
		auto dog = Dog::create(Vec2(300, 200));
		if (dog)
		{
			layer->addChild(dog);
			dog->moveAround();
		}
		// ��������� chicken
		auto chicken = Chicken::create(Vec2(100, 200));
		if (chicken)
		{
			layer->addChild(chicken);
			chicken->moveAround();
		}

		// ��������� cat
		auto cat = Cat::create(Vec2(100, 100));
		if (cat)
		{
			layer->addChild(cat);
			cat->moveAround();
		}

		// ��������� sheep
		auto sheep = Sheep::create(Vec2(30, 50));
		if (sheep)
		{
			layer->addChild(sheep);
			sheep->moveAround();
		}

		// ��������� cow
		auto cow = Cow::create(Vec2(50, 150));
		auto cow2 = Cow::create(Vec2(90, 120));
		if (cow)
		{
			layer->addChild(cow);
			layer->addChild(cow2);
			cow->moveAround();
			cow2->moveAround();
		}

		// ��������� rabbit
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




#include "AnimalManager.h"
#include"menus.h"

using namespace cocos2d;

int stringToTag(std::string str)
{
	if (str == "Milk")
		return 11;
	else if (str == "Egg")
		return 17;
	else if (str == "Fur")
		return 16;
	else
		return -1;
}

AnimalManager* AnimalManager::create()
{
	AnimalManager* animalManager = new (std::nothrow) AnimalManager();
	if (animalManager && animalManager->init())
	{
		animalManager->autorelease();
		return animalManager;
	}
	CC_SAFE_DELETE(animalManager);
	return nullptr;
}

bool AnimalManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Initialize event listeners
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(AnimalManager::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	addNewAnimal("Cow");
	addNewAnimal("Sheep");
	addNewAnimal("Chicken");
	addNewAnimal("Rabbit");
	addNewAnimal("Dog");
	addNewAnimal("Cat");

	return true;
}

void AnimalManager::sellAnimal(Animal* animal)
{
	if (animal->isMature())
	{
		// Selling logic: remove the animal and return the price
		int price = dynamic_cast<Livestock*>(animal)->getPrice();
		CCLOG("Animal sold for %d", price);
		itemBag->money += price;
		itemBag->updateMoney(itemBag->money);

		removeAnimal(animal);
	}
	else {
		CCLOG("Animal is not mature yet, cannot sell.");
	}
}

void AnimalManager::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	Vec2 clickLocation = Vec2(e->getCursorX(), e->getCursorY());

	if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		// Left click event
		checkForAnimals(clickLocation);
	}
	else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		// Right click event
		sellAnimalAtPosition(clickLocation);
	}
}

void AnimalManager::checkForAnimals(Vec2 clickPosition)
{
	for (auto animal : animals)
	{
		// Check if the click position is within the bounding box of the animal
		if (animal->getCurrentSprite()->getBoundingBox().containsPoint(clickPosition))
		{
			animal->feed();
			// TODO:人物获得产品
			if (auto livestock = dynamic_cast<Livestock*>(animal))
			{
				int havecstNum = 0, tag = -1;
				std::string productName = livestock->getProduct(havecstNum);
				tag = stringToTag(productName);
				if (tag != -1 && havecstNum > 0) {
					itemBag->addItem(tag, havecstNum);
					itemBag->money += itemBag->getItem(tag)->sell_price * havecstNum;
					itemBag->updateMoney(itemBag->money);
				}

			}
			else if (auto pet = dynamic_cast<Pet*>(animal))
			{
				CCLOG("This is a pet, no product available.");
				pet->interact();
			}
			break;
		}


	}
}

void AnimalManager::sellAnimalAtPosition(Vec2 clickPosition)
{
	for (auto& animal : animals)
		//TODO: 卖出动物,人物获得金钱
	{
		if (animal->getCurrentSprite()->getBoundingBox().containsPoint(clickPosition))
		{
			if (auto livestock = dynamic_cast<Livestock*>(animal))
				sellAnimal(animal);
			break;
		}
	}
}

void AnimalManager::addNewAnimal(const std::string& animalType)
{
	Vec2 position = Vec2(xStart + (rand() % (xEnd - xStart)), yStart + (rand() % (yEnd - yStart)));
	Animal* newAnimal = nullptr;
	if (animalType == "Cow")
	{
		newAnimal = Cow::create(position);
	}
	else if (animalType == "Sheep")
	{
		newAnimal = Sheep::create(position);
	}
	else if (animalType == "Chicken")
	{
		newAnimal = Chicken::create(position);

	}
	else if (animalType == "Rabbit")
	{
		newAnimal = Rabbit::create(position);
	}
	else if (animalType == "Dog")
	{
		newAnimal = Dog::create(position);
	}
	else if (animalType == "Cat")
	{
		newAnimal = Cat::create(position);
	}
	if (newAnimal)
	{
		addAnimal(newAnimal);
	}
}

void AnimalManager::addAnimal(Animal* animal)
{
	animals.pushBack(animal);
	this->addChild(animal);
	animal->moveAround();
}

void AnimalManager::removeAnimal(Animal* animal)
{
	auto it = std::find(animals.begin(), animals.end(), animal);
	if (it != animals.end())
	{
		animals.erase(it);
		animal->stopAllActions();
		this->removeChild(animal);

	}
}
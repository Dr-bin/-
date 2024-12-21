#ifndef ANIMAL_MANAGER_H
#define ANIMAL_MANAGER_H

#include "Animal.h"
#include "cocos2d.h"

USING_NS_CC;

class AnimalManager : public Layer
{
private:
    Vector<Animal*> animals; // 存储所有的动物
    int xStart = 1100;
    int xEnd = 1300;
    int yStart = 200;
    int yEnd = 450;

public:
    // 初始化事件监听
    virtual bool init() override;

    // 创建并返回一个 AnimalManager 对象
    static AnimalManager* create();

    // 售卖动物
    void sellAnimal(Animal* animal);

    // 处理鼠标点击事件
    void onMouseDown(Event* event);

    // 检查点击位置是否有动物
    void checkForAnimals(Vec2 clickPosition);

    // 在指定位置售卖动物
    void sellAnimalAtPosition(Vec2 clickPosition);

    // 创建并添加指定类型的动物到场景中
    void addNewAnimal(const std::string& animalType);

    // 添加动物
    void addAnimal(Animal* animal);

    // 删除动物
    void removeAnimal(Animal* animal);
};

#endif // ANIMAL_MANAGER_H
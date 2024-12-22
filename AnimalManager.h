#ifndef ANIMAL_MANAGER_H
#define ANIMAL_MANAGER_H

#include "Animal.h"
#include "cocos2d.h"

USING_NS_CC;

class AnimalManager : public Layer
{
private:
    Vector<Animal*> animals; // �洢���еĶ���
    int xStart = 1100;
    int xEnd = 1300;
    int yStart = 200;
    int yEnd = 450;

public:
    // ��ʼ���¼�����
    virtual bool init() override;

    // ����������һ�� AnimalManager ����
    static AnimalManager* create();

    // ��������
    void sellAnimal(Animal* animal);

    // ����������¼�
    void onMouseDown(Event* event);

    // �����λ���Ƿ��ж���
    void checkForAnimals(Vec2 clickPosition);

    // ��ָ��λ����������
    void sellAnimalAtPosition(Vec2 clickPosition);

    // ���������ָ�����͵Ķ��ﵽ������
    void addNewAnimal(const std::string& animalType);

    // ��Ӷ���
    void addAnimal(Animal* animal);

    // ɾ������
    void removeAnimal(Animal* animal);
};

#endif // ANIMAL_MANAGER_H
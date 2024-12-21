#include "DataProvider.h"

//DataProvider是一个单例类，可以用来给不同的类之间传递数值
//这里我写的很糙，只能用来传递int数组，当然也可以修改成传递更多值的类
//不过修改后要注意不要让这个类同时被多个地方同时修改访问，可能需要加锁来解决

DataProvider* DataProvider::getInstance() {
    static DataProvider instance;
    return &instance;
}

int* DataProvider::getEXData() {

    return LevelTreeEx;
}

void DataProvider::setEXData(int* ex) {
    for (int i = 0; i < 4; i++)
        LevelTreeEx[i] = ex[i];
    return;
}

DataProvider::DataProvider() {}
DataProvider::~DataProvider() {}
#include "DataProvider.h"

//DataProvider��һ�������࣬������������ͬ����֮�䴫����ֵ
//������д�ĺܲڣ�ֻ����������int���飬��ȻҲ�����޸ĳɴ��ݸ���ֵ����
//�����޸ĺ�Ҫע�ⲻҪ�������ͬʱ������ط�ͬʱ�޸ķ��ʣ�������Ҫ���������

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
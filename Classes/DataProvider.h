#pragma once

#ifndef __DATA_PROVIDER__
#define __DATA_PROVIDER__

class DataProvider
{
public:
    static DataProvider* getInstance();
    //需要保证数组大小为4
    void setEXData(int* ex);
    int* getEXData();//获取最新数据，这里是是一个int数组,类似的可以在后面添加
private:
    int LevelTreeEx[4];
    DataProvider(); // 私有构造函数
    ~DataProvider(); // 私有析构函数
    DataProvider(const DataProvider&) = delete; // 删除拷贝构造函数
    DataProvider& operator=(const DataProvider&) = delete; // 删除赋值运算符
};


#endif // __DATA_PROVIDER__
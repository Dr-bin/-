#pragma once

#ifndef __DATA_PROVIDER__
#define __DATA_PROVIDER__

class DataProvider
{
public:
    static DataProvider* getInstance();
    //��Ҫ��֤�����СΪ4
    void setEXData(int* ex);
    int* getEXData();//��ȡ�������ݣ���������һ��int����,���ƵĿ����ں������
private:
    int LevelTreeEx[4];
    DataProvider(); // ˽�й��캯��
    ~DataProvider(); // ˽����������
    DataProvider(const DataProvider&) = delete; // ɾ���������캯��
    DataProvider& operator=(const DataProvider&) = delete; // ɾ����ֵ�����
};


#endif // __DATA_PROVIDER__
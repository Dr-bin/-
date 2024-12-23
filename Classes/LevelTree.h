#pragma once

#include "cocos2d.h"
#include "PopupBase.h"
#include "DataProvider.h"

USING_NS_CC;
#define maxEX 100.0

//�������ʾ�ȼ��;����õĵ���������ʹ����Ҫ�õ�DataProvider��ȡCharater����Ϣ��
//����Ҫ�ڽ�ɫ��ʵ����⿴������ڿ��������ֲ�Ϳ�����������������ļ�¼
//Ҫ����DataProviderһ��4��С�����飬��û�иĳɸ��õ����ͣ����Դ�Сֻ��Ϊ4

//����������
class LevelTree : public PopupBase
{
public:
	static LevelTree* create() {//exΪ���澭�������
        auto ret = new (std::nothrow) LevelTree();
        if (ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
        return ret;
	}

    bool init();

    //void updataEX(int* e) {�����ã�ûɾ
    //    for (int i = 0; i < 4; i++)
    //        ex[i] = e[i];
    //    return;
    //}

    virtual void onShow();
    virtual void onHide();

private:
    float startx = 0;
    float starty = 0;
    float dy = 0;
    float times[4] = { 0 };
    int* ex = NULL;
    Size fSize;

};



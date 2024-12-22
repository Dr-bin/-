#pragma once

#include "cocos2d.h"
USING_NS_CC;

#define SEASON_TIME 3//һ�����ڳ���������

class GameTime : public cocos2d::Ref {
public:
    // ��ȡ����ʵ��
    static GameTime* getInstance() {
        static GameTime instance;
        return &instance;
    }

    //����ÿ��֡��
    void set(float frames) {
        fps = frames;
        return;
    }

    // ��¼ʱ��ĺ���,���شӿ�ʼ�����ھ���������
    float recordTime_second() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return (currentTime - startTime) / fps;
    }

    //��¼ʱ��ĺ���,���شӿ�ʼ�����ھ�����֡��
    float recordTime_frames() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return currentTime - startTime;
    }

    //���ص�ǰ���ڣ�1234�ֱ��Ǵ����ﶬ
    int recordTime_season() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return int((currentTime - startTime) / fps / SEASON_TIME) % 4 + 1;
    }

private:
    float startTime;
    float fps = 60;//֡��

    // ˽�л����캯����������������ֹ�ⲿʵ����������
    GameTime() {
        // ��ʼ��ʱ���¼
        startTime = cocos2d::Director::getInstance()->getTotalFrames();
    }
    virtual ~GameTime() {}

    // ��ֹ���ƺ͸�ֵ
    GameTime(const GameTime&) = delete;
    GameTime& operator=(const GameTime&) = delete;
};
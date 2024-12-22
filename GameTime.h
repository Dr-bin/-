#pragma once

#include "cocos2d.h"
USING_NS_CC;

#define SEASON_TIME 3//一个季节持续多少秒

class GameTime : public cocos2d::Ref {
public:
    // 获取单例实例
    static GameTime* getInstance() {
        static GameTime instance;
        return &instance;
    }

    //设置每秒帧数
    void set(float frames) {
        fps = frames;
        return;
    }

    // 记录时间的函数,返回从开始到现在经历的秒数
    float recordTime_second() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return (currentTime - startTime) / fps;
    }

    //记录时间的函数,返回从开始到现在经历的帧数
    float recordTime_frames() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return currentTime - startTime;
    }

    //返回当前季节，1234分别是春夏秋冬
    int recordTime_season() {
        float currentTime = cocos2d::Director::getInstance()->getTotalFrames();
        return int((currentTime - startTime) / fps / SEASON_TIME) % 4 + 1;
    }

private:
    float startTime;
    float fps = 60;//帧数

    // 私有化构造函数和析构函数，防止外部实例化和销毁
    GameTime() {
        // 初始化时间记录
        startTime = cocos2d::Director::getInstance()->getTotalFrames();
    }
    virtual ~GameTime() {}

    // 禁止复制和赋值
    GameTime(const GameTime&) = delete;
    GameTime& operator=(const GameTime&) = delete;
};
#pragma once

#include "cocos2d.h"
#include "GameTime.h"
USING_NS_CC;

class TimeBoard : public Node
{
public:
    static TimeBoard* create(const Vec2& position)
    {
        auto ret = new (std::nothrow) TimeBoard();
        if (ret && ret->init(position))
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

    bool init(const Vec2& position)
    {
        if (!Node::init())
        {
            return false;
        }

        auto cache = SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile("season.plist");

        spring = Sprite::createWithSpriteFrameName("spring.png");
        summer = Sprite::createWithSpriteFrameName("summer.png");
        fall = Sprite::createWithSpriteFrameName("fall.png");
        winter = Sprite::createWithSpriteFrameName("winter.png");

        auto TimeBar = Sprite::create("TimeBar.png");
        this->addChild(TimeBar);

        auto timeLabel = Label::createWithSystemFont("Time: 00:00", "Garamond", 16);
        auto seasonLabel = Label::createWithSystemFont("Season: Spring", "Garamond", 16);

        TimeBar->addChild(spring);
        TimeBar->addChild(summer);
        TimeBar->addChild(fall);
        TimeBar->addChild(winter);
        TimeBar->addChild(timeLabel);
        TimeBar->addChild(seasonLabel);

        auto barsize = TimeBar->getContentSize();
        spring->setPosition(barsize.width / 2, barsize.height / 2);
        summer->setPosition(barsize.width / 2, barsize.height / 2);
        winter->setPosition(barsize.width / 2, barsize.height / 2);
        fall->setPosition(barsize.width / 2, barsize.height / 2);
        timeLabel->setPosition(barsize.width / 2, -8);
        seasonLabel->setPosition(barsize.width / 2, -20);

        summer->setVisible(false);
        fall->setVisible(false);
        winter->setVisible(false);

        this->schedule([=](float dt) {
            char buffer[20];
            int mins = int(GameTime::getInstance()->recordTime_second() / 10);
            int hours = mins / 60 % 24;
            mins %= 60;
            sprintf(buffer, "Time: %02d:%02d", hours, mins);
            timeLabel->setString(buffer);

            spring->setVisible(false);
            summer->setVisible(false);
            fall->setVisible(false);
            winter->setVisible(false);
            switch (GameTime::getInstance()->recordTime_season())
            {
                case 1:
                    spring->setVisible(true);
                    seasonLabel->setString("Season: Spring");
                    break;
                case 2:
                    summer->setVisible(true);
                    seasonLabel->setString("Season: Summer");
                    break;
                case 3:
                    fall->setVisible(true);
                    seasonLabel->setString("Season: Fall");
                    break;
                case 4:
                    winter->setVisible(true);
                    seasonLabel->setString("Season: Winter");
                    break;
                default:
                    break;
            }
            }, 1.0f, "TimeBoard_scheduled_task");

        this->setScale(1.5f);
        this->setPosition(position);

        return true;
    }

private:
    Sprite* spring;
    Sprite* summer;
    Sprite* fall;
    Sprite* winter;

};
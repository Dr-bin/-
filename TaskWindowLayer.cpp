// TaskWindowLayer.cpp
#include "TaskWindowLayer.h"
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include"NPCManager.h"

USING_NS_CC;

Layer* TaskWindowLayer::create(NPC* npc) {
    auto layer = new TaskWindowLayer();
    if (layer && layer->init(npc)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool TaskWindowLayer::init(NPC* npc) {
    if (!Layer::init()) {
        return false;
    }
    _npc = npc;

    // 创建背景 Sprite
    auto background = Sprite::create("PopBkg.png");
    background->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    background->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(background);

    // 显示NPC名字
    auto nameLabel = Label::createWithSystemFont(_npc->getNPCName(), "Arial", 24);
    nameLabel->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height - 50));
    background->addChild(nameLabel);

    // 显示任务列表
    int y = background->getContentSize().height - 100;
    for (Task* task : _npc->getTasks()) {
        auto taskLabel = Label::createWithSystemFont(task->getName(), "Arial", 18);
        taskLabel->setPosition(Vec2(background->getContentSize().width / 2, y));
        background->addChild(taskLabel);
        y -= 30;
    }
    
    // 创建关闭按钮
    auto closeButton = ui::Button::create("CloseSelected.png");
    closeButton->setPosition(Vec2(background->getContentSize().width - 30, 30));
    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->addClickEventListener([this](Ref* sender) {
        this->closeWindow();
        });
    background->addChild(closeButton);

    // 添加触摸事件来检测点击外部区域
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!this->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
            this->closeWindow();
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

void TaskWindowLayer::closeWindow() {
    this->removeFromParentAndCleanup(true);
}
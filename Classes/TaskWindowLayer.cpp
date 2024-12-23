// TaskWindowLayer.cpp
#include "TaskWindowLayer.h"
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include"NPCManager.h"
#include"TaskManager.h"

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

    // �������� Sprite
    background = Sprite::create("PopBkg.png");
    background->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    background->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(background,500);

    // ��ʾNPC����
    auto nameLabel = Label::createWithSystemFont(_npc->getNPCName(), "Arial", 24);
    nameLabel->setPosition(Vec2(background->getContentSize().width / 2, background->getContentSize().height - 50));
    background->addChild(nameLabel);

    // ��ʾ�����б�
    int y = background->getContentSize().height - 100;
    for (Task* task : _npc->getTasks()) {
        auto taskButton = ui::Button::create("task_button_normal.png", "task_button_pressed.png");
        taskButton->setTitleText(task->getName());
        taskButton->setPosition(Vec2(background->getContentSize().width / 2, y));
        taskButton->addClickEventListener([this, task](Ref* sender) {
            TaskManager::getInstance()->completeTask(task, _npc);
            });
        background->addChild(taskButton);
        y -= 50;
    }
  /*  for (Task* task : _npc->getTasks()) {
        auto taskLabel = Label::createWithSystemFont(task->getName()+"+"+task->getDescription(), "Arial", 18);
        taskLabel->setPosition(Vec2(background->getContentSize().width / 2, y));
        background->addChild(taskLabel);
        y -= 30;
    }*/
    
    // �����رհ�ť
    auto closeButton = ui::Button::create("CloseSelected.png");
    closeButton->setPosition(Vec2(background->getContentSize().width - 30, 30));
    closeButton->setAnchorPoint(Vec2(1, 0));
    closeButton->addClickEventListener([this](Ref* sender) {
        this->closeWindow();
        });
    background->addChild(closeButton);

    // ע���Զ����¼�������
    auto eventListener = EventListenerCustom::create(TaskManager::TASK_COMPLETED_EVENT, [this](EventCustom* event) {
        const char* taskName = (const char*)event->getUserData();
        this->showTaskCompletionMessage(taskName);
        });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    // ��Ӵ����¼���������ⲿ����
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!this->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
            this->closeWindow();
            return true;
        }
        return false;
        };
    //touchListener_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

void TaskWindowLayer::closeWindow() {
    this->removeFromParent();
}

void TaskWindowLayer::showTaskCompletionMessage(const char* taskName) {
    std::string message = "���� '" + std::string(taskName) + "' ����ɣ�";
    auto completionLabel = Label::createWithSystemFont(message, "Arial", 24);
    completionLabel->setPosition(Vec2(background->getContentSize().width / 2, 50));
    background->addChild(completionLabel);

    // ���õ�������
    auto fadeOut = FadeOut::create(2.0f);
    auto removeLabel = RemoveSelf::create();
    auto closeWindow = CallFunc::create([this]() {
        this->closeWindow();
        });
    completionLabel->runAction(Sequence::create(
        fadeOut,
        removeLabel,
        closeWindow,
        nullptr
    ));
}
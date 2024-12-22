//#include"cocos2d.h"
//#include"NPC.h"
//
//class TaskWindow : public Layer {
//public:
//    static TaskWindow* create(NPC* npc) {
//        TaskWindow* window = new TaskWindow();
//        if (window && window->init(npc)) {
//            window->autorelease();
//            return window;
//        }
//        CC_SAFE_DELETE(window);
//        return nullptr;
//    }
//
//    bool init(NPC* npc) {
//        if (!Layer::init()) {
//            return false;
//        }
//        // ��ʾNPC������
//        Label* nameLabel = Label::createWithSystemFont(npc->getNPCName(), "Arial", 24); 
//        nameLabel->setPosition(Vec2(100, 400));
//        this->addChild(nameLabel);
//
//        // ��ʾ�����б�
//        int y = 350;
//        for (Task* task : npc->getTasks()) {
//            Label* taskLabel = Label::createWithSystemFont(task->getName(), "Arial", 18);
//            taskLabel->setPosition(Vec2(100, y));
//            this->addChild(taskLabel);
//            y -= 30;
//        }
//
//        // ��ӽ�������İ�ť
//        // ...
//
//        return true;
//    }
//};

#pragma once
// TaskWindowLayer.h
#ifndef TASK_WINDOW_LAYER_H
#define TASK_WINDOW_LAYER_H

#include "cocos2d.h"
class NPC;

class TaskWindowLayer : public cocos2d::Layer {
public:
    static cocos2d::Layer* create(NPC* npc);
    bool init(NPC* npc);
    void closeWindow();

private:
    NPC* _npc;
    
};

#endif // TASK_WINDOW_LAYER_H
#pragma once
#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "NPC.h"
#include "cocos2d.h"
//#include "PopupBase.h"


USING_NS_CC;

class TaskWindowLayer;

class NPCManager : public Layer {
private:
    Vector<NPC*> npcs; // 存储所有的NPC
    int xStart = 1100;
    int xEnd = 1300;
    int yStart = 200;
    int yEnd = 450;

public:
    // 初始化事件监听
    virtual bool init() override;

    // 创建并返回一个 NPCManager 对象
    static NPCManager* create();

    // 添加NPC
    void addNPC(NPC* npc);

    // 删除NPC
    void removeNPC(NPC* npc);

    // 处理鼠标点击事件
    void onMouseDown(Event* event);

    // 检查点击位置是否有NPC
    void checkForNPCs(Vec2 clickPosition);


    // 创建并添加指定类型的NPC到场景中
    void addNewNPC(const std::string& npcType);
    void checkRightClickNPCs(Vec2 clickPosition);
    //显示任务
    void showTaskWindow(NPC* npc);
};

#endif // NPC_MANAGER_H
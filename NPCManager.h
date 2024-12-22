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
    Vector<NPC*> npcs; // �洢���е�NPC
    int xStart = 1100;
    int xEnd = 1300;
    int yStart = 200;
    int yEnd = 450;

public:
    // ��ʼ���¼�����
    virtual bool init() override;

    // ����������һ�� NPCManager ����
    static NPCManager* create();

    // ���NPC
    void addNPC(NPC* npc);

    // ɾ��NPC
    void removeNPC(NPC* npc);

    // ����������¼�
    void onMouseDown(Event* event);

    // �����λ���Ƿ���NPC
    void checkForNPCs(Vec2 clickPosition);


    // ���������ָ�����͵�NPC��������
    void addNewNPC(const std::string& npcType);
    void checkRightClickNPCs(Vec2 clickPosition);
    //��ʾ����
    void showTaskWindow(NPC* npc);
};

#endif // NPC_MANAGER_H
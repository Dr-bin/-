

#include "NPCManager.h"
#include "TaskWindowLayer.h"

USING_NS_CC;
using namespace cocos2d;

NPCManager* NPCManager::create() {
    NPCManager* npcManager = new (std::nothrow) NPCManager();
    if (npcManager && npcManager->init()) {
        npcManager->autorelease();
        return npcManager;
    }
    CC_SAFE_DELETE(npcManager);
    return nullptr;
}

bool NPCManager::init() {
    if (!Layer::init()) {
        return false;
    }

    // Initialize event listeners
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(NPCManager::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //初始化放置

    addNewNPC("Leah");
    addNewNPC("Elliott");
    addNewNPC("Alex");
    addNewNPC("Amy");
    return true;
}

void NPCManager::addNPC(NPC* npc) {
    npcs.pushBack(npc);
    this->addChild(npc);
    npc->moveAround();
}

void NPCManager::removeNPC(NPC* npc) {
    auto it = std::find(npcs.begin(), npcs.end(), npc);
    if (it != npcs.end()) {
        npcs.erase(it);
        npc->stopAllActions();
        this->removeChild(npc);
    }
}

void NPCManager::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    Vec2 clickLocation = Vec2(e->getCursorX(), e->getCursorY());

    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        // Left click event
        checkForNPCs(clickLocation);
    }
    else if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        // Right click event
        //进入当前任务栏
        checkRightClickNPCs(clickLocation);

    }
}

void NPCManager::checkRightClickNPCs(Vec2 clickPosition) {
    for (auto npc : npcs) {
        if (npc->getCurrentSprite()->getBoundingBox().containsPoint(clickPosition)) {
            // 显示任务窗口
            showTaskWindow(npc);
            break;
        }
    }
}

void NPCManager::checkForNPCs(Vec2 clickPosition) {
    for (auto npc : npcs) {
        if (npc->getCurrentSprite()->getBoundingBox().containsPoint(clickPosition)) {
            npc->interact();
            break;
        }
    }
}

void  NPCManager::addNewNPC(const std::string& npcName)
{
    Vec2 position = Vec2(xStart + (rand() % (xEnd - xStart)), yStart + (rand() % (yEnd - yStart)));
    NPC* newNPC = nullptr;
    if (npcName == "Amy")
    {
        newNPC = Amy::create(position);
    }
    else if (npcName == "Alex")
    {
        newNPC = Alex::create(position);
    }
    else if (npcName == "Leah")
    {
        newNPC = Leah::create(position);
    }
    else if (npcName == "Elliott")
    {
        newNPC = Elliott::create(position);
    }
    if (newNPC) {
        addNPC(newNPC);
    }

}

void NPCManager::showTaskWindow(NPC* npc) {
    auto taskWindow = TaskWindowLayer::create(npc);
    Director::getInstance()->getRunningScene()->addChild(taskWindow);
}

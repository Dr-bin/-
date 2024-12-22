#include "TaskManager.h"
#include"NPC.h"
TaskManager* TaskManager::instance = nullptr;

TaskManager* TaskManager::getInstance() {
    if (!instance) {
        instance = new TaskManager();
    }
    return instance;
}

void TaskManager::addTask(Task* task) {
    tasks.push_back(task);
}

void TaskManager::removeTask(Task* task) {
    tasks.erase(std::remove(tasks.begin(), tasks.end(), task), tasks.end());
}

std::vector<Task*> TaskManager::getTasks() const {
    return tasks;
}

void TaskManager::completeTask(Task* task, NPC* npc) {
    if (task->isCompleted()) {
        // 奖励金钱和友谊值
        // TODO:在item中增加奖励
        // player->addMoney(task->getRewardMoney());
        npc->addFriendship(task->getRewardFriendship());
        // 移除任务
        removeTask(task);
        // 显示完成提示 TODO：在GameScene中实现
        // showCompletionMessage(npc->getNPCName(), task->getName());
        removeTask(task);
        // 显示完成提示  TODO：在GameScene中实现
        //  void showCompletionMessage(const std::string& npcName, const std::string& taskName);
        // void GameScene::showCompletionMessage(const std::string& npcName, const std::string& taskName) {
// 组合消息内容
    //    std::string message = npcName + "’s  task " + taskName + "' 已完成！";

    //    // 创建Label来显示消息
    //    auto label = Label::createWithSystemFont(message, "Arial", 24);
    //    if (label) {
    //        // 获取屏幕尺寸并设置Label的位置
    //        Size winSize = Director::getInstance()->getWinSize();
    //        label->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

    //        // 将Label添加到场景中
    //        this->addChild(label);

    //        // 创建淡出动作
    //        auto fadeOut = FadeOut::create(2.0f);

    //        // 运行动作：淡出后移除Label
    //        label->runAction(Sequence::create(
    //            fadeOut,
    //            RemoveSelf::create(),
    //            nullptr
    //        ));
    //    }
    //}
        //showCompletionMessage(npc->getNPCName(), task->getName());
        //GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene();
        //if (scene) {
        //    scene->showCompletionMessage(npc->getNPCName(), task->getName());
        //}
    }
}

TaskManager::TaskManager() {}
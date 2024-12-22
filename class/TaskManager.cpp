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
        // ������Ǯ������ֵ
        // TODO:��item�����ӽ���
        // player->addMoney(task->getRewardMoney());
        npc->addFriendship(task->getRewardFriendship());
        // �Ƴ�����
        removeTask(task);
        // ��ʾ�����ʾ TODO����GameScene��ʵ��
        // showCompletionMessage(npc->getNPCName(), task->getName());
        removeTask(task);
        // ��ʾ�����ʾ  TODO����GameScene��ʵ��
        //  void showCompletionMessage(const std::string& npcName, const std::string& taskName);
        // void GameScene::showCompletionMessage(const std::string& npcName, const std::string& taskName) {
// �����Ϣ����
    //    std::string message = npcName + "��s  task " + taskName + "' ����ɣ�";

    //    // ����Label����ʾ��Ϣ
    //    auto label = Label::createWithSystemFont(message, "Arial", 24);
    //    if (label) {
    //        // ��ȡ��Ļ�ߴ粢����Label��λ��
    //        Size winSize = Director::getInstance()->getWinSize();
    //        label->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

    //        // ��Label��ӵ�������
    //        this->addChild(label);

    //        // ������������
    //        auto fadeOut = FadeOut::create(2.0f);

    //        // ���ж������������Ƴ�Label
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
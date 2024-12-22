#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "cocos2d.h"
#include <vector>

class Task;
class NPC;

class TaskManager {
public:
    static TaskManager* getInstance();
    void addTask(Task* task);
    void removeTask(Task* task);
    std::vector<Task*> getTasks() const;
    void completeTask(Task* task, NPC* npc);

private:
    TaskManager();
    static TaskManager* instance;
    std::vector<Task*> tasks;
};

#endif // TASK_MANAGER_H
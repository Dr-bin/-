#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "cocos2d.h"
#include <vector>

class Task;
class NPC;

class MessageDisplay {
public:
    void showCompletionMessage(const std::string& message);
};

class TaskManager {
public:
    static TaskManager* getInstance();
    void addTask(Task* task);
    void removeTask(Task* task);
    std::vector<Task*> getTasks() const;
    void completeTask(Task* task, NPC* npc);
    void setMessageDisplay(MessageDisplay* display);

    static const std::string TASK_COMPLETED_EVENT;
private:
    TaskManager();
    static TaskManager* instance;
    std::vector<Task*> tasks;
    MessageDisplay* messageDisplay;

};

#endif // TASK_MANAGER_H
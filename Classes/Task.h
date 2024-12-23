#include "cocos2d.h"


class Task {
public:
    Task(int id, const std::string& name, const std::string& description, int targetAmount, int rewardMoney, double rewardFriendship)
        : id(id), name(name), description(description), targetAmount(targetAmount), rewardMoney(rewardMoney), rewardFriendship(rewardFriendship), currentAmount(0) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getTargetAmount() const { return targetAmount; }
    int getRewardMoney() const { return rewardMoney; }
    double getRewardFriendship() const { return rewardFriendship; }
    int getCurrentAmount() const { return currentAmount; }

    void incrementAmount(int amount) { currentAmount += amount; }
    bool isCompleted() const { return currentAmount >= targetAmount; }

private:
    int id;
    std::string name;
    std::string description;
    int targetAmount;
    int rewardMoney;
    double rewardFriendship;
    int currentAmount;
    
};
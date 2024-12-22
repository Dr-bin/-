#include <algorithm>
#include <vector>
#include "cocos2d.h"
#include"Animal.h"
#include"Task.h"

#define FRIENDSHIP_PER_LEVEL 250
USING_NS_CC;

const float FRONTSIZE = 15;


enum class RelationshipStatus {
    Neutral,    // 普通居民
    Friend,     // 朋友
    Lover,      // 恋人
    Married     // 已婚
};

enum class Gender {
    Male, //男性
    Female//女性
};


#ifndef NPC_H
#define NPC_H
class NPC : public Node {
protected:
    std::string _plistFile;
    Vector<SpriteFrame*> _images;
    AnimationCache* _animationCache;
    Sprite* _moveRightSprite;
    Sprite* _moveUpSprite;
    Sprite* _moveLeftSprite;
    Sprite* _moveDownSprite;
    Sprite* _currentSprite;
    Vec2 _startPosition;
    Vec2 _currentPosition;
    Vector<Label*> labels;
    Label* _currentLabel;

    bool _isAlive;
    bool _isTalk;
    int _currentFrame;
    int _moveCount;
    double friendship; // 友谊值，范围0-1000
    double MaxFriendship; // 最大友谊值
    int MaxFriendshipLevel; // 最大友谊等级
    int friendshipLevel; // 友谊等级，0-5颗心，每颗心250点友谊值
    bool isSingle; // 是否单身
    Gender _gender; // 性别
    RelationshipStatus _relationshipStatus;//关系
    std::string _name;


public:
    virtual bool init(Vec2 startPosition);
    virtual std::string getNPCName() const = 0;
    virtual void interact() = 0;
    virtual void update(float dt) = 0;
    void moveAround();
    void setImages();
    void createAnimations();
    float getRandomWaitTime() {
        std::random_device rd;  // 用于生成随机种子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 算法

        // 创建一个分布对象，指定范围
        std::uniform_real_distribution<> dis(1.0f, 3.0f);
        // 生成随机数
        return (float)dis(gen);
    };
    int getRandomRepeatTime() {return rand() % 3 + 10; };
    bool isAlive() { return _isAlive; }
    double getFriendship() const { return friendship; }
    void addFriendship(int value);
    void subtractFriendship(int value);
    void setRelationshipStatus(RelationshipStatus status) {
        _relationshipStatus = status;
    }
    void updateRelationship(bool isGiveFlower = false);
    Sprite* getCurrentSprite() { return _currentSprite; }
    RelationshipStatus getRelationshipStatus() const {
        return _relationshipStatus;
    }
    void talk() {
        _isTalk = true;
        this->stopAllActions();
        _currentLabel = labels.at(friendshipLevel);
        //对话框位置
        Vec2 spritePosition = _currentSprite->getPosition(); // 获取精灵的位置
        Size labelSize = _currentLabel->getContentSize(); // 获取 Label 的大小
        float yOffset = labelSize.height / 2; // 偏移量为 Label 高度的一半
        Vec2 labelPosition = spritePosition + Vec2(0, yOffset);
        // 显示对话框
        _currentLabel->setPosition(labelPosition);
        _currentLabel->setVisible(true);
        auto startAnimaiton = CallFunc::create([&]() {
            //CCLOG("start animation");
            _currentLabel->setVisible(true);
            });
        auto stopAnimation = CallFunc::create([&]() {
            //CCLOG("stop animation");
            _currentLabel->setVisible(false);
            });

        auto sequence = Sequence::create(startAnimaiton, DelayTime::create(2.0), stopAnimation, nullptr);
        this->runAction(sequence->clone());
        _currentLabel->setVisible(false);
    }
    virtual std::vector<Task*> getTasks() const = 0;
};
#endif // NPC_H


class Leah : public NPC {
public:
    virtual bool init(cocos2d::Vec2 startPosition) override {
        if (!Node::init())
            return false;

        _plistFile = "Leah.plist";
        _name = "Leah";
        isSingle = true;
        _gender = Gender::Female;
        _relationshipStatus = RelationshipStatus::Friend;
        NPC::init(startPosition);
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // 实现与Leah互动的逻辑
        addFriendship(30); // 假设每次互动增加30点友谊值
        talk(); // 显示对话框
    }
    void update(float dt) override {
        // 实现Leah的更新逻辑
        MaxFriendship =  (double)MaxFriendshipLevel * FRIENDSHIP_PER_LEVEL;

        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // 假设每天不互动减少25点友谊值
        }
        if (_currentFrame >= TOTAL_FRAME_DAY) {
            _currentFrame = 0;
            _isTalk = false;
        }
    }
    static Leah* create(cocos2d::Vec2 startPosition) {
        Leah* leah = new Leah();
        if (leah && leah->init(startPosition)) {
            leah->autorelease();
            return leah;
        }
        CC_SAFE_DELETE(leah);
        return nullptr;
    }

    virtual std::vector<Task*> getTasks() const override {
        std::vector<Task*> tasks;
        // 添加Leah发布的任务
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }
};


class Elliott : public NPC {
public:
    virtual bool init(cocos2d::Vec2 startPosition) override {
        if (!Node::init())
            return false;

        _plistFile = "Elliott.plist";
        _name = "Elliott";
        isSingle = true;
        _gender = Gender:: Male;
        _relationshipStatus = RelationshipStatus::Friend;
        NPC::init(startPosition);
   
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // 实现与Elliott互动的逻辑
        addFriendship(30); // 假设每次互动增加30点友谊值
        talk(); // 显示对话框
    }
    void update(float dt) override {
        // 实现Elliott的更新逻辑
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // 假设每天不互动减少25点友谊值
        }
        if (_currentFrame >= TOTAL_FRAME_DAY) {
            _currentFrame = 0;
            _isTalk = false;
        }
    }
    static Elliott* create(cocos2d::Vec2 startPosition) {
        Elliott* elliott = new Elliott();
        if (elliott && elliott->init(startPosition)) {
            elliott->autorelease();
            return elliott;
        }
        CC_SAFE_DELETE(elliott);
        return nullptr;
    }
    virtual std::vector<Task*> getTasks() const override {
        std::vector<Task*> tasks;
        // 添加Leah发布的任务
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }
};

class Alex : public NPC {
public:
    virtual bool init(cocos2d::Vec2 startPosition) override {
        if (!Node::init())
            return false;

        _plistFile = "Alex.plist";
        _name = "Alex";
        isSingle = true;
        _gender = Gender::Male;
        _relationshipStatus = RelationshipStatus:: Friend;
        NPC::init(startPosition);
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // 实现与Alex互动的逻辑
        addFriendship(30); // 假设每次互动增加30点友谊值b
        talk(); // 显示对话框
    }
    void update(float dt) override {
        // 实现Alex的更新逻辑
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // 假设每天不互动减少25点友谊值
        }
        if (_currentFrame >= TOTAL_FRAME_DAY) {
            _currentFrame = 0;
            _isTalk = false;
        }
    }
    static Alex* create(cocos2d::Vec2 startPosition) {
        Alex* alex = new Alex();
        if (alex && alex->init(startPosition)) {
            alex->autorelease();
            return alex;
        }
        CC_SAFE_DELETE(alex);
        return nullptr;
    }
    virtual std::vector<Task*> getTasks() const override {
        std::vector<Task*> tasks;
        // 添加Leah发布的任务
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }
};

class Amy : public NPC {
public:
    virtual bool init(cocos2d::Vec2 startPosition) override {
        if (!Node::init())
            return false;

        _plistFile = "Amy.plist";
        _name = "Amy";
        isSingle = true;
        _gender = Gender::Female;
        _relationshipStatus = RelationshipStatus:: Friend;
        NPC::init(startPosition);
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // 实现与Amy互动的逻辑
        addFriendship(30); // 假设每次互动增加30点友谊值
        talk(); // 显示对话框
    }
    void update(float dt) override {
        // 实现Amy的更新逻辑
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // 假设每天不互动减少25点友谊值
        }
        if (_currentFrame >= TOTAL_FRAME_DAY) {
            _currentFrame = 0;
            _isTalk = false;
        }
    }
    static Amy* create(cocos2d::Vec2 startPosition) {
        Amy* amy = new Amy();
        if (amy && amy->init(startPosition)) {
            amy->autorelease();
            return amy;
        }
        CC_SAFE_DELETE(amy);
        return nullptr;
    }
    virtual std::vector<Task*> getTasks() const override {
        std::vector<Task*> tasks;
        // 添加Leah发布的任务
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }

};

class Baby : public NPC {
public:
    virtual bool init(cocos2d::Vec2 startPosition) override {
        if (!Node::init())
            return false;

        _plistFile = "Baby.plist";
        _name = "Baby";
        isSingle = false; // 宝宝通常不参与恋爱关系
        _gender = Gender::Male; // 或Female，取决于具体情况
        _relationshipStatus = RelationshipStatus::Friend; // 默认关系为朋友
        NPC::init(startPosition);
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // 实现与宝宝互动的逻辑
        addFriendship(10); // 假设每次互动增加较少的友谊值，因为宝宝不能进行复杂的互动
    }
    void update(float dt) override {
        // 实现宝宝的更新逻辑
        // 宝宝可能不需要每天减少友谊值，因为他们不会因玩家未互动而感到不快
    }
    static Baby* create(cocos2d::Vec2 startPosition) {
        Baby* baby = new Baby();
        if (baby && baby->init(startPosition)) {
            baby->autorelease();
            return baby;
        }
        CC_SAFE_DELETE(baby);
        return nullptr;
    }
    virtual std::vector<Task*> getTasks() const override {
        std::vector<Task*> tasks;
        // 添加Baby的任务
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }
};

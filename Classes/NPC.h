#include <algorithm>
#include <vector>
#include "cocos2d.h"
#include"Animal.h"
#include"Task.h"

#define FRIENDSHIP_PER_LEVEL 250
USING_NS_CC;

const float FRONTSIZE = 15;


enum class RelationshipStatus {
    Neutral,    // ��ͨ����
    Friend,     // ����
    Lover,      // ����
    Married     // �ѻ�
};

enum class Gender {
    Male, //����
    Female//Ů��
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
    double friendship; // ����ֵ����Χ0-1000
    double MaxFriendship; // �������ֵ
    int MaxFriendshipLevel; // �������ȼ�
    int friendshipLevel; // ����ȼ���0-5���ģ�ÿ����250������ֵ
    bool isSingle; // �Ƿ���
    Gender _gender; // �Ա�
    RelationshipStatus _relationshipStatus;//��ϵ
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
        std::random_device rd;  // ���������������
        std::mt19937 gen(rd()); // ʹ�� Mersenne Twister �㷨

        // ����һ���ֲ�����ָ����Χ
        std::uniform_real_distribution<> dis(1.0f, 3.0f);
        // ���������
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
        //�Ի���λ��
        Vec2 spritePosition = _currentSprite->getPosition(); // ��ȡ�����λ��
        Size labelSize = _currentLabel->getContentSize(); // ��ȡ Label �Ĵ�С
        float yOffset = labelSize.height / 2; // ƫ����Ϊ Label �߶ȵ�һ��
        Vec2 labelPosition = spritePosition + Vec2(0, yOffset);
        // ��ʾ�Ի���
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
        // ʵ����Leah�������߼�
        addFriendship(30); // ����ÿ�λ�������30������ֵ
        talk(); // ��ʾ�Ի���
    }
    void update(float dt) override {
        // ʵ��Leah�ĸ����߼�
        MaxFriendship =  (double)MaxFriendshipLevel * FRIENDSHIP_PER_LEVEL;

        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // ����ÿ�첻��������25������ֵ
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
        // ���Leah����������
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
        // ʵ����Elliott�������߼�
        addFriendship(30); // ����ÿ�λ�������30������ֵ
        talk(); // ��ʾ�Ի���
    }
    void update(float dt) override {
        // ʵ��Elliott�ĸ����߼�
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // ����ÿ�첻��������25������ֵ
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
        // ���Leah����������
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
        // ʵ����Alex�������߼�
        addFriendship(30); // ����ÿ�λ�������30������ֵb
        talk(); // ��ʾ�Ի���
    }
    void update(float dt) override {
        // ʵ��Alex�ĸ����߼�
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // ����ÿ�첻��������25������ֵ
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
        // ���Leah����������
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
        // ʵ����Amy�������߼�
        addFriendship(30); // ����ÿ�λ�������30������ֵ
        talk(); // ��ʾ�Ի���
    }
    void update(float dt) override {
        // ʵ��Amy�ĸ����߼�
        if (_currentFrame == TOTAL_FRAME_DAY && !_isTalk) {
            subtractFriendship(25); // ����ÿ�첻��������25������ֵ
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
        // ���Leah����������
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
        isSingle = false; // ����ͨ��������������ϵ
        _gender = Gender::Male; // ��Female��ȡ���ھ������
        _relationshipStatus = RelationshipStatus::Friend; // Ĭ�Ϲ�ϵΪ����
        NPC::init(startPosition);
        return true;
    }
    virtual std::string getNPCName() const override {
        return _name;
    }
    void interact() override {
        // ʵ���뱦���������߼�
        addFriendship(10); // ����ÿ�λ������ӽ��ٵ�����ֵ����Ϊ�������ܽ��и��ӵĻ���
    }
    void update(float dt) override {
        // ʵ�ֱ����ĸ����߼�
        // �������ܲ���Ҫÿ���������ֵ����Ϊ���ǲ��������δ�������е�����
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
        // ���Baby������
        tasks.push_back(new Task(1, "Collect Eggs", "Collect 10 eggs from the chicken coop.", 10, 30, 10.0));
        tasks.push_back(new Task(2, "Milk the Cow", "Milk the cow 5 times.", 5, 15, 5.0));
        return tasks;
    }
};

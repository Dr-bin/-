#pragma once
#include "cocos2d.h"

USING_NS_CC;

// 使用示例
// 在你的场景或层的某个方法中:
// auto MC = CharacterAnimation::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MC); // 假设你在一个继承自Node的类中

class CharacterAnimation : public Sprite
{
public:
    // 成员变量，用于存储动画和精灵
    Sprite* CharacterD = nullptr;
    Sprite* CharacterL = nullptr;
    Sprite* CharacterU = nullptr;
    Sprite* CharacterR = nullptr;
    Sprite* CharacterDstop = nullptr;
    Sprite* CharacterLstop = nullptr;
    Sprite* CharacterUstop = nullptr;
    Sprite* CharacterRstop = nullptr;
    //添加判断WASD不能同时按下的变量
    unsigned short WASDisP_num = 0;
    //一些按键是否被按下的变量
    bool isKeyWPressed = false;                 //W键
    bool isKeySPressed = false;                 //S键
    bool isKeyAPressed = false;                 //A键
    bool isKeyDPressed = false;                 //D键
    bool isKeySPACEPressed = false;             //空格键
    bool isKeyESCAPEPressed = false;            //Esc键
    bool isKeyENTERPressed = false;             //Enter键
    bool isKeyBACKSPACEPressed = false;         //Backspace键
    bool isKey_0_Pressed = false;               //数字0键
    bool isKey_1_Pressed = false;               //数字1键
    bool isKey_2_Pressed = false;               //数字2键
    bool isKey_3_Pressed = false;               //数字3键
    bool isKey_4_Pressed = false;               //数字4键
    bool isKey_5_Pressed = false;               //数字5键
    bool isKey_6_Pressed = false;               //数字6键
    bool isKey_7_Pressed = false;               //数字7键
    bool isKey_8_Pressed = false;               //数字8键
    bool isKey_9_Pressed = false;               //数字9键
    //关于鼠标状态的变量
    bool isMouseButtonLeftPressed = false;      //左键
    bool isMouseButtonRightPressed = false;     //右键
    float MouseAbscissa = 0.1f;                //鼠标光标横坐标
    float MouseOrdinate = 0.1f;                //鼠标光标纵坐标
    float MouseScrollX = 0;                 //滚轮横向状态，恒为0
    float MouseScrollY = 0;                 //滚轮纵向状态，1为向上，-1为向下
    //一些状态变量
    int now_item = 1;                         //当前物品

    static CharacterAnimation* create(const std::string& plistFile, float frameDuration, float scale, const Vec2& position);

    bool init(const std::string& plistFile, float frameDuration, float scale, const Vec2& position);

	void StopMove();
    //dir=1,2,3,4:上下左右
	void Move(int dir);
    Vec2 getCharacterPosition();
    //以下为监听器部分
	virtual void update(float delta) override;

	//鼠标相关
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);
	void onMouseMove(EventMouse* event);
	void onMouseScroll(EventMouse* event);
	//键盘的回调函数
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //物理引擎相关
    bool onContactBegin(PhysicsContact& contact);
    //人物动作相关
    char get_facing();
    void useAxeToLeft();
    void useAxeToRight();
    void usePickToLeft();
    void usePickToRight();
    void useHoeToLeft();
    void useHoeToRight();
    void fetchWaterToLeft();
    void fetchWaterToRight();
    void fishingToLeft();
    void fishingToRight();
    void useTool();
    void wateringToLeft();
    void wateringToRight();
    
    PhysicsBody* body;

};
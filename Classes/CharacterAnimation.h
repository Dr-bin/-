#pragma once
#include "cocos2d.h"

USING_NS_CC;

// ʹ��ʾ��
// ����ĳ�������ĳ��������:
// auto MC = CharacterAnimation::create("farmer.plist", 0.2f, 4.0f, Vec2(200, 200));
// this->addChild(MC); // ��������һ���̳���Node������

class CharacterAnimation : public Sprite
{
public:
    // ��Ա���������ڴ洢�����;���
    Sprite* CharacterD = nullptr;
    Sprite* CharacterL = nullptr;
    Sprite* CharacterU = nullptr;
    Sprite* CharacterR = nullptr;
    Sprite* CharacterDstop = nullptr;
    Sprite* CharacterLstop = nullptr;
    Sprite* CharacterUstop = nullptr;
    Sprite* CharacterRstop = nullptr;
    //����ж�WASD����ͬʱ���µı���
    unsigned short WASDisP_num = 0;
    //һЩ�����Ƿ񱻰��µı���
    bool isKeyWPressed = false;                 //W��
    bool isKeySPressed = false;                 //S��
    bool isKeyAPressed = false;                 //A��
    bool isKeyDPressed = false;                 //D��
    bool isKeySPACEPressed = false;             //�ո��
    bool isKeyESCAPEPressed = false;            //Esc��
    bool isKeyENTERPressed = false;             //Enter��
    bool isKeyBACKSPACEPressed = false;         //Backspace��
    bool isKey_0_Pressed = false;               //����0��
    bool isKey_1_Pressed = false;               //����1��
    bool isKey_2_Pressed = false;               //����2��
    bool isKey_3_Pressed = false;               //����3��
    bool isKey_4_Pressed = false;               //����4��
    bool isKey_5_Pressed = false;               //����5��
    bool isKey_6_Pressed = false;               //����6��
    bool isKey_7_Pressed = false;               //����7��
    bool isKey_8_Pressed = false;               //����8��
    bool isKey_9_Pressed = false;               //����9��
    //�������״̬�ı���
    bool isMouseButtonLeftPressed = false;      //���
    bool isMouseButtonRightPressed = false;     //�Ҽ�
    float MouseAbscissa = 0.1f;                //����������
    float MouseOrdinate = 0.1f;                //�����������
    float MouseScrollX = 0;                 //���ֺ���״̬����Ϊ0
    float MouseScrollY = 0;                 //��������״̬��1Ϊ���ϣ�-1Ϊ����
    //һЩ״̬����
    int now_item = 1;                         //��ǰ��Ʒ

    static CharacterAnimation* create(const std::string& plistFile, float frameDuration, float scale, const Vec2& position);

    bool init(const std::string& plistFile, float frameDuration, float scale, const Vec2& position);

	void StopMove();
    //dir=1,2,3,4:��������
	void Move(int dir);
    Vec2 getCharacterPosition();
    //����Ϊ����������
	virtual void update(float delta) override;

	//������
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);
	void onMouseMove(EventMouse* event);
	void onMouseScroll(EventMouse* event);
	//���̵Ļص�����
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //�����������
    bool onContactBegin(PhysicsContact& contact);
    //���ﶯ�����
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
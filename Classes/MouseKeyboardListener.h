#pragma once
#include"cocos2d.h"
#include"global_variable.h"
USING_NS_CC;
using namespace std;
//��������ʹ�÷�����
/*
1.����ꡢ���̵Ļص��������Լ��ĳ�����������������
2.�ڳ������init���������������䣺
    auto keyboardListener = EventListenerKeyboard::create();
	auto mouseListener = EventListenerMouse::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MyScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MyScene::onKeyReleased, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MyScene::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MyScene::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(MyScene::onMouseMove, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MyScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
3.�����߼��ȿ���д�ڳ������ڵ���ĵ�updata���������global_variable���ȫ�ֱ���ʵ�֣���
4.�ڳ������ڵ����onEnter��������������scheduleUpdate����������this->scheduleUpdate()��
*/
//���Ļص�����
void onMouseDown(EventMouse* event)
{
    EventMouse::MouseButton button = event->getMouseButton();
    auto location = event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
        isMouseButtonLeftPressed = true;
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = true;
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void onMouseUp(EventMouse* event)
{
    EventMouse::MouseButton button = event->getMouseButton();
    auto location = event->getLocation();
    if (button == EventMouse::MouseButton::BUTTON_LEFT)
        isMouseButtonLeftPressed = false;
    if (button == EventMouse::MouseButton::BUTTON_RIGHT)
        isMouseButtonRightPressed = false;
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void onMouseMove(EventMouse* event)
{
    auto location = event->getLocation();
    MouseAbscissa = location.x;
    MouseOrdinate = location.y;
}
void onMouseScroll(EventMouse* event)
{
    MouseScrollX = event->getScrollX();
    MouseScrollY = event->getScrollX();
}
//���̵Ļص�����
void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	bool state = true;
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		isKeyWPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_S)
		isKeySPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
		isKeyAPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
		isKeyDPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		isKeySPACEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		isKeyESCAPEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		isKeyENTERPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		isKeyBACKSPACEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_0)
		isKey_0_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_1)
		isKey_1_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_2)
		isKey_2_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_3)
		isKey_3_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_4)
		isKey_4_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_5)
		isKey_5_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_6)
		isKey_6_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_7)
		isKey_7_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_8)
		isKey_8_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_9)
		isKey_9_Pressed = state;
}
void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	bool state = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		isKeyWPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_S)
		isKeySPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
		isKeyAPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
		isKeyDPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		isKeySPACEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		isKeyESCAPEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)
		isKeyENTERPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE)
		isKeyBACKSPACEPressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_0)
		isKey_0_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_1)
		isKey_1_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_2)
		isKey_2_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_3)
		isKey_3_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_4)
		isKey_4_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_5)
		isKey_5_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_6)
		isKey_6_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_7)
		isKey_7_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_8)
		isKey_8_Pressed = state;
	if (keyCode == EventKeyboard::KeyCode::KEY_9)
		isKey_9_Pressed = state;
}
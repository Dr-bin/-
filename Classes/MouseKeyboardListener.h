#pragma once
#include"cocos2d.h"
#include"global_variable.h"
USING_NS_CC;
using namespace std;
//监听器的使用方法：
/*
1.将鼠标、键盘的回调函数在自己的场景类中声明并定义
2.在场景类的init函数中添加下列语句：
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
3.触发逻辑等可以写在场景类或节点类的的updata函数里（利用global_variable里的全局变量实现）；
4.在场景类或节点类的onEnter函数里调用自身的scheduleUpdate函数，即：this->scheduleUpdate()；
*/
//鼠标的回调函数
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
//键盘的回调函数
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
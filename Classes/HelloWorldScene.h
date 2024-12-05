/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CharacterAnimation.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	CharacterAnimation* MC;

	//添加判断WASD不能同时按下的变量
	unsigned short WASDisP_num = 0;
	//添加一个判断人物是否移动的变量
	bool isNoMoving = 0;

	//一些按键是否被按下的变量
	bool isKeyWPressed;                 //W键
	bool isKeySPressed;                 //S键
	bool isKeyAPressed;                 //A键
	bool isKeyDPressed;                 //D键
	bool isKeySPACEPressed;             //空格键
	bool isKeyESCAPEPressed;            //Esc键
	bool isKeyENTERPressed;             //Enter键
	bool isKeyBACKSPACEPressed;         //Backspace键
	bool isKey_0_Pressed;               //数字0键
	bool isKey_1_Pressed;               //数字1键
	bool isKey_2_Pressed;               //数字2键
	bool isKey_3_Pressed;               //数字3键
	bool isKey_4_Pressed;               //数字4键
	bool isKey_5_Pressed;               //数字5键
	bool isKey_6_Pressed;               //数字6键
	bool isKey_7_Pressed;               //数字7键
	bool isKey_8_Pressed;               //数字8键
	bool isKey_9_Pressed;               //数字9键
	//关于鼠标状态的变量
	bool isMouseButtonLeftPressed;      //左键
	bool isMouseButtonRightPressed;     //右键
	float MouseAbscissa;                //鼠标光标横坐标
	float MouseOrdinate;                //鼠标光标纵坐标
	float MouseScrollX;                 //滚轮横向状态，恒为0
	float MouseScrollY;                 //滚轮纵向状态，1为向上，-1为向下

	virtual void update(float delta) override
	{
		WASDisP_num = 0;
		WASDisP_num += isKeySPressed;
		WASDisP_num += isKeyAPressed;
		WASDisP_num += isKeyWPressed;
		WASDisP_num += isKeyDPressed;
		if (WASDisP_num != 1) {//多于两个按键按下或无按下按键时停止不动
			MC->StopMove();
			isNoMoving = true;
			return;
		}

		if (isKeySPressed){
			MC->Move(1);
			MC->runAction(MoveBy::create(0.2f, Vec2(0, -2)));
		}

		if (isKeyAPressed){
			MC->Move(2); 
			MC->runAction(MoveBy::create(0.2f, Vec2(-2, 0)));
		}
			
		if (isKeyWPressed){
			MC->Move(3);
			MC->runAction(MoveBy::create(0.2f, Vec2(0, 2)));
		}
			
		if (isKeyDPressed){
			MC->Move(4);
			MC->runAction(MoveBy::create(0.2f, Vec2(2, 0)));
		}
			
		isNoMoving = false;

		return;
	}

	virtual void onEnter() override
	{
		Scene::onEnter();
		this->scheduleUpdate();
	}

	//鼠标相关
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

};

#endif // __HELLOWORLD_SCENE_H__

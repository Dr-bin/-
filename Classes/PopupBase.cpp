#include "PopupBase.h"
#include"menus.h"

// 静态变量，用于跟踪当前显示的弹窗
PopupBase* PopupBase::currentPopup = nullptr;

// 获取当前显示的弹窗
PopupBase* PopupBase::getCurrentPopup()
{
    return currentPopup;
}

// 关闭当前显示的弹窗
void PopupBase::closeCurrentPopup()
{
    if (currentPopup)
    {
        currentPopup->hide();
    }
}

// 初始化弹窗
bool PopupBase::init()
{
    if (!Node::init())
    {
        return false;
    }

    // 创建背景层
    //background = Sprite::create();
    //background->setColor(Color3B(0, 0, 0));
    //background->setOpacity(10);
    //background->setContentSize(Director::getInstance()->getWinSize());
    //this->addChild(background);

    // 创建弹窗容器
    popupContainer = Sprite::create("PopBkg.png");
    popupContainer->setPosition(Director::getInstance()->getWinSize() / 2);
    this->addChild(popupContainer);

    // 创建内容区域
    contentArea = Node::create();
    contentArea->setPosition(popupContainer->getContentSize() / 2);
    popupContainer->addChild(contentArea);

    // 创建关闭按钮背景
    closeBtnBg = Sprite::create("BtBkg.png");
    closeBtnBg->setPosition(Vec2(popupContainer->getContentSize().width - closeBtnBg->getContentSize().width / 2 - 10,
        popupContainer->getContentSize().height - closeBtnBg->getContentSize().height / 2 - 10));
    popupContainer->addChild(closeBtnBg);

    // 创建关闭按钮文字
    closeBtnLabel = Label::createWithTTF("X", "fonts/arial.ttf", 48);
    closeBtnLabel->setPosition(closeBtnBg->getContentSize() / 2);
    closeBtnBg->addChild(closeBtnLabel);

    auto pressLisener = EventListenerKeyboard::create();
    pressLisener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == stimulateKey) {
            this->show();
            return true;
        }
        return false;
        };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pressLisener, this);

    // 注册触摸事件监听器
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        //Vec2 touchLocation = popupContainer->convertToNodeSpace( touch->getLocation());
        //CCLOG("Touch location: (%f, %f)", touchLocation.x, touchLocation.y);
        //CCLOG("Close button bounds: (%f, %f) - (%f, %f)",
        //    closeBtnBg->getBoundingBox().getMinX(),
        //    closeBtnBg->getBoundingBox().getMinY(),
        //    closeBtnBg->getBoundingBox().getMaxX(),
        //    closeBtnBg->getBoundingBox().getMaxY());
        if (closeBtnBg->getBoundingBox().containsPoint(popupContainer->convertToNodeSpace(touch->getLocation())))
        {
            this->hide();
            return true;
        }
        return false;
        };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, closeBtnBg);

    show();
    hide();

    //// 为背景层添加触摸事件监听器，点击背景层也关闭弹窗，，这里忽略就行，当然你有需求也可以用上
    //auto backgroundListener = cocos2d::EventListenerTouchOneByOne::create();
    //backgroundListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
    //    if (this->background && this->background->getBoundingBox().containsPoint(this->background->convertToNodeSpace(touch->getLocation())))
    //    {
    //        this->hide();
    //        return true;
    //    }
    //    return false;
    //    };
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(backgroundListener, background);

    return true;
}

// 显示弹窗
void PopupBase::show()
{
    if (currentPopup != this)
    {
        if (currentPopup)
        {
            currentPopup->hide();
        }
        currentPopup = this;
        this->onShow();
        this->setVisible(true);
    }
}

// 隐藏弹窗
void PopupBase::hide()
{
    if (currentPopup == this)
    {
        currentPopup = nullptr;
        this->onHide();
        this->setVisible(false);
    }
}

bool PopupShop::init()
{
    if (!PopupBase::init())
    return false;
    //增加内容
    this->stimulateKey = EventKeyboard::KeyCode::KEY_O;
   
}

void PopupShop::onShow()
{
    //创建商店

    for (int i = 0; i < 5; i++) {
        auto shopBox = ShopBox::create();
        shopBox->item_bag = this->itemBag;
        shopBoxs.pushBack(shopBox);
        shopBox->setPosition(Vec2(popupContainer->getContentSize().width / 2 - 500, popupContainer->getContentSize().height / 2 - 50 - i * 50));
        contentArea->addChild(shopBox);

    }
   
    setShopBoxs(tags);
    _mouse= EventListenerMouse::create();
    _mouse->onMouseDown = CC_CALLBACK_1(PopupShop::OnMouseDown, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouse, this);
    
}

void PopupShop::onHide()
{
    this->shopBoxs.clear();
    this->contentArea->removeAllChildren();
    Director::getInstance()->getEventDispatcher()->removeEventListener(_mouse);
}

void PopupShop::setShopBoxs(int tags[5])
{
    auto items = ItemBag::create();
    for (int i = 0; i < 5; i++) {
        Item* item = items->getItem(tags[i]);
        //log("item name: %s", item->name);
        shopBoxs.at(i)->addProduction(item);
    }

}

void PopupShop::OnMouseDown(EventMouse* event)
{
    log("shop mouse down");
}

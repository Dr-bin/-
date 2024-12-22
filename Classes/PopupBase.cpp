#include "PopupBase.h"
#include"menus.h"

// ��̬���������ڸ��ٵ�ǰ��ʾ�ĵ���
PopupBase* PopupBase::currentPopup = nullptr;

// ��ȡ��ǰ��ʾ�ĵ���
PopupBase* PopupBase::getCurrentPopup()
{
    return currentPopup;
}

// �رյ�ǰ��ʾ�ĵ���
void PopupBase::closeCurrentPopup()
{
    if (currentPopup)
    {
        currentPopup->hide();
    }
}

// ��ʼ������
bool PopupBase::init()
{
    if (!Node::init())
    {
        return false;
    }

    // ����������
    //background = Sprite::create();
    //background->setColor(Color3B(0, 0, 0));
    //background->setOpacity(10);
    //background->setContentSize(Director::getInstance()->getWinSize());
    //this->addChild(background);

    // ������������
    popupContainer = Sprite::create("PopBkg.png");
    popupContainer->setPosition(Director::getInstance()->getWinSize() / 2);
    this->addChild(popupContainer);

    // ������������
    contentArea = Node::create();
    contentArea->setPosition(popupContainer->getContentSize() / 2);
    popupContainer->addChild(contentArea);

    // �����رհ�ť����
    closeBtnBg = Sprite::create("BtBkg.png");
    closeBtnBg->setPosition(Vec2(popupContainer->getContentSize().width - closeBtnBg->getContentSize().width / 2 - 10,
        popupContainer->getContentSize().height - closeBtnBg->getContentSize().height / 2 - 10));
    popupContainer->addChild(closeBtnBg);

    // �����رհ�ť����
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

    // ע�ᴥ���¼�������
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

    //// Ϊ��������Ӵ����¼������������������Ҳ�رյ�������������Ծ��У���Ȼ��������Ҳ��������
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

// ��ʾ����
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

// ���ص���
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
    //��������
    this->stimulateKey = EventKeyboard::KeyCode::KEY_O;
   
}

void PopupShop::onShow()
{
    //�����̵�

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

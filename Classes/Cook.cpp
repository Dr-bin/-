#include "Cook.h"

bool Cook::init() {

    if (!PopupBase::init())
    {
        return false;
    }
    stimulateKey = EventKeyboard::KeyCode::KEY_C;

    onShow();

    // 注册触摸事件监听器
    touchListener_1 = EventListenerTouchOneByOne::create();
    touchListener_1->onTouchBegan = [this](Touch* touch, Event* event) {

        auto pos = touch->getLocation();
        pos = contentArea->convertToNodeSpace(pos);
        CCLOG("%f %f", pos.x, pos.y);

        auto size = cook_origin1->box->getBoundingBox();
        CCLOG("%f %f %f %f", size.getMinX(), size.getMaxX(), size.getMinY(), size.getMaxY());
        auto size1 = cook_origin2->box->getBoundingBox();
        CCLOG("%f %f %f %f", size1.getMinX(), size1.getMaxX(), size1.getMinY(), size1.getMaxY());
        auto size2 = cook_origin3->box->getBoundingBox();
        CCLOG("%f %f %f %f", size2.getMinX(), size2.getMaxX(), size2.getMinY(), size2.getMaxY());
        auto size3 = cook_result->box->getBoundingBox();
        CCLOG("%f %f %f %f", size3.getMinX(), size3.getMaxX(), size3.getMinY(), size3.getMaxY());



        if (isinpos(pos,size.getMinX(),size.getMaxX(), size.getMinY(), size.getMaxY()))//第一个
        {
            if (cook_origin1->content != NULL) {
                bag->addItem(cook_origin1->contentTag, 1);
                cook_origin1->removeContent();
            }
            return true;
        }
        if (isinpos(pos, size1.getMinX(), size1.getMaxX(), size1.getMinY(), size1.getMaxY()))//第二个
        {
            if (cook_origin2->content != NULL) {
                bag->addItem(cook_origin2->contentTag, 1);
                cook_origin2->removeContent();
            }
            return true;
        }
        if (isinpos(pos, size2.getMinX(), size2.getMaxX(), size2.getMinY(), size2.getMaxY()))//第三个
        {
            if (cook_origin3->content != NULL) {
                bag->addItem(cook_origin3->contentTag, 1);
                cook_origin3->removeContent();
            }
            return true;
        }
        if (isinpos(pos, size3.getMinX(), size3.getMaxX(), size3.getMinY(), size3.getMaxY()))//结果
        {
            if (cook_result->content != NULL) {
                bag->addItem(cook_result->contentTag, 1);
                cook_result->removeContent();
            }
            return true;
        }
        if (uptocookBt->getBoundingBox().containsPoint(pos))//物品栏上放按钮
        {
            if (bag->now_select >= 0) {
                if (cook_origin1->content == NULL) {
                    cook_origin1->addContent(bag->getItem(bag->now_select+1));
                    bag->removeItem(bag->serchItem(bag->now_select+1), 1);
                    return true;
                }
                if (cook_origin2->content == NULL) {
                    cook_origin2->addContent(bag->getItem(bag->now_select+1));
                    bag->removeItem(bag->serchItem(bag->now_select+1), 1);
                    return true;
                }
                if (cook_origin3->content == NULL) {
                    cook_origin3->addContent(bag->getItem(bag->now_select+1));
                    bag->removeItem(bag->serchItem(bag->now_select+1), 1);
                    return true;
                }
            }
            return true;
        }
        if (mixBt->getBoundingBox().containsPoint(pos))//结果
        {
            if (cook_origin1->content == NULL && cook_origin2->content == NULL && cook_origin3->content == NULL)
                return true;
            int sum = 0;
            if (cook_origin1->content != NULL) {
                sum += cook_origin1->contentTag;
                cook_origin1->removeContent();
            }

            if (cook_origin2->content != NULL) {
                sum += cook_origin2->contentTag;
                cook_origin2->removeContent();
            }

            if (cook_origin3->content != NULL) {
                sum += cook_origin3->contentTag;
                cook_origin3->removeContent();
            }

            if (sum <= MaxItemNum)
                cook_result->addContent(bag->getItem(sum));
            else
                cook_result->addContent(bag->getItem(ItemGarbageTag));

            return true;
        }
        return false;
        };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener_1, contentArea);

    contentArea->setScale(1.0f);

    return true;
}

void Cook::onShow()
{
    cook_origin1 = SquareBox::create();
    cook_origin2 = SquareBox::create();
    cook_origin3 = SquareBox::create();
    cook_result = SquareBox::create();
    log("cooking");
    auto boardsize = popupContainer->getContentSize();
    auto w = boardsize.width;
    auto h = boardsize.height;
    auto dx = w / 6;//算一个偏移

    contentArea->addChild(cook_origin1);
    contentArea->addChild(cook_origin2);
    contentArea->addChild(cook_origin3);
    contentArea->addChild(cook_result);

    cook_origin1->box->setPosition(-1.5 * dx, 0);
    cook_origin2->box->setPosition(-0.5 * dx, 0);
    cook_origin3->box->setPosition(0.5 * dx, 0);
    cook_result->box->setPosition(1.5 * dx, 0);

    auto Poptitle = Label::createWithSystemFont("Let`s Cook!", "Garamond", 36);
    Poptitle->setPosition(0.0f, h / 4);
    contentArea->addChild(Poptitle);

    uptocookBt = Sprite::create("BtBkg.png");//上放按钮
    contentArea->addChild(uptocookBt);
    uptocookBt->setPosition(1.1 * dx, -(h / 4));

    mixBt = Sprite::create("BtBkg.png");//混合按钮
    contentArea->addChild(mixBt);
    mixBt->setPosition(1.6 * dx, -(h / 4));



    return;
}

void Cook::onHide()
{

    return;
}
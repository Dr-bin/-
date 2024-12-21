#include "menus.h"

// Menubox类的初始化方法
bool Menubox::init()
{
    if(!Node::init())
    return false;
    this->setAnchorPoint(Vec2(0.5,0.5));
    return true;
}

// SquareBox类的初始化方法
bool SquareBox::init()
{
    if(!Menubox::init())
    return false;
    this->box=Sprite::create("square_box.png");
    box->setScale(0.12);
    this->addChild(this->box);
    return true;
}

// 为物品栏添加物品
void SquareBox::addContent(Item* item)
{
    
    this->contentTag=item->tag;
    this->content=item;
    this->addChild(this->content);
    this->content->setPosition(this->box->getPosition());
}

// 移除物品栏中的物品
void SquareBox::removeContent()
{
    if(this->content!=nullptr)
    {
        this->removeChild(this->content);
        this->contentTag=-1;
        this->content=nullptr;
    }
    return;
}

// 获取物品栏中的物品tag
int SquareBox::getContentTag()
{
    if(this->content!=nullptr)
    {
        return contentTag;
    }
    return -1;
}

// Item类的初始化方法
bool Item::init()
{
    if(!Node::init())
    return false;
    this->setAnchorPoint(Vec2(0.5,0.5));
    this->num = 1;
    this->num_label = Label::create();
    std::string num = std::to_string(this->num);
    num_label->setString(num);
    this->addChild(this->num_label);
    num_label->setPosition(Vec2(10,-10));
    return true;
}

// 更新物品数量
void Item::updateNum(int num)
{
    this->num = num;
    std::string num_str = std::to_string(this->num);
    this->num_label->setString(num_str);
}

// 修改数量标签
void Item::changelabel(std::string str)
{
    this->num_label->setString(str);
}

// ItemAxe类的初始化方法
bool ItemAxe::init()
{
    if(!Item::init())
    return false;
    this->tag=1;
    num=1;
    this->name="Axe";
    this->item=Sprite::create("items/axe.png");
    this->item->setScale(0.4);
    this->addChild(this->item);
    return true;
}

// ItemHoe类的初始化方法
bool ItemHoe::init()
{
    if(!Item::init())
    return false;
    this->tag=2;
    this->num=1;
    this->name="Hoe";
    this->item=Sprite::create("items/hoe.png");
    this->item->setScale(0.8);
    this->addChild(this->item);
    return true;
}

// ItemPick类的初始化方法
bool ItemPick::init() {
    if(!Item::init())
    return false;
    this->tag=3;
    this->num=1;
    this->name="Pick";
    this->item=Sprite::create("items/pick.png");
    this->item->setScale(0.8);
    this->addChild(this->item);
    return true;
}

// ItemBucket类的初始化方法
bool ItemBucket::init()
{
    if(!Item::init())
    return false;
    this->tag=4;
    this->num=1;
    this->name="Bucket";
    this->item=Sprite::create("items/bucket.png");
    this->item->setScale(0.8);
    this->addChild(this->item);
    return true;
}

// ItemLayer类的初始化方法
bool ItemLayer::init()
{
    if(!Layer::init())
    return false;
    item_bag = ItemBag::create();
    this->addChild(item_bag);
    return true;
}
 

// ItemBag类的初始化方法
bool ItemBag::init()
{
    if(!Node::init())
    return false;
    for (int i = 0;i < 12;i++) {
        auto squarebox = SquareBox::create();
        squarebox->setPosition(Vec2(700+40*i,200));
        this->addChild(squarebox);
        square_boxes.pushBack(squarebox);
    }
    cur = Sprite::create("cursor.png");
    this->addChild(cur);
    cur->setRotation(-155);
    auto _mouselistener = EventListenerMouse::create();
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouselistener, this);
    addItem(1, 2);
    addItem(1, 3);
    addItem(3, 5);
    addItem(2, 4);
    addItem(4, 1);
    addItem(5, 1);
    addItem(6, 1);
    addItem(5, 2);
    addItem(7, 2);
    addItem(8, 6);
    addItem(9, 1);
    addItem(10, 1);
    addItem(11, 5);
    addItem(9, 4);
    this->selectItem(0);
    return true;
}

// 获取当前选中的物品
Item* ItemBag::getNowItem()
{
    if (now_select < 0 || now_select >= 12) {
        return nullptr;
    }
    return square_boxes.at(now_select)->content;
}

// 根据tag获取物品
Item* ItemBag::getItem(int tag)
{
    switch (tag)
    {
    case 1:
        return ItemAxe::create();
        break;
    case 2:
        return ItemHoe::create();
        break;
    case 3:
        return ItemPick::create();
        break;
    case 4:
        return ItemBucket::create();
        break;
    case 5:
        return ItemPotatoSeed::create();
        break;
    case 6:
        return ItemPotato::create();
        break;
    case 7:
        return ItemCarrot::create();
        break;
    case 8:
        return ItemCarrotSeed::create();
        break;
    case 9:
        return ItemPumpkinSeed::create();
        break;
    case 10:
        return ItemPumpkin::create();
        break;
    case 11:
        return ItemMilk::create();
        break;
    default:
        break;
        
    }
    return nullptr;
}

// 添加物品到物品栏
void ItemBag::addItem(int tag, int num)
{
    Item* item=getItem(tag);
    if (this->serchItem(tag) != -1) {
        square_boxes.at(serchItem(tag))->content->updateNum(square_boxes.at(serchItem(tag))->content->num + num);
        return;
    }
  
    for (int i = 0;i < square_boxes.size();i++) {
        if (square_boxes.at(i)->getContentTag() == -1) {
            square_boxes.at(i)->addContent(item);
            item->updateNum(num);
            break;
        }
    }
    return;
}

// 移除指定位置的物品
void ItemBag::removeItem(int pos, int num)
{
    if (pos < 0 || pos >= 12) {
        return;
    }
    if (num > square_boxes.at(pos)->content->num) {
        num = square_boxes.at(pos)->content->num;
    }
    square_boxes.at(pos)->content->updateNum(square_boxes.at(pos)->content->num - num);
    if (square_boxes.at(pos)->content->num <= 0) {
        square_boxes.at(pos)->removeContent();
        for (int i = 0;i < 12;i++) {
            if(square_boxes.at(i)->getContentTag() == -1)
            {
                for (int j = i;j < 12;j++) {
                    if(square_boxes.at(j)->getContentTag() != -1)
                    {
                        square_boxes.at(i)->addContent(square_boxes.at(j)->content);
                        square_boxes.at(j)->removeContent();
                        break;
                    }
                    
                }
            }
        }
        
    }
}

// 选择物品
void ItemBag::selectItem(int pos)
{
    if (pos < 0 || pos >= 12) {
        return;
    }
    if (square_boxes.at(pos)->content == nullptr) 
    {
        log("can't choose this!");
        return;
    }
    cur->setPosition(Vec2(700+40*pos,225));
    now_select=pos;
    return;
}

// 搜索物品
int ItemBag::serchItem(int tag)
{
    for (int i = 0;i < 12;i++) {
        if (square_boxes.at(i)->content != nullptr && square_boxes.at(i)->content->tag == tag) {
            return i;
        }
    }
    return -1;
}

// 鼠标点击事件处理
int ItemBag::onMouseDown(Event* event)
{
    try {
        auto mouse_event = static_cast<EventMouse*>(event);
        int x = mouse_event->getCursorX();
        int y = mouse_event->getCursorY();
        if (x >= 680 && x <= 1160 && y >= 180 && y <= 225) {
            int pos = (x - 680) / 40;
            selectItem(pos);
            if (square_boxes.at(pos)->content != nullptr) {
                return square_boxes.at(pos)->content->tag;
            }

        }
    }
    catch (...) {
        return -2;
    }
    return -2;
}

// ItemPotatoSeed类的初始化方法
bool ItemPotatoSeed::init()
{
    if(!Item::init())
    return false;
    this->tag=5;
    this->num=1;
    this->name="Potato Seed";
    this->item=Sprite::create("items/potato_seed.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemPotato类的初始化方法
bool ItemPotato::init()
{
    if(!Item::init())
    return false;
    this->tag=6;
    this->num=1;
    this->name="Potato";
    this->item=Sprite::create("items/potato.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemCarrot类的初始化方法
bool ItemCarrot::init()
{
    if(!Item::init())
    return false;
    this->tag=7;
    this->num = 1;
    this->name = "Carrot";
    this->item = Sprite::create("items/carrot.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemCarrotSeed类的初始化方法
bool ItemCarrotSeed::init()
{
    if(!Item::init())
    return false;
    this->tag=8;
    this->num = 1;
    this->name = "Carrot Seed";
    this->item = Sprite::create("items/carrot_seed.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemPumpkinSeed类的初始化方法
bool ItemPumpkinSeed::init()
{
    if(!Item::init())
    return false;
    this->tag=9;
    this->num = 1;
    this->name = "Pumpkin Seed";
    this->item = Sprite::create("items/pumpkin_seed.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemPumpkin类的初始化方法
bool ItemPumpkin::init()
{
    if(!Item::init())
    return false;
    this->tag=10;
    this->num = 1;
    this->name = "Pumpkin";
    this->item = Sprite::create("items/pumpkin.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

// ItemMilk类的初始化方法
bool ItemMilk::init()
{
    if(!Item::init())
    return false;
    this->tag=11;
    this->num = 1;
    this->name = "Milk";
    this->item = Sprite::create("items/milk.png");
    this->item->setScale(1.5);
    this->addChild(this->item);
    return true;
}

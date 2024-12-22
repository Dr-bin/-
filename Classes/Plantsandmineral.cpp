#include"Plantsandmineral.h"
USING_NS_CC;
using namespace std;
// 创建植物实例
Plant* Plant:: create(const std::string& springSprite, const std::string& summerSprite,
    const std::string& autumnSprite, const std::string& winterSprite)
{
    Plant* plant = new Plant();
    if (plant && plant->init(springSprite, summerSprite, autumnSprite, winterSprite))
    {
        plant->autorelease();
        return plant;
    }
    CC_SAFE_DELETE(plant);
    return nullptr;
}
// 初始化植物
bool Plant::init(const std::string& springSprite, const std::string& summerSprite,
    const std::string& autumnSprite, const std::string& winterSprite)
{
    if (!cocos2d::Node::init())
        return false;
    _spriteSpring = cocos2d::Sprite::create(springSprite);
    _spriteSummer = cocos2d::Sprite::create(summerSprite);
    _spriteAutumn = cocos2d::Sprite::create(autumnSprite);
    _spriteWinter = cocos2d::Sprite::create(winterSprite);
    _originalContentSize = _spriteSpring->getContentSize();
    if (_spriteSpring && _spriteSummer && _spriteAutumn && _spriteWinter)
    {
        _spriteWinter->setVisible(false);
        _spriteSummer->setVisible(false);
        _spriteAutumn->setVisible(false);
        addChild(_spriteSpring);
        addChild(_spriteSummer);
        addChild(_spriteAutumn);
        addChild(_spriteWinter);
        _currentSprite = _spriteSpring; // 默认显示春季图像
        _health = 3;
        _currentSeason = 0;
        _isTregger = 0;
        this->scheduleUpdate();
        _scaleFactor = 1.0f;
        //this->schedule(CC_SCHEDULE_SELECTOR(Plant::updateSeason), switchtime);
        return true;
    }
    return false;
}
//控制季节变换
void Plant::update(float dt)
{
    if (_isTregger)
        return;
    timeSinceLastSeasonChange += dt;
    //timeSinceLastSeasonChange >= switchtime &&
    // 检查是否已经过去了switchtime秒
    if (timeSinceLastSeasonChange >= switchtime && !_isTregger)
    {
        CCLOG("1");
        timeSinceLastSeasonChange = 0.0f; // 重置计时器
        _currentSeason = (_currentSeason + 1) % 4; // 循环季节
        switchSeason(_currentSeason);
    }
}
// 更新植物的季节显示
void Plant::switchSeason(int season)
{
    switch (season) {
        case 0:
            _currentSprite->setVisible(false);
            _spriteSpring->setVisible(true);
            _currentSprite = _spriteSpring;
            break;
        case 1:
            _currentSprite->setVisible(false);
            _spriteSummer->setVisible(true);
            _currentSprite = _spriteSummer;
            break;
        case 2:
            _currentSprite->setVisible(false);
            _spriteAutumn->setVisible(true);
            _currentSprite = _spriteAutumn;
            break;
        case 3:
            _currentSprite->setVisible(false);
            _spriteWinter->setVisible(true);
            _currentSprite = _spriteWinter;
            break;
    }
}
// 减少生命值
void Plant::damage(int amount) {
    _health -= amount;
    if (_health <= 0) {
        _isTregger = 1;
        fallDownAndDisappear();
        return;
    }
}
// 树倒下和消失的动画
void Plant::fallDownAndDisappear()
{
    auto toRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(20, 0)); // 向右移动
    auto rotate = cocos2d::RotateTo::create(0.1f, 90); // 旋转90度
    auto fadeOut = cocos2d::FadeOut::create(0.5f); // 0.5秒内淡出
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Plant::removeThis, this)); // 旋转后移除自身
    auto sequence = cocos2d::Sequence::create(toRight, rotate, fadeOut, call,nullptr); // 先移动再旋转
    //auto spawn = cocos2d::Spawn::create(sequence, call, nullptr); // 同时执行
    //removeThis();
    _currentSprite->runAction(sequence);
    return;
}
// 移除自身的函数
void Plant::removeThis() 
{
    this->removeFromParent();
}
Size Plant::getcontentSize()
{
    // 返回缩放后的内容大小
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}


// 创建矿石实例
Mineral* Mineral::create(const string& spriteFile)
{
    Mineral* mineral = new Mineral();
    if (mineral && mineral->init(spriteFile)) {
        mineral->autorelease();
        return mineral;
    }
    CC_SAFE_DELETE(mineral);
    return nullptr;
}
// 初始化矿石
bool Mineral:: init(const string& spriteFile)
{
    if (!cocos2d::Node::init())
        return false;
    _sprite = Sprite::create(spriteFile);
    if (_sprite)
    {
        addChild(_sprite);
        _sprite->setVisible(true);
        _state = 1;
        _health = 3;
        _scaleFactor = 1.0;
        _originalContentSize = _sprite->getContentSize();
        return true;
    }
    return false;
}
// 减少生命值
void Mineral::damage(int amount)
{
    _health -= amount;
    if (_health <= 0)
    {
        _state = 0;
        Disappear();
    }
}
// 开采矿石
void Mineral::Disappear()
{
    auto toRight = cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(20, 0)); // 向右移动
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5秒内淡出
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Mineral::removeThis, this)); // 移除自身
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _sprite->runAction(toRight);
    _sprite->runAction(sequence);
}
//移除自身
void Mineral::removeThis()
{
    this->removeFromParent();
}
Size Mineral::getcontentSize()
{
    // 返回缩放后的内容大小
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}


// 创建作物实例
Crop* Crop::create(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& finalSprite)
{
    Crop* crop = new Crop();
    if (crop && crop->init(seedSprite,youngSprite,matureSprite,finalSprite))
    {
        crop->autorelease();
        return crop;
    }
    CC_SAFE_DELETE(crop);
    return nullptr;
}
// 初始化作物
bool Crop::init(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& finalSprite)
{
    if (!Node::init())
        return false;
    _seedSprite = Sprite::create(seedSprite);
    _youngSprite = Sprite::create(youngSprite);
    _matureSprite = Sprite::create(matureSprite);
    _finalSprite = Sprite::create(finalSprite);
    _deadSprite = Sprite::create("crop/crop_dead.png");
    _originalContentSize = _seedSprite->getContentSize();
    if (_seedSprite && _youngSprite && _matureSprite && _finalSprite&&_deadSprite)
    {
        _finalSprite->setVisible(false);
        _youngSprite->setVisible(false);
        _matureSprite->setVisible(false);
        _deadSprite->setVisible(false);
        addChild(_seedSprite);
        addChild(_youngSprite);
        addChild(_matureSprite);
        addChild(_finalSprite);
        addChild(_deadSprite);
        _currentSprite = _seedSprite; // 默认显示种子
        _growthstage = 1;    //种子状态
        ifgrow = 1;    //默认为成长状态
        growspeed = 2;
        _health = 10;
        ifripe = 0;    //还未成熟
        ifwithered = 0;    //并未枯萎
        _scaleFactor = 1.0f;
        this->scheduleUpdate();
        return true;
    }
    return false;
}
// 更新作物状态
void Crop::update(float dt)
{
    if (ifwithered)    //如果作物已经枯萎，转态无需更新
        return;
    timeSince += dt;
    if (irrigatetime > 0.0)
    {
        irrigatetime -= dt;
        if (irrigatetime <= 0.0)
        {
            irrigatetime = 0.0;
            growspeed = 1;
        }
    }
    // 检查是否已经过去了switchtime秒
    if (timeSince >= 1.0)    //每1s变化一次
    {
        timeSince = 0.0f; // 重置计时器
        if (ifgrow)
        {
            if (!ifripe&&_health<=40)
                _health += growspeed;
            //log("%d %d", _health, _growthstage);
        }
        else
        {
            _health--;
        }
        if (_health <= 0)
        {
            ifwithered = 1;
            _growthstage = 0;
            switchwithered();
        }
        if (_growthstage < _health / 10)
        {
            _growthstage++;
            switchstage();
            if (_growthstage == 4)
                ifripe = 1;
        }
    }
}
//更新作物状态
void Crop::switchstage()
{
    //log("%d", _growthstage);
    switch (_growthstage)
    {
        case 2:
            _currentSprite->setVisible(false);
            _youngSprite->setVisible(true);
            _currentSprite = _youngSprite;
            break;
        case 3:
            _currentSprite->setVisible(false);
            _matureSprite->setVisible(true);
            _currentSprite = _matureSprite;
            break;
        case 4:
            _currentSprite->setVisible(false);
            _finalSprite->setVisible(true);
            _currentSprite = _finalSprite;
            break;
    }
}
//作物被摧毁
void Crop::damage()
{
    Disappear();
}
//作物枯萎
void Crop::switchwithered()
{
    _currentSprite->setVisible(false);
    _deadSprite->setVisible(true);
    _currentSprite = _deadSprite;
}
// 作物消失
void Crop::Disappear()
{
    auto toRight = cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(20, 0)); // 向右移动
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5秒内淡出
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Crop::removeThis, this)); // 移除自身
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _currentSprite->runAction(toRight);
    _currentSprite->runAction(sequence);
}
// 作物被采摘
void Crop::Pick()
{
    auto toRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, 20)); // 向上
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5秒内淡出
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Crop::removeThis, this)); // 移除自身
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _currentSprite->runAction(toRight);
    _currentSprite->runAction(sequence);
}
// 移除自身
void Crop::removeThis()
{
    this->removeFromParent();
}
//获取作物状态
int Crop::getstage()
{
    return _growthstage;
}
Size Crop::getcontentSize()
{
    // 返回缩放后的内容大小
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}



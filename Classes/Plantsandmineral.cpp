#include"Plantsandmineral.h"
USING_NS_CC;
using namespace std;
// ����ֲ��ʵ��
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
// ��ʼ��ֲ��
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
        _currentSprite = _spriteSpring; // Ĭ����ʾ����ͼ��
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
//���Ƽ��ڱ任
void Plant::update(float dt)
{
    if (_isTregger)
        return;
    timeSinceLastSeasonChange += dt;
    //timeSinceLastSeasonChange >= switchtime &&
    // ����Ƿ��Ѿ���ȥ��switchtime��
    if (timeSinceLastSeasonChange >= switchtime && !_isTregger)
    {
        CCLOG("1");
        timeSinceLastSeasonChange = 0.0f; // ���ü�ʱ��
        _currentSeason = (_currentSeason + 1) % 4; // ѭ������
        switchSeason(_currentSeason);
    }
}
// ����ֲ��ļ�����ʾ
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
// ��������ֵ
void Plant::damage(int amount) {
    _health -= amount;
    if (_health <= 0) {
        _isTregger = 1;
        fallDownAndDisappear();
        return;
    }
}
// �����º���ʧ�Ķ���
void Plant::fallDownAndDisappear()
{
    auto toRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(20, 0)); // �����ƶ�
    auto rotate = cocos2d::RotateTo::create(0.1f, 90); // ��ת90��
    auto fadeOut = cocos2d::FadeOut::create(0.5f); // 0.5���ڵ���
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Plant::removeThis, this)); // ��ת���Ƴ�����
    auto sequence = cocos2d::Sequence::create(toRight, rotate, fadeOut, call,nullptr); // ���ƶ�����ת
    //auto spawn = cocos2d::Spawn::create(sequence, call, nullptr); // ͬʱִ��
    //removeThis();
    _currentSprite->runAction(sequence);
    return;
}
// �Ƴ�����ĺ���
void Plant::removeThis() 
{
    this->removeFromParent();
}
Size Plant::getcontentSize()
{
    // �������ź�����ݴ�С
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}


// ������ʯʵ��
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
// ��ʼ����ʯ
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
// ��������ֵ
void Mineral::damage(int amount)
{
    _health -= amount;
    if (_health <= 0)
    {
        _state = 0;
        Disappear();
    }
}
// ���ɿ�ʯ
void Mineral::Disappear()
{
    auto toRight = cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(20, 0)); // �����ƶ�
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5���ڵ���
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Mineral::removeThis, this)); // �Ƴ�����
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _sprite->runAction(toRight);
    _sprite->runAction(sequence);
}
//�Ƴ�����
void Mineral::removeThis()
{
    this->removeFromParent();
}
Size Mineral::getcontentSize()
{
    // �������ź�����ݴ�С
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}


// ��������ʵ��
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
// ��ʼ������
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
        _currentSprite = _seedSprite; // Ĭ����ʾ����
        _growthstage = 1;    //����״̬
        ifgrow = 1;    //Ĭ��Ϊ�ɳ�״̬
        growspeed = 2;
        _health = 10;
        ifripe = 0;    //��δ����
        ifwithered = 0;    //��δ��ή
        _scaleFactor = 1.0f;
        this->scheduleUpdate();
        return true;
    }
    return false;
}
// ��������״̬
void Crop::update(float dt)
{
    if (ifwithered)    //��������Ѿ���ή��ת̬�������
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
    // ����Ƿ��Ѿ���ȥ��switchtime��
    if (timeSince >= 1.0)    //ÿ1s�仯һ��
    {
        timeSince = 0.0f; // ���ü�ʱ��
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
//��������״̬
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
//���ﱻ�ݻ�
void Crop::damage()
{
    Disappear();
}
//�����ή
void Crop::switchwithered()
{
    _currentSprite->setVisible(false);
    _deadSprite->setVisible(true);
    _currentSprite = _deadSprite;
}
// ������ʧ
void Crop::Disappear()
{
    auto toRight = cocos2d::MoveBy::create(0.3f, cocos2d::Vec2(20, 0)); // �����ƶ�
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5���ڵ���
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Crop::removeThis, this)); // �Ƴ�����
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _currentSprite->runAction(toRight);
    _currentSprite->runAction(sequence);
}
// ���ﱻ��ժ
void Crop::Pick()
{
    auto toRight = cocos2d::MoveBy::create(0.2f, cocos2d::Vec2(0, 20)); // ����
    auto fadeOut = cocos2d::FadeOut::create(0.3f); // 0.5���ڵ���
    auto call = cocos2d::CallFunc::create(CC_CALLBACK_0(Crop::removeThis, this)); // �Ƴ�����
    auto sequence = cocos2d::Sequence::create(fadeOut, call, nullptr);
    _currentSprite->runAction(toRight);
    _currentSprite->runAction(sequence);
}
// �Ƴ�����
void Crop::removeThis()
{
    this->removeFromParent();
}
//��ȡ����״̬
int Crop::getstage()
{
    return _growthstage;
}
Size Crop::getcontentSize()
{
    // �������ź�����ݴ�С
    return Size(_originalContentSize.width * _scaleFactor, _originalContentSize.height * _scaleFactor);
}



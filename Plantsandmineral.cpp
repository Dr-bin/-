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
        this->schedule(CC_SCHEDULE_SELECTOR(Plant::updateSeasons), switchtime);
        return true;
    }
    return false;
}
//���Ƽ��ڱ任
void Plant::updateSeasons(float dt)
{
    if (_isTregger)
        return;
    static float timeSinceLastSeasonChange = 0.0f;
    timeSinceLastSeasonChange += dt;

    // ����Ƿ��Ѿ���ȥ��switchtime��
    if (timeSinceLastSeasonChange >= switchtime && !_isTregger)
    {
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
    //removeThis();
    return;
}
// �Ƴ�����ĺ���
void Plant::removeThis() {
    this->removeFromParent();
}


// ������ʯʵ��
Mineral* Mineral::create(const std::string& spriteFile)
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
bool Mineral:: init(const std::string& spriteFile)
{
    if (!cocos2d::Node::init())
        return false;
    _sprite = cocos2d::Sprite::create(spriteFile);
    if (_sprite)
    {
        addChild(_sprite);
        _sprite->setVisible(true);
        _state = 1;
        _health = 3;
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


// ��������ʵ��
Crop* Crop::create(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite)
{
    Crop* crop = new Crop();
    if (crop && crop->init(seedSprite,youngSprite,matureSprite,deadSprite))
    {
        crop->autorelease();
        return crop;
    }
    CC_SAFE_DELETE(crop);
    return nullptr;
}
// ��ʼ������
bool Crop::init(const string& seedSprite, const string& youngSprite, const string& matureSprite, const string& deadSprite)
{
    if (!cocos2d::Node::init())
        return false;

    _seedSprite = cocos2d::Sprite::create(seedSprite);
    _youngSprite = cocos2d::Sprite::create(youngSprite);
    _matureSprite = cocos2d::Sprite::create(matureSprite);
    _deadSprite = cocos2d::Sprite::create(deadSprite);

    if (_seedSprite && _youngSprite && _matureSprite && _deadSprite)
    {
        _deadSprite->setVisible(false);
        _youngSprite->setVisible(false);
        _matureSprite->setVisible(false);
        addChild(_deadSprite);
        addChild(_youngSprite);
        addChild(_matureSprite);
        addChild(_deadSprite);
        _currentSprite = _seedSprite; // Ĭ����ʾ����
        _growthstage = 1;    //����״̬
        ifgrow = 1;    //Ĭ��Ϊ�ɳ�״̬
        _health = 10;
        ifripe = 0;    //��δ����
        ifwithered = 0;    //��δ��ή
        this->schedule(CC_SCHEDULE_SELECTOR(Crop::updatastage), switchtime);
        return true;
    }
    return false;
}
// ��������״̬
void Crop::updatastage(float dt)
{
    if (ifwithered)    //��������Ѿ���ή��ת̬�������
        return;
    static float timeSinceLastSeasonChange = 0.0f;
    timeSinceLastSeasonChange += dt;

    // ����Ƿ��Ѿ���ȥ��switchtime��
    if (timeSinceLastSeasonChange >= switchtime)
    {
        timeSinceLastSeasonChange = 0.0f; // ���ü�ʱ��
        if (ifgrow)
        {
            if(!ifripe)
                _health++;
        }
        else
        {
            _health--;
        }
        if (_health <= 0)
        {
            ifwithered = 1;
            _growthstage = 0;
            switchstage();
        }
        if (_growthstage < _health / 10)
        {
            ifgrow++;
            switchstage();
            if (ifgrow == 3)
                ifripe = 1;
        }
    }
}
//��������״̬
void Crop::switchstage()
{
    switch (_growthstage)
    {
        case 0:
            _currentSprite->setVisible(false);
            _deadSprite->setVisible(true);
            _currentSprite = _deadSprite;
            break;
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
    }
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


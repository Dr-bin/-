#include"maptry.h"
#include<stdlib.h>
#include<ctime>

bool Maptest::init()
{
	if(!Scene::init())return false;
	l1 = MapLayer::create();
	this->addChild(l1);
	return true;
}
bool MapNode::init() {
	if (!Node::init()) return false;
	return true;
}


bool FarmMap::init() {
	srand(time(0));
	if (!MapNode::init()) return false;
	this->ground = Sprite::create("mapresource/farm_ground.png");
	winter = Director::getInstance()->getTextureCache()->addImage("mapresource/farm_ground_winter.png");
	nowater = Director::getInstance()->getTextureCache()->addImage("mapresource/farm_ground_nowater.png");
	ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	int maxX = ground->getContentSize().width;
	int maxY = ground->getContentSize().height;
	for (int i = 0;i < 15;i++) {
		tree[i] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
		int x = rand() % maxX;
		int y = rand() % maxY;
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 1450 && x < 1750 && y>336 && y < 510)&&!(x>155&&x<240&&y>880&&y<1020)&&!(x>1340&&x<1850&&y>800&&y<920)&&!(x>920&&x<1205&&y>620&&y<835))
		{
			this->plantpos[i][0]=x;
			this->plantpos[i][1]=y;
			tree[i]->setAnchorPoint(Vec2(0.5, 0));
			tree[i]->setPosition(Vec2(x, y));
			int rank = 20;
			for (int j = 0;j < i;j++) {
				if (y > tree[j]->getPosition().y)
					rank--;
			}
			this->addChild(tree[i], rank);
		}
		
		
	}
	this->house = House::create();
	this->house->setAnchorPoint(Vec2(0.5, 0));
	this->house->setScale(2.0);
	this->house->setPosition(Vec2(1061, 730));
	this->addChild(this->house, 50);
	return true;

}
void FarmMap::changeSeason(int season) {
	if (season == 0) {
		for (int i = 0;i < 15;i++) {
			tree[i]->switchSeason(0);
		}
		nowSeason = 0;
	}
	if (season == 1) {
		for (int i = 0;i < 15;i++) {
			tree[i]->switchSeason(3);
		}
		nowSeason = 1;
	}
	ground->setTexture(winter);
	if (season == 2) {
		ground->setTexture(nowater);
	}
	
	return;
}



void MapLayer::setMap(int i) {
	currentMap->removeFromParent();
	currentMap = maps[i];
	this->addChild(currentMap);

}
bool MapLayer::init() {
	if (!Node::init())	return false;
	maps[0] = FarmMap::create();
	auto mouse = EventListenerMouse::create();
	mouse->onMouseDown = [](EventMouse* event) {
		CCLOG("x:%f,y:%f", event->getCursorX(), event->getCursorY());
		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse, this);
	maps[1]=ForestMap::create();
	maps[2]=MineMap::create();
	maps[3]=SeaMap::create();
	maps[4]=VillageMap::create();
	//change first map
	this->addChild(maps[0]);
	currentMap = maps[0];
	setMap(4);
	auto ch = CharacterAnimation::create("farmer.plist", 0.2f, 2.0f, Vec2(500, 500));
	this->addChild(ch,50);
	ch->Move(1);
	return true;
	
}

bool ForestMap::init()
{
	
	if(!MapNode::init())
	return false;
	srand(time(0));
	this->ground = Sprite::create("mapresource/froest.png");
	ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	int maxX = ground->getContentSize().width;
	int maxY = ground->getContentSize().height;
	for (int i = 0;i < 30;i++) {
		tree[i] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
		int x = rand() % maxX;
		int y = rand() % maxY;
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 0 && x < 220 && y>890 && y < 1025) && !(x > 380 && x < 490 && y>65 && y < 210)  ) {
			this->plantpos[i][0] = x;
			this->plantpos[i][1] = y;
			tree[i]->setAnchorPoint(Vec2(0.5, 0));
			tree[i]->setPosition(Vec2(x, y));
			int rank = 30;
			for (int j = 0;j < i;j++) {
				if (y > tree[j]->getPosition().y)
					rank--;
			}
			this->addChild(tree[i], rank);
		}
	}

	return true;
}

bool MineMap::init()
{
	if(!MapNode::init())
	return false;
	srand(time(0));
	this->ground = Sprite::create("mapresource/mine.png");
	ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	int maxX = ground->getContentSize().width-50;
	int maxY = ground->getContentSize().height-400;
	for (int i = 0;i < 50;i++) {
		mineral[i]=Mineral::create("plant/mine.png");
		int x = 500+rand() % maxX;
		int y = 200+rand() % maxY;
		mineral[i]->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(mineral[i], 100);
		mineral[i]->setPosition(Vec2(x, y));
	}
	
	return true;
}

bool House::init()
{
	if(!Node::init())
	return false;
	this->house = Sprite::create("plant/house.png");
	this->addChild(this->house);
	return true;
}

bool SeaMap::init()
{
	if(!MapNode::init())
	return false;
	this->ground=Sprite::create("mapresource/sea.png");
	this->ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground,0);
	return true;
}

bool VillageMap::init()
{
	if(!MapNode::init())
	return false;
	this->ground=Sprite::create("mapresource/village_ground.png");
	this->ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground,0);
	this->house[0]=House::create();
	this->house[0]->setAnchorPoint(Vec2(0.5, 0));
	this->house[0]->setScale(2.0);
	this->house[0]->setPosition(Vec2(553, 842));
	this->addChild(this->house[0], 50);
	this->house[1]=House::create();
	this->house[1]->setAnchorPoint(Vec2(0.5, 0));
	this->house[1]->setScale(2.0);
	this->house[1]->setPosition(Vec2(894, 450));
	this->addChild(this->house[1], 50);
	this->house[2]=House::create();
	this->house[2]->setAnchorPoint(Vec2(0.5, 0));
	this->house[2]->setScale(2.0);
	this->house[2]->setPosition(Vec2(1549, 448));
	this->addChild(this->house[2], 50);
	this->house[3]=House::create();
	this->house[3]->setAnchorPoint(Vec2(0.5, 0));
	this->house[3]->setScale(2.0);
	this->house[3]->setPosition(Vec2(1480, 730));
	this->addChild(this->house[3], 50);
	this->tree[0] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[0]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[0]->setPosition(Vec2(214, 806));
	this->addChild(this->tree[0], 20);
	this->tree[1] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[1]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[1]->setPosition(Vec2(274, 215));
	this->addChild(this->tree[1], 20);
	this->tree[2] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[2]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[2]->setPosition(Vec2(1827, 81));
	this->addChild(this->tree[2], 20);
	this->tree[3] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[3]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[3]->setPosition(Vec2(1820, 764));
	this->addChild(this->tree[3], 20);
	this->tree[4] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[4]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[4]->setPosition(Vec2(144, 475));
	this->addChild(this->tree[4], 20);
	this->tree[5] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[5]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[5]->setPosition(Vec2(581, 506));
	this->addChild(this->tree[5], 20);
	this->tree[6] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[6]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[6]->setPosition(Vec2(1170, 633));
	this->addChild(this->tree[6], 20);
	this->tree[7] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[7]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[7]->setPosition(Vec2(985, 726));
	this->addChild(this->tree[7], 20);
	return true;
}

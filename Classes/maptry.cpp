#include"maptry.h"
#include<stdlib.h>
#include<ctime>
#include"menus.h"
bool MapNode::init() {
	if (!Node::init()) return false;
	return true;
}

void MapNode::setEdgebox(int x1, int y1, int x2, int y2) {//设碰撞用
	Vec2 downtops[4]= { Vec2(x1-50,y1),Vec2(x2+50,y1),Vec2(x1-50,y1-50),Vec2(x2+50,y1-50) };
	auto downshape = DrawNode::create();
	downshape->drawPolygon(downtops, 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 0));
	this->addChild(downshape);
	auto downbody = PhysicsBody::createPolygon(downtops, 4);
	downbody->setCollisionBitmask(0x00000001);
	downbody->setDynamic(false);
	downshape->setPhysicsBody(downbody);
	Vec2 uptops[4] = { Vec2(x1-50, y2),Vec2(x2+50, y2),Vec2(x1-50, y2+50),Vec2(x2+50, y2+50) };
	auto upshape = DrawNode::create();
	upshape->drawPolygon(uptops, 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 0));
	this->addChild(upshape);
	auto upbody = PhysicsBody::createPolygon(uptops, 4);
	upbody->setCollisionBitmask(0x00000001);
	upbody->setDynamic(false);
	upshape->setPhysicsBody(upbody);
	Vec2 lefttops[4] = { Vec2(x1, y1-50),Vec2(x1-50, y1-50),Vec2(x1-50, y2+50),Vec2(x1, y2+50) };
	auto leftshape = DrawNode::create();
	leftshape->drawPolygon(lefttops, 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 0));
	this->addChild(leftshape);
	auto leftbody = PhysicsBody::createPolygon(lefttops, 4);
	leftbody->setCollisionBitmask(0x00000001);
	leftbody->setDynamic(false);
	leftshape->setPhysicsBody(leftbody);
	Vec2 righttops[4] = { Vec2(x2, y1-50),Vec2(x2+50, y1-50),Vec2(x2+50, y2+50),Vec2(x2, y2+50) };
	auto rightshape = DrawNode::create();
	rightshape->drawPolygon(righttops, 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 0));
	this->addChild(rightshape);
	auto rightbody = PhysicsBody::createPolygon(righttops, 4);
	rightbody->setCollisionBitmask(0x00000001);
	rightbody->setDynamic(false);
	rightshape->setPhysicsBody(rightbody);
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
		auto treebody = PhysicsBody::createBox(Size(50,80));
		treebody->setDynamic(false);
		tree[i]->setPhysicsBody(treebody);
		tree[i]->setAnchorPoint(Vec2(0.5, 0));
		int x = rand() % maxX;
		int y = rand() % maxY;
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 1450 && x < 1750 && y>336 && y < 510) && !(x > 155 && x < 240 && y>880 && y < 1020) && !(x > 1340 && x < 1850 && y>800 && y < 920) && !(x > 920 && x < 1205 && y>620 && y < 835))
		{
			this->plantpos[i][0] = x;
			this->plantpos[i][1] = y;
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
	auto housebody = PhysicsBody::createBox(Size(120, 80));
	housebody->setPositionOffset(Vec2(0, -20));
	housebody->setMass(100000);
	housebody->setCollisionBitmask(0x00000001);
	this->house->setPhysicsBody(housebody);
	housebody->setDynamic(false);
	Vec2 pooltops[9] = { Vec2(1494,480),Vec2(1494,358),Vec2(1538,358),Vec2(1538,383),Vec2(1707,383),Vec2(1707,454),Vec2(1683,454),Vec2(1683,479),Vec2(1499,479) };
	auto poolshape = DrawNode::create();
	poolshape->drawPolygon(pooltops, 9, Color4F(1, 1, 1, 0),1, Color4F(1, 1, 1, 1));
	this->addChild(poolshape);
	auto poolbody = PhysicsBody::createPolygon(pooltops, 9);
	poolbody->setMass(100000);
	poolbody->setCollisionBitmask(0x00000001);
	poolbody->setDynamic(false);
	poolshape->setPhysicsBody(poolbody);
	this->setEdgebox(0, 60, 1915, 1020);
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
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse, this);
	maps[1] = ForestMap::create();
	maps[2] = MineMap::create();
	maps[3] = SeaMap::create();
	maps[4] = VillageMap::create();
	//change first map
	this->addChild(maps[0]);
	currentMap = maps[0];
	setMap(VILLAGE);
	/*以下有改动*/
	player = CharacterAnimation::create("farmer.plist", 0.2f, 2.0f, Vec2(200, 200));
	this->addChild(player, 50);
	mouse->onMouseDown = CC_CALLBACK_1(CharacterAnimation::onMouseDown, player);
	return true;
}


bool ForestMap::init()
{
	if (!MapNode::init())
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
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 0 && x < 220 && y>890 && y < 1025) && !(x > 380 && x < 490 && y>65 && y < 210)) {
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
			auto treebody = PhysicsBody::createBox(Size(50, 80));
			treebody->setDynamic(false);
			tree[i]->setPhysicsBody(treebody);
		
		}
	}
	Vec2 walltop[4] = { Vec2(0,1023),Vec2(0,907),Vec2(212,907),Vec2(208,1023) };
	auto wallshape = DrawNode::create();
	wallshape->drawPolygon(walltop, 4, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 1));
	this->addChild(wallshape);
	auto wallbody = PhysicsBody::createPolygon(walltop, 4);
	wallbody->setMass(100000);
	wallbody->setCollisionBitmask(0x00000001);
	wallbody->setDynamic(false);
	wallshape->setPhysicsBody(wallbody);
	this->setEdgebox(0, 60, 1915, 1020);
	return true;
}

bool MineMap::init()
{
	if (!MapNode::init())
		return false;
	srand(time(0));
	this->ground = Sprite::create("mapresource/mine.png");
	ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	int maxX = ground->getContentSize().width - 50;
	int maxY = ground->getContentSize().height - 400;
	for (int i = 0;i < 50;i++) {
		mineral[i] = Mineral::create("plant/mine.png");
		auto minebody = PhysicsBody::createBox(Size(10, 10));
		minebody->setDynamic(false);
		mineral[i]->setPhysicsBody(minebody);
		int x = 500 + rand() % maxX;
		int y = 200 + rand() % maxY;
		mineral[i]->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(mineral[i], 100);
		mineral[i]->setPosition(Vec2(x, y));
	}
	auto edgebox = PhysicsBody::createEdgeBox(Size(955,810));
	edgebox->setMass(100000);
	edgebox->setCollisionBitmask(0x00000001);
	edgebox->setDynamic(false);
	this->ground->setPhysicsBody(edgebox);
	this->setEdgebox(483, 123, 1434, 934);

	return true;
}

bool House::init()
{
	if (!Node::init())
		return false;
	this->house = Sprite::create("plant/house.png");
	this->addChild(this->house);
	return true;
}

bool SeaMap::init()
{
	if (!MapNode::init())
		return false;
	this->ground = Sprite::create("mapresource/sea.png");
	this->ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	Vec2 seatops[24] = { Vec2(0,432),Vec2(655,432),Vec2(655,393),Vec2(668,393),Vec2(695,393),Vec2(695,338),Vec2(721,338),Vec2(721,387),Vec2(742,387),Vec2(742,434),Vec2(1047,434),Vec2(1345,432),Vec2(1350,402),Vec2(1385,402),Vec2(1382,369),Vec2(1439,371),
	Vec2(1437,343),Vec2(1616,334),Vec2(1621,304),Vec2(1795,303),Vec2(1801,274),Vec2(1918,276),Vec2(1914,1012),Vec2(0,1015) };
	auto seashape = DrawNode::create();
	seashape->drawPolygon(seatops, 24, Color4F(1, 1, 1, 0), 1, Color4F(1, 1, 1, 1));
	auto seabody = PhysicsBody::createEdgePolygon(seatops, 24);
	seabody->setMass(100000);
	seabody->setCollisionBitmask(0x00000001);
	seabody->setDynamic(false);
	seashape->setPhysicsBody(seabody);
	this->addChild(seashape);
	this->setEdgebox(0, 60, 1915, 1020);
	return true;
}

bool VillageMap::init()
{
	if (!MapNode::init())
		return false;
	this->ground = Sprite::create("mapresource/village_ground.png");
	this->ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	this->house[0] = House::create();
	this->house[0]->setAnchorPoint(Vec2(0.5, 0));
	this->house[0]->setScale(2.0);
	this->house[0]->setPosition(Vec2(553, 842));
	this->addChild(this->house[0], 50);
	auto housebody0 = PhysicsBody::createBox(Size(120, 80));
	housebody0->setPositionOffset(Vec2(0, -20));
	housebody0->setMass(100000);
	housebody0->setCollisionBitmask(0x00000001);
	this->house[0]->setPhysicsBody(housebody0);
	housebody0->setDynamic(false);
	this->house[1] = House::create();
	this->house[1]->setAnchorPoint(Vec2(0.5, 0));
	this->house[1]->setScale(2.0);
	this->house[1]->setPosition(Vec2(894, 450));
	this->addChild(this->house[1], 50);
	auto housebody1 = PhysicsBody::createBox(Size(120, 80));
	housebody1->setPositionOffset(Vec2(0, -20));
	housebody1->setMass(100000);
	housebody1->setCollisionBitmask(0x00000001);
	this->house[1]->setPhysicsBody(housebody1);
	housebody1->setDynamic(false);
	this->house[2] = House::create();
	this->house[2]->setAnchorPoint(Vec2(0.5, 0));
	this->house[2]->setScale(2.0);
	this->house[2]->setPosition(Vec2(1549, 448));
	this->addChild(this->house[2], 50);
	auto housebody2 = PhysicsBody::createBox(Size(120, 80));
	housebody2->setPositionOffset(Vec2(0, -20));
	housebody2->setMass(100000);
	housebody2->setCollisionBitmask(0x00000001);
	this->house[2]->setPhysicsBody(housebody2);
	housebody2->setDynamic(false);
	this->house[3] = House::create();
	this->house[3]->setAnchorPoint(Vec2(0.5, 0));
	this->house[3]->setScale(2.0);
	this->house[3]->setPosition(Vec2(1480, 730));
	this->addChild(this->house[3], 50);
	auto housebody3 = PhysicsBody::createBox(Size(120, 80));
	housebody3->setMass(100000);
	housebody3->setCollisionBitmask(0x00000001);
	this->house[3]->setPhysicsBody(housebody3);
	housebody3->setDynamic(false);
	this->tree[0] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[0]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[0]->setPosition(Vec2(214, 806));
	this->addChild(this->tree[0], 20);
	auto treebody1 = PhysicsBody::createBox(tree[0]->_spriteAutumn->getContentSize());
	treebody1->setMass(100000);
	treebody1->setCollisionBitmask(0x00000001);
	this->tree[0]->setPhysicsBody(treebody1);
	treebody1->setDynamic(false);
	this->tree[1] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[1]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[1]->setPosition(Vec2(274, 215));
	this->addChild(this->tree[1], 20);
	auto treebody2 = PhysicsBody::createBox(tree[1]->_spriteAutumn->getContentSize());
	treebody2->setMass(100000);
	treebody2->setCollisionBitmask(0x00000001);
	this->tree[1]->setPhysicsBody(treebody2);
	treebody2->setDynamic(false);
	this->tree[2] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[2]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[2]->setPosition(Vec2(1827, 81));
	this->addChild(this->tree[2], 20);
	auto treebody3 = PhysicsBody::createBox(tree[2]->_spriteAutumn->getContentSize());
	treebody3->setMass(100000);
	treebody3->setCollisionBitmask(0x00000001);
	this->tree[2]->setPhysicsBody(treebody3);
	treebody3->setDynamic(false);
	this->tree[3] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[3]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[3]->setPosition(Vec2(1820, 764));
	this->addChild(this->tree[3], 20);
	auto treebody4 = PhysicsBody::createBox(tree[3]->_spriteAutumn->getContentSize());
	treebody4->setMass(100000);
	treebody4->setCollisionBitmask(0x00000001);
	this->tree[3]->setPhysicsBody(treebody4);
	treebody4->setDynamic(false);
	this->tree[4] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[4]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[4]->setPosition(Vec2(144, 475));
	this->addChild(this->tree[4], 20);
	auto treebody5 = PhysicsBody::createBox(tree[4]->_spriteAutumn->getContentSize());
	treebody5->setMass(100000);
	treebody5->setCollisionBitmask(0x00000001);
	this->tree[4]->setPhysicsBody(treebody5);
	treebody5->setDynamic(false);
	this->tree[5] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[5]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[5]->setPosition(Vec2(581, 506));
	this->addChild(this->tree[5], 20);
	auto treebody6 = PhysicsBody::createBox(tree[5]->_spriteAutumn->getContentSize());
	treebody6->setMass(100000);
	treebody6->setCollisionBitmask(0x00000001);
	this->tree[5]->setPhysicsBody(treebody6);
	treebody6->setDynamic(false);
	this->tree[6] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[6]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[6]->setPosition(Vec2(1170, 633));
	this->addChild(this->tree[6], 20);
	auto treebody7 = PhysicsBody::createBox(tree[6]->_spriteAutumn->getContentSize());
	treebody7->setMass(100000);
	treebody7->setCollisionBitmask(0x00000001);
	this->tree[6]->setPhysicsBody(treebody7);
	treebody7->setDynamic(false);
	this->tree[7] = Plant::create("plant/tree1_spring.png", "plant/tree1_summer.png", "plant/tree1_fall.png", "plant/tree1_winter.png");
	this->tree[7]->setAnchorPoint(Vec2(0.5, 0));
	this->tree[7]->setPosition(Vec2(985, 726));
	this->addChild(this->tree[7], 20);
	auto treebody8 = PhysicsBody::createBox(tree[7]->_spriteAutumn->getContentSize());
	treebody8->setMass(100000);
	treebody8->setCollisionBitmask(0x00000001);
	this->tree[7]->setPhysicsBody(treebody8);
	treebody8->setDynamic(false);
	auto poolshape=DrawNode::create();
	Vec2 pooltops[4] = { Vec2(153,204),Vec2(237,204),Vec2(237,124),Vec2(153,124) };
	poolshape->drawPolygon(pooltops, 4, Color4F(0.5, 0.5, 0.5, 0),1,Color4F(0.5, 0.5, 0.5, 0));
	poolshape->setVisible(false);
	auto poolbody = PhysicsBody::createPolygon(pooltops, 4);
	poolbody->setMass(100000);
	poolbody->setCollisionBitmask(0x00000001);
	poolbody->setDynamic(false);
	poolshape->setPhysicsBody(poolbody);
	this->addChild(poolshape, 10);
	this->setEdgebox(0, 60, 1915, 1020);
	return true;
}

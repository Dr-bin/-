#include"maptry.h"
#include<stdlib.h>
#include<ctime>


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



bool FarmMap::init() 
{
	srand(time(0));
	if (!MapNode::init()) return false;
	this->ground = Sprite::create("mapresource/farm_ground.png");
	winter = Director::getInstance()->getTextureCache()->addImage("mapresource/farm_ground_winter.png");
	nowater = Director::getInstance()->getTextureCache()->addImage("mapresource/farm_ground_nowater.png");
	spring = Director::getInstance()->getTextureCache()->addImage("mapresource/farm_ground.png");
	ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->addChild(this->ground, 0);
	this->scheduleUpdate();
	int maxX = ground->getContentSize().width;
	int maxY = ground->getContentSize().height;
	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(FarmMap::onMouseDown, this,1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
#if 0
	tree[0] = Plant::create("Plantsource/tree1_spring.png", "Plantsource/tree1_summer.png", "Plantsource/tree1_fall.png", "Plantsource/tree1_winter.png");
	tree[0]->setScale(1.4f);
	tree[0]->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(this->tree[0], 20);
	auto treebody = PhysicsBody::createBox(tree[0]->_spriteAutumn->getContentSize());
	treebody->setMass(100000);
	treebody->setCollisionBitmask(0x00000001);
	this->tree[0]->setPhysicsBody(treebody);
	treebody->setDynamic(false);
	tree[0]->setPosition(Vec2(500, 500));
	CCLOG("%d", tree[0]->getParent()->isRunning());
	if (this->isRunning())
		CCLOG("1");
	else
		CCLOG("0");
#endif
#if 0
	for (int i = 0;i < 15;i++) {
		if(i%2==0)
		    tree[i] = Plant::create("Plantsource/tree1_spring.png", "Plantsource/tree1_summer.png", "Plantsource/tree1_fall.png", "Plantsource/tree1_winter.png");
		else
			tree[i] = Plant::create("Plantsource/tree2_spring.png", "Plantsource/tree2_summer.png", "Plantsource/tree2_fall.png", "Plantsource/tree2_winter.png");
		tree[i]->scheduleUpdate();
		auto treebody = PhysicsBody::createBox(Size(50,80));
		treebody->setDynamic(false);
		tree[i]->setPhysicsBody(treebody);
		tree[i]->setAnchorPoint(Vec2(0.5, 0));
		int x = rand() % maxX;
		int y = rand() % maxY;
		int rank = 20;
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 1450 && x < 1750 && y>336 && y < 510) && !(x > 155 && x < 240 && y>880 && y < 1020) && !(x > 1340 && x < 1850 && y>800 && y < 920) && !(x > 920 && x < 1205 && y>620 && y < 835))
		{
			this->plantpos[i][0] = x;
			this->plantpos[i][1] = y;
			tree[i]->setAnchorPoint(Vec2(0.5, 0));
			tree[i]->setPosition(Vec2(x, y));
			for (int j = 0;j < i;j++) {
				if (y > tree[j]->getPosition().y)
					rank--;
			}
		}
		this->addChild(tree[i], rank);
	}
#endif
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			landstatus[i][j] = 1;
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
	drawcropfence();
	drawanimalfence();
	drawtree();
	CCLOG("fail");
	return true;

}

void FarmMap::update(float dt)
{
	timeSinceLastSeasonChange += dt;
	//timeSinceLastSeasonChange >= switchtime &&
	// 检查是否已经过去了switchtime秒
	if (timeSinceLastSeasonChange >= switchtime)
	{
		timeSinceLastSeasonChange = 0.0f; // 重置计时器
		nowSeason = (nowSeason + 1) % 4; // 循环季节
		switchseason(nowSeason);
	}
}
void FarmMap::switchseason(int season)
{
	if (season == 0)
	{
		ground->setTexture(spring);
	}
	if (season == 1)
	{
		ground->setTexture(nowater);
		for (int i = 0; i < cropnum; i++)
		{
			allcrop[i]->setifgrow(false);
		}
	}
	if (season == 2)
	{
		ground->setTexture(spring);
		for (int i = 0; i < cropnum; i++)
		{
			allcrop[i]->setifgrow(true);
		}
	}
	if (season == 3)
	{
		ground->setTexture(winter);
	}
	for (int i = 0; i < croptreenum; i++)
	{
		treeincropfence[i]->switchSeason(season);
	}
	for (int i = 0; i < outcroptreenum; i++)
	{
		treeoutcropfence[i]->switchSeason(season);
	}
}
void FarmMap::drawtree()
{
	//先画crop范围内的树
#if 1
	int startx = 200, starty = 200;
	auto onetree = Plant::create("Plantsource/tree4_spring.png", "Plantsource/tree4_summer.png", "Plantsource/tree4_fall.png", "Plantsource/tree4_winter.png");
	auto treebody = PhysicsBody::createBox(onetree->_spriteAutumn->getContentSize());
	treebody->setMass(100000);
	treebody->setCollisionBitmask(0x00000001);
	onetree->setPhysicsBody(treebody);
	treebody->setDynamic(false);
	//+onetree->getContentSize().width / 2
	//+onetree->getContentSize().height/2
	onetree->setAnchorPoint(Vec2(0, 0));
	onetree->setScale(1.2f);
	auto Size = onetree->getcontentSize();
	onetree->setPosition(Vec2(startx+Size.width/2, starty+Size.height/2));
	log("%f %f", onetree->getPosition().x, onetree->getPosition().y);
	addChild(onetree, 20);
	treeincropfence[croptreenum++]=onetree;
#endif
	//画crop范围外的树
#if 1
	for (int i = 0; i < 10; i++)
	{
		if (i % 4 == 0)
		{
			treeoutcropfence[i] = Plant::create("Plantsource/tree1_spring.png", "Plantsource/tree1_summer.png", "Plantsource/tree1_fall.png", "Plantsource/tree1_winter.png");
			treeoutcropfence[i]->setScale(1.4f);
		}
		else if (i % 4 == 1)
		{
			treeoutcropfence[i] = Plant::create("Plantsource/tree2_spring.png", "Plantsource/tree2_summer.png", "Plantsource/tree2_fall.png", "Plantsource/tree2_winter.png");
			treeoutcropfence[i]->setScale(1.8f);
		}
		else if (i % 4 == 2)
		{
			treeoutcropfence[i] = Plant::create("Plantsource/tree3_spring.png", "Plantsource/tree3_spring.png", "Plantsource/tree3_fall.png", "Plantsource/tree3_winter.png");
			treeoutcropfence[i]->setScale(2.0f);
		}
		else if (i % 4 == 3)
		{
			treeoutcropfence[i] = Plant::create("Plantsource/tree4_spring.png", "Plantsource/tree4_summer.png", "Plantsource/tree4_fall.png", "Plantsource/tree4_winter.png");
			treeoutcropfence[i]->setScale(1.6f);
		}
		treeoutcropfence[i]->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(this->treeoutcropfence[i], 20);
		auto treebody = PhysicsBody::createBox(treeoutcropfence[i]->_spriteAutumn->getContentSize());
		treebody->setMass(100000);
		treebody->setCollisionBitmask(0x00000001);
		this->treeoutcropfence[i]->setPhysicsBody(treebody);
		treebody->setDynamic(false);
	}
	treeoutcropfence[0]->setPosition(Vec2(50,220));
	treeoutcropfence[1]->setPosition(Vec2(90, 390));
	treeoutcropfence[2]->setPosition(Vec2(1860, 690));
	treeoutcropfence[3]->setPosition(Vec2(910, 150));
	treeoutcropfence[4]->setPosition(Vec2(80, 690));
	treeoutcropfence[5]->setPosition(Vec2(1610, 250));
	treeoutcropfence[6]->setPosition(Vec2(1280, 720));
	treeoutcropfence[7]->setPosition(Vec2(1520, 150));
	treeoutcropfence[8]->setPosition(Vec2(1820, 170));
	treeoutcropfence[9]->setPosition(Vec2(1740, 480));
#endif
}
void FarmMap::drawcropfence()
{
#if 1
	int startx = 200;
	int starty = 200;
	int endx = 800;
	int endy = 820;
	if (1)    //画左下角
	{
		auto leftdown = Sprite::create("fence/fence_4.png");
		leftdown->setAnchorPoint(Vec2(0.5, 0));
		leftdown->setScale(2.0f);
		this->addChild(leftdown, 20);
		leftdown->setPosition(Vec2(startx - 20, starty - 54));
	}
	for (int i = 1; i <=15; i++)
	{
		auto onefence= Sprite::create("fence/fence_3.png");
		onefence->setScale(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 20+i*40, starty - 54));
	}
	if (1)    //画右下角
	{
		auto rightdown = Sprite::create("fence/fence_5.png");
		rightdown->setAnchorPoint(Vec2(0.5, 0));
		rightdown->setScale(2.0f);
		this->addChild(rightdown, 20);
		rightdown->setPosition(Vec2(startx - 20 + 16 * 40, starty - 54));
	}
	for (int i = 1; i <= 12; i++)
	{
		auto onefence = Sprite::create("fence/fence_6.png");
		onefence->setScaleX(2.0f);
		onefence->setScaleY(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 21, starty - 63+i*56));
	}
	for (int i = 1; i <= 12; i++)
	{
		auto onefence = Sprite::create("fence/fence_6.png");
		onefence->setScaleX(2.0f);
		onefence->setScaleY(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 13+16*40, starty - 63 + i * 56));
	}
	if (1)    //画左上角
	{
		auto leftup = Sprite::create("fence/fence_4.png");
		leftup->setAnchorPoint(Vec2(0.5, 0));
		leftup->setScale(2.0f);
		this->addChild(leftup, 20);
		leftup->setPosition(Vec2(startx - 20, starty - 66+10*62+64));
	}
	for (int i = 1; i <= 15; i++)
	{
		if (i <= 5 || i >= 11)
		{
			auto onefence = Sprite::create("fence/fence_3.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 10 * 62 + 64));
		}
		if (i == 6)
		{
			auto onefence = Sprite::create("fence/fence_1.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 10 * 62 + 64));
		}
		if (i == 10)
		{
			auto onefence = Sprite::create("fence/fence_2.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 10 * 62 + 64));
		}
	}
	if (1)    //画右上角
	{
		auto rightdown = Sprite::create("fence/fence_5.png");
		rightdown->setAnchorPoint(Vec2(0.5, 0));
		rightdown->setScale(2.0f);
		this->addChild(rightdown, 20);
		rightdown->setPosition(Vec2(startx - 20 + 16 * 40, starty - 66 + 10 * 62 + 64));
	}
#endif
	int x1 = 200, y1 = 200, x2 = 800, y2 = 820;
	int horizontalThickness = 64; // 横向厚度
	int verticalThickness = 40;   // 纵向宽度

	// 创建碰撞墙
	createCollisionWall(x1, y1-horizontalThickness, x2, y1); // 下边
	createCollisionWall(x1, y2, x1+230, y2+horizontalThickness); // 上左边
	createCollisionWall(x2-230, y2, x2, y2 + horizontalThickness); // 上右边
	createCollisionWall(x1-verticalThickness, y1, x1, y2); // 左边
	createCollisionWall(x2, y1, x2+verticalThickness, y2); // 右边
}
void FarmMap::drawanimalfence()
{
#if 1
	int startx = 1000;
	int starty = 150;
	int endx = 1400;
	int endy = 510;
	if (1)    //画左下角
	{
		auto leftdown = Sprite::create("fence/fence_4.png");
		leftdown->setAnchorPoint(Vec2(0.5, 0));
		leftdown->setScale(2.0f);
		this->addChild(leftdown, 20);
		leftdown->setPosition(Vec2(startx - 20, starty - 54));
	}
	for (int i = 1; i <= 10; i++)
	{
		auto onefence = Sprite::create("fence/fence_3.png");
		onefence->setScale(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 54));
	}
	if (1)    //画右下角
	{
		auto rightdown = Sprite::create("fence/fence_5.png");
		rightdown->setAnchorPoint(Vec2(0.5, 0));
		rightdown->setScale(2.0f);
		this->addChild(rightdown, 20);
		rightdown->setPosition(Vec2(startx - 20 + 11 * 40, starty - 54));
	}
	for (int i = 1; i <= 7; i++)
	{
		auto onefence = Sprite::create("fence/fence_6.png");
		onefence->setScaleX(2.0f);
		onefence->setScaleY(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 21, starty - 63 + i * 54));
	}
	for (int i = 1; i <= 7; i++)
	{
		auto onefence = Sprite::create("fence/fence_6.png");
		onefence->setScaleX(2.0f);
		onefence->setScaleY(2.0f);
		onefence->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(onefence, 20);
		onefence->setPosition(Vec2(startx - 13 + 11 * 40, starty - 63 + i * 54));
	}
	if (1)    //画左上角
	{
		auto leftup = Sprite::create("fence/fence_4.png");
		leftup->setAnchorPoint(Vec2(0.5, 0));
		leftup->setScale(2.0f);
		this->addChild(leftup, 20);
		leftup->setPosition(Vec2(startx - 20, starty - 66 + 6 * 62 + 64));
	}
	for (int i = 1; i <= 10; i++)
	{
		if (i <= 3 || i >=8)
		{
			auto onefence = Sprite::create("fence/fence_3.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 6 * 62 + 64));
		}
		if (i == 4)
		{
			auto onefence = Sprite::create("fence/fence_1.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 6 * 62 + 64));
		}
		if (i == 7)
		{
			auto onefence = Sprite::create("fence/fence_2.png");
			onefence->setScale(2.0f);
			onefence->setAnchorPoint(Vec2(0.5, 0));
			this->addChild(onefence, 20);
			onefence->setPosition(Vec2(startx - 20 + i * 40, starty - 66 + 6* 62 + 64));
		}
	}
	if (1)    //画右上角
	{
		auto rightdown = Sprite::create("fence/fence_5.png");
		rightdown->setAnchorPoint(Vec2(0.5, 0));
		rightdown->setScale(2.0f);
		this->addChild(rightdown, 20);
		rightdown->setPosition(Vec2(startx - 20 + 11 * 40, starty - 66 + 6 * 62 + 64));
	}
#endif
	int x1 = 1000, y1 = 150, x2 = 1400, y2 = 510;
	int horizontalThickness = 64; // 横向厚度
	int verticalThickness = 40;   // 纵向宽度

	// 创建碰撞墙
	createCollisionWall(x1, y1 - horizontalThickness, x2, y1); // 下边
	createCollisionWall(x1, y2, x1 + 150, y2 + horizontalThickness); // 上左边
	createCollisionWall(x2 - 150, y2, x2, y2 + horizontalThickness); // 上右边
	createCollisionWall(x1 - verticalThickness, y1, x1, y2); // 左边
	createCollisionWall(x2, y1, x2 + verticalThickness, y2); // 右边
}
void FarmMap::createCollisionWall(int x1, int y1, int x2, int y2) {
	// 创建一个DrawNode来绘制碰撞墙
	auto drawNode = DrawNode::create();
	this->addChild(drawNode);

	// 计算碰撞墙的顶点
	Vec2 vertices[4];
	vertices[0] = Vec2(x1, y1);
	vertices[1] = Vec2(x2, y1);
	vertices[2] = Vec2(x2, y2);
	vertices[3] = Vec2(x1, y2);
	bool visible = false;
	// 如果需要显示碰撞墙，则绘制它
	if (visible) {
		drawNode->drawPolygon(vertices, 4, Color4F::RED, 1, Color4F::RED);
	}
	else {
		// 不绘制碰撞墙，但仍然创建物理身体
		drawNode->setVisible(false);
	}

	// 创建物理身体
	auto body = PhysicsBody::createPolygon(vertices, 4);
	body->setDynamic(false); // 设置为静态
	body->setCollisionBitmask(0x00000001); // 设置碰撞位掩码

	// 将物理身体添加到DrawNode
	drawNode->setPhysicsBody(body);

	// 如果需要显示碰撞墙，则添加到场景
	if (visible) {
		this->addChild(drawNode);
	}
}
void FarmMap::onMouseDown(EventMouse* event,int nowtool) 
{
	bool ifproceed = false;    //判断这一步是否已经执行
	if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) 
	{
		int number = -1;
		Plant* treenode = checkcropPlantNode(event,&number);
		//找到为crop范围内的树
		if (treenode != nullptr)
		{
			if (!ifproceed)
			{
				CCLOG("Plant");
				float x = treenode->getPosition().x, y = treenode->getPosition().y;
				Size size = treenode->getcontentSize();
				//log("%f %f", mousePos.x, mousePos.y);
				//log("%f %f", mineral[i]->getPosition().x, mineral[i]->getPosition().y);
				float x1 = x - size.width / 2 - 25, x2 = x + size.width / 2 + 25;
				float y1 = y - size.height / 2 - 25, y2 = y + size.height / 2 + 25;
				float chx = ch->getPosition().x, chy = ch->getPosition().y;
				if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
				{
					if (1)    //添加手中武器为斧头的逻辑   
					{
						if (treenode->_isTregger == 0)
						{
							treenode->damage(1);
							if (treenode->_isTregger == 1)
							{
								Plant* temp[40] = { nullptr };
								int j = 0;
								for (int i = 0; i < 40; i++)
								{
									if (i == number)
										continue;
									temp[j++] = treeincropfence[i];
								}
								for (int i = 0; i < 40; i++)
								{
									treeincropfence[i] = temp[i];
								}
								croptreenum--;
							}
						}
					}
				}
				ifproceed = true;
			}
		}
		Crop* cropnode = checkcropNode(event, &number);
		//找到为crop
		if (cropnode != nullptr)
		{
			if (!ifproceed)
			{
				CCLOG("Crop");
				float x = cropnode->getPosition().x, y = cropnode->getPosition().y;
				Size size = cropnode->getcontentSize();
				//log("%f %f", mousePos.x, mousePos.y);
				//log("%f %f", mineral[i]->getPosition().x, mineral[i]->getPosition().y);
				float x1 = x - size.width / 2 - 25, x2 = x + size.width / 2 + 25;
				float y1 = y - size.height / 2 - 25, y2 = y + size.height / 2 + 25;
				float chx = ch->getPosition().x, chy = ch->getPosition().y;
				if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
				{
					int stage = cropnode->getstage();
					if (stage > 0 && stage < 4)   //作物未枯萎也为未成熟
					{
						if (1)    //工具为水桶
						{
							cropnode->plusspeed();
							ifproceed = true;
						}
						else if (2)    //工具为锄头
						{
							cropnode->damage();
							Crop* temp[225] = { nullptr };
							int j = 0;
							for (int i = 0; i < 225; i++)
							{
								if (i == number)
									continue;
								temp[j++] = allcrop[i];
							}
							for (int i = 0; i < 225; i++)
							{
								allcrop[i] = temp[i];
							}
							cropnum--;
						}
						ifproceed = true;
					}
					else if (stage == 4)    //作物已经成熟
					{
						if (1)    //工具为锄头
						{
							cropnode->Pick();
							Crop* temp[225] = { nullptr };
							int j = 0;
							for (int i = 0; i < 225; i++)
							{
								if (i == number)
									continue;
								temp[j++] = allcrop[i];
							}
							for (int i = 0; i < 225; i++)
							{
								allcrop[i] = temp[i];
							}
							cropnum--;
						}
						ifproceed = true;
					}
					else if (stage == 0)
					{
						if (1)    //工具为锄头
						{
							cropnode->damage();
							Crop* temp[225] = { nullptr };
							int j = 0;
							for (int i = 0; i < 225; i++)
							{
								if (i == number)
									continue;
								temp[j++] = allcrop[i];
							}
							for (int i = 0; i < 225; i++)
							{
								allcrop[i] = temp[i];
							}
							cropnum--;
						}
						ifproceed = true;
					}
				}
				ifproceed == true;
			}
		}
		float mousex = event->getCursorX(), mousey = event->getCursorY();
		// 耕地逻辑
		if (1)    //添加工具为锄头的逻辑
		{
			if (!ifproceed)
			{
				int cropx = (mousex - 200) / 40, cropy = (mousey - 200) / 40;
				log("%d %d %d", cropx, cropy, landstatus[cropy][cropx]);
				if (landstatus[cropy][cropx] == 1)
				{
					float chx = ch->getPosition().x, chy = ch->getPosition().y;
					float x1 = 200.0 + cropx * 40 - 25, y1 = 200.0 + cropy * 40 - 25;
					float x2 = 200.0 + cropx * 40 + 40 + 25, y2 = 200.0 + cropy * 40 + 40 + 25;
					log("%f %f", x1, y1);
					log("%f %f", x2, y2);
					log("%f %f", chx, chy);
					if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
					{
						auto land = Sprite::create("plowland.png");
						log("success");
						land->setScale(1.0 / 3);
						land->setAnchorPoint(Vec2(0, 0));
						land->setVisible(true);
						land->setPosition(Vec2(200.0 + cropx * 40, 200.0 + cropy * 40));
						addChild(land, 10);
						landstatus[cropy][cropx] = 2;
					}
					ifproceed = true;
				}
				
			}
		}
		// 种地逻辑
		if (1)    //添加工具为种子的逻辑
		{
			if (!ifproceed)
			{
				int cropx = (mousex - 200) / 40, cropy = (mousey - 200) / 40;
				log("%d %d %d", cropx, cropy, landstatus[cropy][cropx]);
				if (landstatus[cropy][cropx] == 2)
				{
					float chx = ch->getPosition().x, chy = ch->getPosition().y;
					float x1 = 200.0 + cropx * 40 - 25, y1 = 200.0 + cropy * 40 - 25;
					float x2 = 200.0 + cropx * 40 + 40 + 25, y2 = 200.0 + cropy * 40 + 40 + 25;
					log("seed");
					log("%f %f", x1, y1);
					log("%f %f", x2, y2);
					log("%f %f", chx, chy);
					if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
					{
						auto crop = Crop::create("crop/crop2_seed.png","crop/crop2_young.png","crop/crop2_mature.png","crop/crop2_final.png");
						log("success");
						crop->setScale(2.0);
						crop->setAnchorPoint(Vec2(0, 0));
						crop->setVisible(true);
						crop->setPosition(Vec2(200.0 + cropx * 40+20, 200.0 + cropy * 40+20));
						addChild(crop, 15);
						landstatus[cropy][cropx] = 2;
						allcrop[cropnum++] = crop;	
					}
					ifproceed = true;
				}
			}
		}
	}
}

Plant* FarmMap::checkcropPlantNode(EventMouse* event,int* number) {
	Vec2 mousePos = Vec2(event->getCursorX(),event->getCursorY());
	for (int i = 0; i<croptreenum; i++) 
	{
		if (treeincropfence[i]->_isTregger == 1)
			continue;
		float x = treeincropfence[i]->getPosition().x, y = treeincropfence[i]->getPosition().y;
		Size size = treeincropfence[i]->getcontentSize();
		//log("%f %f", mousePos.x, mousePos.y);
		//log("%f %f", x, y);
		float x1 = x - size.width / 2, x2 =x + size.width / 2;
		float y1 = y - size.height / 2, y2 = y + size.height / 2;
		//log("%f %f", x1, y1);
		//log("%f %f", x2, y2);
		// 将鼠标位置转换为子节点的空间坐标
		//Vec2 localPos = treeincropfence[i]->convertToNodeSpace(mousePos);
		// 检查鼠标位置是否在子节点的边界框内
		if (mousePos.x>x1&&mousePos.x<x2&&mousePos.y>y1&&mousePos.y<y2) 
		{
			//CCLOG("Yes");
			// 如果是，返回这个子节点
			*number = i;
			return treeincropfence[i];
		}
	}
	// 如果没有找到任何包含鼠标位置的子节点，返回nullptr
	return nullptr;
}
Crop* FarmMap::checkcropNode(EventMouse* event, int* number)
{
	Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
	for (int i = 0; i < cropnum; i++)
	{
		float x = allcrop[i]->getPosition().x, y = allcrop[i]->getPosition().y;
		Size size = allcrop[i]->getcontentSize();
		//log("%f %f", mousePos.x, mousePos.y);
		//log("%f %f", x, y);
		float x1 = x - size.width / 2, x2 = x + size.width / 2;
		float y1 = y - size.height / 2, y2 = y + size.height / 2;
		//log("%f %f", x1, y1);
		//log("%f %f", x2, y2);
		// 将鼠标位置转换为子节点的空间坐标
		//Vec2 localPos = allcrop[i]->convertToNodeSpace(mousePos);
		// 检查鼠标位置是否在子节点的边界框内
		if (mousePos.x > x1 && mousePos.x<x2 && mousePos.y>y1 && mousePos.y < y2)
		{
			//CCLOG("Yes");
			// 如果是，返回这个子节点
			*number = i;
			return allcrop[i];
		}
	}
	// 如果没有找到任何包含鼠标位置的子节点，返回nullptr
	return nullptr;
}

void MapLayer::setMap(int i) {
	currentMap->removeFromParent();
	currentMap = maps[i];
	this->addChild(currentMap);
	currentMap->scheduleUpdate();
}
bool MapLayer::init() {
	if (!Node::init())	return false;
	maps[0] = FarmMap::create();
	/*
	auto mouse = EventListenerMouse::create();
	mouse->onMouseDown = [](EventMouse* event) {
		CCLOG("x:%f,y:%f", event->getCursorX(), event->getCursorY());
		};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse, this);
	*/
	maps[1] = ForestMap::create();
	maps[2] = MineMap::create();
	maps[3] = SeaMap::create();
	maps[4] = VillageMap::create();
	//change first 
	this->addChild(maps[0]);
	currentMap = maps[0];
	setMap(FARM);
	ch = CharacterAnimation::create("farmer.plist", 0.2f, 2.0f, Vec2(0, 0));
	ch->setPosition(Vec2(600, 600));
	this->addChild(ch, 50);
	maps[0]->ch = ch;
	ch->Move(1);
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
	for (int i = 0;i < 30;i++) 
	{
		Plant* onetree;
		if (i % 4 == 0)
		{
			onetree = Plant::create("Plantsource/tree1_spring.png", "Plantsource/tree1_summer.png", "Plantsource/tree1_fall.png", "Plantsource/tree1_winter.png");
			onetree->setScale(1.4f);
		}
		else if (i % 4 == 1)
		{
			onetree = Plant::create("Plantsource/tree2_spring.png", "Plantsource/tree2_summer.png", "Plantsource/tree2_fall.png", "Plantsource/tree2_winter.png");
			onetree->setScale(1.8f);
		}
		else if (i % 4 == 2)
		{
			onetree = Plant::create("Plantsource/tree3_spring.png", "Plantsource/tree3_spring.png", "Plantsource/tree3_fall.png", "Plantsource/tree3_winter.png");
			onetree->setScale(2.0f);
		}
		else if (i % 4 == 3)
		{
			onetree = Plant::create("Plantsource/tree4_spring.png", "Plantsource/tree4_summer.png", "Plantsource/tree4_fall.png", "Plantsource/tree4_winter.png");
			onetree->setScale(1.6f);
		}
		int x = rand() % maxX;
		int y = rand() % maxY;
		if (x > 10 && x < maxX - 10 && y>100 && y < maxY - 10 && !(x > 0 && x < 220 && y>890 && y < 1025) && !(x > 380 && x < 490 && y>65 && y < 210)) {
			tree[i] = onetree;
			this->plantpos[i][0] = x;
			this->plantpos[i][1] = y;
			tree[i]->setAnchorPoint(Vec2(0.5, 0));
			tree[i]->setPosition(Vec2(x, y));
			int rank = 30;
			for (int j = 0; j < i; j++) {
				if (y > tree[j]->getPosition().y)
					rank--;
			}
			this->addChild(tree[i], rank);
			auto treebody = PhysicsBody::createBox(Size(50, 80));
			treebody->setDynamic(false);
			tree[i]->setPhysicsBody(treebody);
			plantnum++;
		}
		else
			i--;
	}
	log("%d", plantnum);
	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ForestMap::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
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
void ForestMap::onMouseDown(EventMouse* event)
{
	if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		int number = -1;
		Plant* node = checkPlantNode(event, &number);
		if (node != nullptr)
		{
			CCLOG("Plant");
			float x = node->getPosition().x, y = node->getPosition().y;
			Size size = node->getcontentSize();
			//log("%f %f", mousePos.x, mousePos.y);
			//log("%f %f", mineral[i]->getPosition().x, mineral[i]->getPosition().y);
			float x1 = x - size.width / 2 - 25, x2 = x + size.width / 2 + 25;
			float y1 = y - size.height / 2 - 25, y2 = y + size.height / 2 + 25;
			float chx = ch->getPosition().x, chy = ch->getPosition().y;
			if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
			{
				if (1)    //添加手中武器为斧头的逻辑
					if (node->_isTregger == 0)
					{
						node->damage(1);
						if (node->_isTregger == 1)
						{
							Plant* temp[30] = { nullptr };
							int j = 0;
							for (int i = 0; i < 30; i++)
							{
								if (i == number)
									continue;
								temp[j++] = tree[i];
							}
							for (int i = 0; i < 30; i++)
							{
								tree[i] = temp[i];
							}
							plantnum--;
						}
					}
			}
		}
	}
}
Plant* ForestMap::checkPlantNode(EventMouse* event, int* number) {
	Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
	for (int i = 0; i < plantnum; i++)
	{
		if (tree[i]->_isTregger == 1)
			continue;
		float x = tree[i]->getPosition().x, y = tree[i]->getPosition().y;
		Size size = tree[i]->getcontentSize();
		//log("%f %f", mousePos.x, mousePos.y);
		//log("%f %f", x, y);
		float x1 = x - size.width / 2, x2 = x + size.width / 2;
		float y1 = y - size.height / 2, y2 = y + size.height / 2;
		//log("%f %f", x1, y1);
		//log("%f %f", x2, y2);
		// 将鼠标位置转换为子节点的空间坐标
		//Vec2 localPos = treeincropfence[i]->convertToNodeSpace(mousePos);
		// 检查鼠标位置是否在子节点的边界框内
		if (mousePos.x > x1 && mousePos.x<x2 && mousePos.y>y1 && mousePos.y < y2)
		{
			//CCLOG("Yes");
			// 如果是，返回这个子节点
			*number = i;
			return tree[i];
		}
	}
	// 如果没有找到任何包含鼠标位置的子节点，返回nullptr
	return nullptr;
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
	minenum = 50;
	mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MineMap::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	auto edgebox = PhysicsBody::createEdgeBox(Size(955,810));
	edgebox->setMass(100000);
	edgebox->setCollisionBitmask(0x00000001);
	edgebox->setDynamic(false);
	this->ground->setPhysicsBody(edgebox);
	this->setEdgebox(483, 123, 1434, 934);
	return true;
}
void MineMap::onMouseDown(EventMouse* event)
{
	if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		int number = -1;
		Mineral* node = checkMineNode(event,&number);
		log("%d", number);
		if (node != nullptr)
		{
			CCLOG("Mineral");
			float x = node->getPosition().x, y = node->getPosition().y;
			Size size = node->getcontentSize();
			//log("%f %f", mousePos.x, mousePos.y);
			//log("%f %f", mineral[i]->getPosition().x, mineral[i]->getPosition().y);
			float x1 = x - size.width / 2-25, x2 = x + size.width / 2+25;
			float y1 = y - size.height / 2-25, y2 = y + size.height / 2+25;
			float chx = ch->getPosition().x, chy = ch->getPosition().y;
			if (chx > x1 && chx<x2 && chy>y1 && chy < y2)
			{
				if(1)    //添加手中武器为镐子的逻辑
				    if (node->_state == 1)
				{
					node->damage(1);
					if (node->_state == 0)
					{
						Mineral* temp[50] = { nullptr };
						int j = 0;
						for (int i = 0; i < 50; i++)
						{
							if (i == number)
								continue;
							temp[j++] = mineral[i];
						}
						for (int i = 0; i < 50; i++)
						{
							mineral[i] = temp[i];
						}
						minenum--;
					}
				}
			}
		}
	}
}
Mineral* MineMap::checkMineNode(EventMouse* event,int* number) {
	Vec2 mousePos = Vec2(event->getCursorX(), event->getCursorY());
	for (int i = 0; i < minenum; i++)
	{
		if (mineral[i]->_state == 0)
			continue;
		float x = mineral[i]->getPosition().x, y = mineral[i]->getPosition().y;
		Size size = mineral[i]->getcontentSize();
		//log("%f %f", mousePos.x, mousePos.y);
		//log("%f %f", mineral[i]->getPosition().x, mineral[i]->getPosition().y);
		float x1 = x - size.width / 2, x2 = x + size.width / 2;
		float y1 = y - size.height / 2, y2 = y + size.height / 2;
		//log("%f %f", x1, y1);
		//log("%f %f", x2, y2);
		// 检查鼠标位置是否在子节点的边界框内
		if (mousePos.x > x1 && mousePos.x<x2 && mousePos.y>y1 && mousePos.y < y2)
		{
			CCLOG("Yes");
			// 如果是，返回这个子节点
			log("%d", i);
			*number = i;
			log("%d", *number);
			return mineral[i];
		}
	}
	// 如果没有找到任何包含鼠标位置的子节点，返回nullptr
	return nullptr;
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
	for (int i = 0; i < 3; i++)
	{
		coconuttree[i] = Sprite::create("Plantsource/coconuttree_1.png");
		coconuttree[i]->setScale(1.5f);
		coconuttree[i]->setPosition(Vec2(150+(i==1?i*420:i*650), 150+i*40));
		addChild(coconuttree[i], 1);
		auto treebody1 = PhysicsBody::createBox(coconuttree[i]->getContentSize());
		treebody1->setMass(100000);
		treebody1->setCollisionBitmask(0x00000001);
		this->coconuttree[i]->setPhysicsBody(treebody1);
		treebody1->setDynamic(false);
	}
	for (int i = 3; i < 6; i++)
	{
		coconuttree[i] = Sprite::create("Plantsource/coconuttree_2.png");
		coconuttree[i]->setScale(1.5f);
		coconuttree[i]->setPosition(Vec2(300 + (i-3) *800, 250 + (3-i) *40 ));
		addChild(coconuttree[i], 1);
		auto treebody1 = PhysicsBody::createBox(coconuttree[i]->getContentSize());
		treebody1->setMass(100000);
		treebody1->setCollisionBitmask(0x00000001);
		this->coconuttree[i]->setPhysicsBody(treebody1);
		treebody1->setDynamic(false);
	}
	for (int i = 6; i < 9; i++)
	{
		coconuttree[i] = Sprite::create("Plantsource/coconuttree_3.png");
		coconuttree[i]->setScale(1.5f);
		addChild(coconuttree[i], 1);
		auto treebody1 = PhysicsBody::createBox(coconuttree[i]->getContentSize());
		treebody1->setMass(100000);
		treebody1->setCollisionBitmask(0x00000001);
		this->coconuttree[i]->setPhysicsBody(treebody1);
		treebody1->setDynamic(false);
	}
	for (int i = 9; i < 12; i++)
	{
		coconuttree[i] = Sprite::create("Plantsource/coconuttree_4.png");
		coconuttree[i]->setScale(1.5f);
		addChild(coconuttree[i], 1);
		auto treebody1 = PhysicsBody::createBox(coconuttree[i]->getContentSize());
		treebody1->setMass(100000);
		treebody1->setCollisionBitmask(0x00000001);
		this->coconuttree[i]->setPhysicsBody(treebody1);
		treebody1->setDynamic(false);
	}
	coconuttree[6]->setPosition(Vec2(752, 200));
	coconuttree[7]->setPosition(Vec2(596, 410));
	coconuttree[8]->setPosition(Vec2(1756, 312));
	coconuttree[9]->setPosition(Vec2(45, 301));
	coconuttree[10]->setPosition(Vec2(450, 246));
	coconuttree[11]->setPosition(Vec2(862, 175));
	return true;
}

bool VillageMap::init()
{
	if (!MapNode::init())
		return false;
	this->ground = Sprite::create("mapresource/village_ground.png");
	winter = Director::getInstance()->getTextureCache()->addImage("mapresource/village_ground_winter.png");
	spring = Director::getInstance()->getTextureCache()->addImage("mapresource/village_ground.png");
	this->ground->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2));
	this->scheduleUpdate();
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
	for (int i = 0; i < 12; i++)
	{
		if (i % 4 == 0)
		{
			tree[i] = Plant::create("Plantsource/tree1_spring.png", "Plantsource/tree1_summer.png", "Plantsource/tree1_fall.png", "Plantsource/tree1_winter.png");
			tree[i]->setScale(1.4f);
		}
		else if (i % 4 == 1)
		{
			tree[i]=Plant::create("Plantsource/tree2_spring.png", "Plantsource/tree2_summer.png", "Plantsource/tree2_fall.png", "Plantsource/tree2_winter.png");
			tree[i]->setScale(1.8f);
		}
		else if (i % 4 == 2)
		{
			tree[i]= Plant::create("Plantsource/tree3_spring.png", "Plantsource/tree3_spring.png", "Plantsource/tree3_fall.png", "Plantsource/tree3_winter.png");
			tree[i]->setScale(2.0f);
		}
		else if (i % 4 == 3)
		{
			tree[i]= Plant::create("Plantsource/tree4_spring.png", "Plantsource/tree4_summer.png", "Plantsource/tree4_fall.png", "Plantsource/tree4_winter.png");
			tree[i]->setScale(1.6f);
		}
		tree[i]->setAnchorPoint(Vec2(0.5, 0));
		this->addChild(this->tree[i], 20);
		auto treebody = PhysicsBody::createBox(tree[i]->_spriteAutumn->getContentSize());
		treebody->setMass(100000);
		treebody->setCollisionBitmask(0x00000001);
		this->tree[i]->setPhysicsBody(treebody);
		treebody->setDynamic(false);
	}
	tree[0]->setPosition(Vec2(214, 806));
	tree[1]->setPosition(Vec2(325,143));
	tree[2]->setPosition(Vec2(1827, 154));
	tree[3]->setPosition(Vec2(1820, 754));
	tree[4]->setPosition(Vec2(244, 485));
	tree[5]->setPosition(Vec2(1250, 576));
	tree[6]->setPosition(Vec2(845, 726));
	tree[7]->setPosition(Vec2(244, 602));
	tree[8]->setPosition(Vec2(616, 576));
	tree[9]->setPosition(Vec2(238, 356));
	tree[10]->setPosition(Vec2(945, 756));
	tree[11]->setPosition(Vec2(1150, 489));
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
void VillageMap::update(float dt)
{
	timeSinceLastSeasonChange += dt;
	//timeSinceLastSeasonChange >= switchtime &&
	// 检查是否已经过去了switchtime秒
	if (timeSinceLastSeasonChange >= switchtime)
	{
		CCLOG("1");
		timeSinceLastSeasonChange = 0.0f; // 重置计时器
		nowSeason = (nowSeason + 1) % 4; // 循环季节
		switchseason(nowSeason);
	}
}
void VillageMap::switchseason(int season)
{
	if (season == 0)
	{
		ground->setTexture(spring);
	}
	if (season == 3)
	{
		ground->setTexture(winter);
	}
}

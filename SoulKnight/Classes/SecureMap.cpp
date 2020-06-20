#include "SecureMap.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "SettingScene.h"
#include "WildMap.h"

USING_NS_CC;
extern std::shared_ptr<Hero> globalHero;
extern int globalCoin;

Scene* SecureMap::createScene()
{
	return SecureMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SecureMapScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SecureMap::init()
{
	//////////////////////////////
	// 1. Ԥ����ʼ��
	//
	/////////////////////
	// 1.1 �����ʼ��
	//
	if (!Scene::init())
	{
		return false;
	}
	if (!Scene::initWithPhysics()) {
		return false;
	}

	/////////////////////
	// 1.2 ��Ա��ʼ��
	//
	interactStatus.door = 0;
	interactStatus.hunter = 0;
	interactStatus.oldMan = 0;
	bulletIndex = 0;

	/////////////////////
	// 1.2 ������Ϣ��ȡ
	//
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 destination(origin.x + visibleSize.width, origin.y + visibleSize.height);

	/////////////////////
	// 1.3 ��Դ����											hth
	//
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("new.plist");
	if (AudioEngine::getPlayingAudioCount())
	{
		AudioEngine::resume(0);
	}
	else
	{
		auto backgroundAudioID = AudioEngine::play2d("bgm2.mp3", true);
	}

	/////////////////////////////
	// 2. ������ʼ�������ǵ�ͼ����������skyworld��				hth
	//
	auto background = DrawNode::create();
	background->drawSolidRect(origin, destination, cocos2d::Color4F(195 / 255.0f, 176 / 255.0f, 145 / 255.0f, 1.0f));
	this->addChild(background, -10);

	/////////////////////////////
	// 3. NPC��ʼ����addNPC������								hth��cyf
	//
	auto hunter = initNPC("hunter.png");
	hunter->getPhysicsBody()->setTag(ASPDNPC);
	auto oldMan = initNPC("oldman.png");
	oldMan->getPhysicsBody()->setTag(SPEEDNPC);

	/////////////////////////////
	//  4. hero ��ʼ��										cyf
	//
	//����ǰһ��������,�˴γ�ʼ��������λ�ü�physicsBody
	globalHero = Hero::createWithSpriteFrameName("hero1right.png");
	globalHero->setSpeed(500.0f);
	globalHero->setScale(0.3f, 0.3f);
	initHero();

	/////////////////////////////
	// 5. ��ͼ��ʼ��											hth��cyf
	//
	_tiledmap = TMXTiledMap::create("safemap.tmx");
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2(origin.x, origin.y + 70));
	this->addChild(_tiledmap, -1);

	/////////////////////////////
	// 5.1 ��ͼ��Ƭ��ʼ��											hth��cyf
	//
	initLayer();

	/////////////////////////////
	// 5.2 ��ͼ��NPC��Hero��ʼ��											hth��cyf
	//
	TMXObjectGroup* objectGroup = _tiledmap->getObjectGroup("object");
	auto heroBornPlace = objectGroup->getObject("born");
	auto hunterBornPlace = objectGroup->getObject("hunter");
	auto oldmanBornPlace = objectGroup->getObject("oldman");

	float bornX = heroBornPlace["x"].asFloat();
	float bornY = heroBornPlace["y"].asFloat();
	float hunterX = hunterBornPlace["x"].asFloat();
	float hunterY = hunterBornPlace["y"].asFloat();
	float oldmanX = oldmanBornPlace["x"].asFloat();
	float oldmanY = oldmanBornPlace["y"].asFloat();

	globalHero->setPosition(Vec2(bornX, bornY));
	hunter->setPosition(Vec2(hunterX, hunterY));
	oldMan->setPosition(Vec2(oldmanX, oldmanY));

	_tiledmap->addChild(hunter, 11);
	_tiledmap->addChild(oldMan, 20);
	_tiledmap->addChild(globalHero.get(), 30);

	/////////////////////
	// 6 ���̼���														cyf
	//���ƶ� WASD�������� J����������NPC��Hero�Ի� space�������ܼ� K���������� L��
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(SecureMap::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(SecureMap::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, _tiledmap);

	/////////////////////
	// 7 ��ײ��⣨NPC��Hero�Ի������ӵ���NPC�����ӵ���ǽ�壩	cyf
	//
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(SecureMap::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(SecureMap::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, _tiledmap);

	/////////////////////////////
	// 8. ��������ʼ����Hero��Ѫ���������Լ���ң�ħ������һ�ࣩ			hth
	//

	auto bloodBar = ui::Slider::create();
	bloodBar->setEnabled(false);
	bloodBar->loadBarTexture("emptybar.png");
	bloodBar->loadProgressBarTexture("fullblood.png");
	bloodBar->setPercent(100);
	bloodBar->setPosition(Vec2(origin.x + bloodBar->getContentSize().width / 2, origin.y + visibleSize.height - bloodBar->getContentSize().height / 2));
	this->addChild(bloodBar, 200);

	auto blueBar = ui::Slider::create();
	blueBar->setEnabled(false);
	blueBar->loadBarTexture("emptybar.png");
	blueBar->loadProgressBarTexture("fullblue.png");
	blueBar->setPercent(100);
	blueBar->setPosition(Vec2(origin.x + bloodBar->getContentSize().width / 2, origin.y + visibleSize.height - bloodBar->getContentSize().height - blueBar->getContentSize().height / 2 - 10));
	this->addChild(blueBar, 200);

	auto shieldBar = ui::Slider::create();
	shieldBar->setEnabled(false);
	shieldBar->loadBarTexture("emptybar.png");
	shieldBar->loadProgressBarTexture("fullshield.png");
	shieldBar->setPercent(100);
	shieldBar->setPosition(Vec2(origin.x + bloodBar->getContentSize().width / 2, origin.y + visibleSize.height - bloodBar->getContentSize().height - blueBar->getContentSize().height - shieldBar->getContentSize().height / 2 - 20));
	this->addChild(shieldBar, 200);

	/////////////////////////////
	// 9. �˵���ʼ��											hth
	//
	auto pause = MenuItemLabel::create(Label::createWithTTF("pause", "fonts/Marker Felt.ttf", 48), CC_CALLBACK_1(SecureMap::pausemenu, this));
	auto menu = Menu::createWithItem(pause);
	menu->setPosition(Vec2(origin.x + visibleSize.width - pause->getContentSize().width / 2 - 20, origin.y + visibleSize.height - pause->getContentSize().height / 2));
	this->addChild(menu, 300);

	/////////////////////////////
	// 10 ���ļ���										hth
	//

	return true;
}

Sprite *SecureMap::initNPC(const std::string& spriteFrameName) {
	auto npc = cocos2d::Sprite::createWithSpriteFrameName(spriteFrameName);
	npc->setAnchorPoint(Vec2(0.5, 0.1));

	auto physicsBody = cocos2d::PhysicsBody::createBox(
		npc->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(NPC);
	physicsBody->setCollisionBitmask(HERO);
	physicsBody->setContactTestBitmask(HERO | MY_BULLET);

	npc->addComponent(physicsBody);

	npc->setScale(2.5);
	return npc;
}

void SecureMap::initHero() {
	globalHero->setAnchorPoint(Vec2(0.38, 0.1));

	auto physicsBody = cocos2d::PhysicsBody::createBox(
		Size(globalHero->getContentSize().width, globalHero->getContentSize().height * 2 / 5),
		PhysicsMaterial(0.0f, 0.0f, 0.0f), Vec2(0.0f, -0.3f*globalHero->getContentSize().height));
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setTag(HERO);
	physicsBody->setCategoryBitmask(HERO);
	physicsBody->setCollisionBitmask(WALL | NPC);
	physicsBody->setContactTestBitmask(DOOR | NPC);

	globalHero->addComponent(physicsBody);
}

void SecureMap::initBullet(std::shared_ptr<Bullet> bullet) {
	auto physicsBody = PhysicsBody::createBox(
		bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	//physicsBody->setGravityEnable(false);
	//physicsBody->setRotationEnable(false);
	physicsBody->setTag(MY_BULLET);
	physicsBody->setCategoryBitmask(MY_BULLET);
	physicsBody->setCollisionBitmask(0x00);
	physicsBody->setContactTestBitmask(DOOR | NPC | WALL);

	bullet->addComponent(physicsBody);

	bullet->setTag(++bulletIndex);
	bulletManagement[bullet->getTag()] = bullet;
	bullet->setPosition(globalHero->getPosition());
}

void SecureMap::initWall(Sprite *wall) {
	auto physicsBody = PhysicsBody::createBox(
		wall->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(WALL);
	physicsBody->setCategoryBitmask(WALL);
	physicsBody->setCollisionBitmask(HERO);
	physicsBody->setContactTestBitmask(MY_BULLET);

	wall->addComponent(physicsBody);
}

void SecureMap::initDoor(Sprite *door) {
	auto physicsBody = PhysicsBody::createBox(
		door->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(DOOR);
	physicsBody->setCategoryBitmask(DOOR);
	physicsBody->setCollisionBitmask(0x00);
	physicsBody->setContactTestBitmask(HERO);

	door->addComponent(physicsBody);
}

void SecureMap::initLayer() {
	//wall
	auto layer2 = _tiledmap->getLayer("layer2");
	for (int i = 3; i < 28; ++i) {
		initWall(layer2->getTileAt(Vec2(1, i)));
	}
	for (int i = 2; i < 62; ++i) {
		initWall(layer2->getTileAt(Vec2(i, 26)));
		//layer2->getTileAt(Vec2(i, 26))->setGlobalZOrder(100);
		//layer2->getTileAt(Vec2(i, 27))->setGlobalZOrder(100);
		//layer2->getTileAt(Vec2(i, 26))//->getParent()->reorderChild(layer2->getTileAt(Vec2(i, 26)), 666);
	}
	for (int i = 28; i > 3; --i) {
		initWall(layer2->getTileAt(Vec2(62, i)));
	}
	for (int i = 62; i > 1; --i) {
		initWall(layer2->getTileAt(Vec2(i, 3)));
	}

	//tree
	auto layer6 = _tiledmap->getLayer("layer6");
	for (int i = 4; i < 26; ++i) {
		initWall(layer6->getTileAt(Vec2(2, i)));
		initWall(layer6->getTileAt(Vec2(61, i)));
	}
	for (int i = 3; i < 12; ++i) {
		initWall(layer6->getTileAt(Vec2(i, 4)));
	}
	for (int i = 53; i < 61; ++i) {
		initWall(layer6->getTileAt(Vec2(i, 4)));
	}

	//bookshelf
	auto layer7 = _tiledmap->getLayer("layer7");
	for (int i = 42; i < 50; ++i) {
		initWall(layer7->getTileAt(Vec2(i, 4)));
	}
	for (int i = 15; i < 23; ++i) {
		initWall(layer7->getTileAt(Vec2(i, 4)));
	}
	auto layer8 = _tiledmap->getLayer("layer8");
	initWall(layer8->getTileAt(Vec2(13, 4)));
	initWall(layer8->getTileAt(Vec2(14, 4)));
	initWall(layer8->getTileAt(Vec2(50, 4)));
	initWall(layer8->getTileAt(Vec2(51, 4)));

	//seat
	auto layer9 = _tiledmap->getLayer("layer9");
	initWall(layer9->getTileAt(Vec2(39, 4)));
	initWall(layer9->getTileAt(Vec2(40, 4)));
	initWall(layer9->getTileAt(Vec2(41, 4)));
	initWall(layer9->getTileAt(Vec2(23, 4)));
	initWall(layer9->getTileAt(Vec2(24, 4)));
	initWall(layer9->getTileAt(Vec2(25, 4)));

	//door
	auto layer4 = _tiledmap->getLayer("layer4");
	initDoor(layer4->getTileAt(Vec2(31, 3)));
	initDoor(layer4->getTileAt(Vec2(32, 3)));
	initDoor(layer4->getTileAt(Vec2(33, 3)));
}

bool SecureMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	static auto heroLeft = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1left.png");
	static auto heroRight = SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1right.png");

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		globalHero->getPhysicsBody()->setVelocity(Vec2(0, globalHero->getSpeed()));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (!globalHero->isTowardLeft()) {
			globalHero->setSpriteFrame(heroLeft);
			globalHero->setToward(true);
		}
		globalHero->getPhysicsBody()->setVelocity(Vec2(-globalHero->getSpeed(), 0));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		globalHero->getPhysicsBody()->setVelocity(Vec2(0, -globalHero->getSpeed()));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (globalHero->isTowardLeft()) {
			globalHero->setSpriteFrame(heroRight);
			globalHero->setToward(false);
		}
		globalHero->getPhysicsBody()->setVelocity(Vec2(globalHero->getSpeed(), 0));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		shoot();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		break;
	default:
		break;
	}
	return true;
}

bool SecureMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	Vec2 velocity = globalHero->getPhysicsBody()->getVelocity();
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		interact();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		if (velocity.y > 0)
			globalHero->getPhysicsBody()->setVelocity(Vec2(velocity.x, 0));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		if (velocity.y < 0)
			globalHero->getPhysicsBody()->setVelocity(Vec2(velocity.x, 0));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		if (velocity.x < 0)
			globalHero->getPhysicsBody()->setVelocity(Vec2(0, velocity.y));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		if (velocity.x > 0)
			globalHero->getPhysicsBody()->setVelocity(Vec2(0, velocity.y));
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		break;
	default:
		break;
	}
	return true;
}

bool SecureMap::onContactBegin(cocos2d::PhysicsContact& contact) {
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	//�ӵ�������
	if (bodyA->getTag()&MY_BULLET) {
		bodyA->getNode()->removeFromParentAndCleanup(true);
		bulletManagement.erase(bodyA->getNode()->getTag());
		return true;
	}
	if (bodyB->getTag()&MY_BULLET) {
		bodyB->getNode()->removeFromParentAndCleanup(true);
		bulletManagement.erase(bodyB->getNode()->getTag());
		return true;
	}
	//Hero ����
	if ((bodyA->getTag()&HERO && bodyB->getTag()&DOOR) ||
		(bodyA->getTag()&DOOR && bodyB->getTag()&HERO)) {
		interactStatus.door = 1;
		return false;
	}
	//Hero��Npc
	return true;
}

bool SecureMap::onContactSeparate(cocos2d::PhysicsContact& contact) {
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	//Hero ����
	if ((bodyA->getTag()&HERO && bodyB->getTag()&DOOR) ||
		(bodyA->getTag()&DOOR && bodyB->getTag()&HERO)) {
		interactStatus.door = 0;
		return false;
	}
	//Hero��NPC
}

void SecureMap::pausemenu(cocos2d::Ref* pSender)
{
	AudioEngine::pause(0);
	Director::getInstance()->pause();
	Scene* settingScene = Setting::createScene();
	Director::getInstance()->pushScene(settingScene);
}

void SecureMap::interact() {
	if (interactStatus.door) {
		//�л�����ǰ�Ĵ���
		//1.ɾ��������Hero����ʾ
		globalHero->removeFromParentAndCleanup(false);
		//2.bulletMangement���
		bulletManagement.clear();
		Director::getInstance()->pushScene(TransitionJumpZoom::create(2.0f, WildMap::createScene()));
		return;
	}
	//NPC����
}

void SecureMap::shoot() {
	if (!globalHero->shoot()) {
		return;
	}
	auto haveBullet = globalHero->getWeaponInstance()->getBulletInstance();
	if (!haveBullet) {//��ս
	}
	else {//Զ��
		auto bullet = static_cast<std::shared_ptr<Bullet>>(haveBullet->clone(false));
		initBullet(bullet);
		if (globalHero->isTowardLeft()) {
			bullet->setSpriteFrame(
				SpriteFrameCache::getInstance()->getSpriteFrameByName("bulletleft.png"));
			bullet->getPhysicsBody()->setVelocity(Vec2(-bullet->getSpeed(), 0));
		}
		else {
			bullet->setSpriteFrame(
				SpriteFrameCache::getInstance()->getSpriteFrameByName("bulletright.png"));
			bullet->getPhysicsBody()->setVelocity(Vec2(bullet->getSpeed(), 0));
		}
	}
}
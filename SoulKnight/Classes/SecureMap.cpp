#include "SecureMap.h"

USING_NS_CC;

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
	// 1.2 ������Ϣ��ȡ
	//
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 destination(origin.x + visibleSize.width, origin.y + visibleSize.height);

	/////////////////////
	// 1.3 ��Դ����											hth
	//
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("spritesheet.plist");

	/////////////////////////////
	// 2. ������ʼ�������ǵ�ͼ����������skyworld��				hth
	//
	auto background = DrawNode::create();
	background->drawSolidRect(origin, destination, cocos2d::Color4F(195 / 255.0f, 176 / 255.0f, 145 / 255.0f, 1.0f));
	this->addChild(background, -10);
	/////////////////////////////
	//  NPC��ʼ����addNPC������								hth��cyf
	//
	auto hunter = initNPC("hunternpc.png");
	auto oldMan = initNPC("oldmannpc.png");

	/////////////////////////////
	//  hero ���ʼ��										cyf
	//
	//����ǰһ��������

	/////////////////////////////
	// 3. ��ͼ��ʼ��											hth��cyf
	//
	_tiledmap = TMXTiledMap::create("safemap.tmx");
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2(origin.x, origin.y + 70));
	this->addChild(_tiledmap);

	hunter->setPosition(Vec2(origin.x+512, origin.y + visibleSize.height - 320));
	oldMan->setPosition(Vec2(origin.y + visibleSize.width-512, origin.y + visibleSize.height -320));
	_tiledmap->addChild(hunter);
	_tiledmap->addChild(oldMan);

	/////////////////////////////
	// 5. Hero��ʼ����Hero��ʼ��Ӧ����һ��ѡ��Ӣ�۳�������ɣ�	hth��cyf
	//    �˴γ�ʼ��������λ�ü�physicsBody�������ʼ����
	//

	/////////////////////
	// 5.1 ���̼�����NPC��Hero�Ի���							cyf
	//
	/////////////////////
	// 5.1.1 ���̼������ƶ�����WASD��							cyf
	//

	/////////////////////
	// 5.1.2 ���̼�������������J��							cyf
	//

	/////////////////////////////
	// 5.1.3 ���̼���������������space��						cyf
	//

	/////////////////////
	// 5.1.3 ���̼��������ܼ������õ����ã�					cyf
	//

	/////////////////////
	// 5.1.4 ���̼������������������õ����ã�					cyf
	//

	/////////////////////
	// 5.2 ��ײ��⣨NPC��Hero�Ի������ӵ���NPC�����ӵ���ǽ�壩	cyf
	//

	/////////////////////////////
	// 6. ��������ʼ����Hero��Ѫ���������Լ���ң�ħ������һ�ࣩ			hth
	//

	/////////////////////////////
	// 7. �˵���ʼ��											hth
	//

	/////////////////////////////
	// 7.1 ���ļ���										hth
	//

	return true;
}

Sprite *SecureMap::initNPC(const std::string& spriteFrameName) {
	auto npc = cocos2d::Sprite::createWithSpriteFrameName(spriteFrameName);

	auto physicsBody = cocos2d::PhysicsBody::createBox(
		npc->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(NPC);
	physicsBody->setCategoryBitmask(0x04);
	physicsBody->setCollisionBitmask(0x01);
	physicsBody->setContactTestBitmask(0x0A);

	npc->addComponent(physicsBody);

	return npc;
}

std::shared_ptr<Hero> SecureMap::initHero(std::shared_ptr<Hero> hero) {
	auto physicsBody = cocos2d::PhysicsBody::createBox(
		hero->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(HERO);
	physicsBody->setCategoryBitmask(0x04);
	physicsBody->setCollisionBitmask(0x01);
	physicsBody->setContactTestBitmask(0x0A);

	hero->addComponent(physicsBody);

	return hero;
}
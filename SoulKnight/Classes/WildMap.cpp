#include "WildMap.h"

USING_NS_CC;
using namespace std;

extern std::shared_ptr<Hero> globalHero;

Scene* WildMap::createScene()
{
	return WildMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in WildMapScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WildMap::init()
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
	// 1.2��Ա��ʼ��
	//
	_hero = globalHero;
	_hero->setSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1right.png"));

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

	/////////////////////
		// 1.3.1 �������ʼ������Ӧ�ӵ���ʼ����					hth
		//�뷨�������һ��vector<std::shared_ptr<Weapon>>����ǰ��ʼ���������������Թ�С�ֱ�����ʱֱ�Ӹ���Weapon
	auto gun1left = RangedWeapon::createWithSpriteFrameName("gun1left.png");
	auto gun1right = RangedWeapon::createWithSpriteFrameName("gun1right.png");
	auto gun2left = RangedWeapon::createWithSpriteFrameName("gun2left.png");
	auto gun2right = RangedWeapon::createWithSpriteFrameName("gun2right.png");
	auto gun3left = RangedWeapon::createWithSpriteFrameName("gun3left.png");
	auto gun3right = RangedWeapon::createWithSpriteFrameName("gun3right.png");
	auto swordleft = CloseInWeapon::createWithSpriteFrameName("swordleft.png");
	auto swordright = CloseInWeapon::createWithSpriteFrameName("swordright.png");
	auto blade1left = CloseInWeapon::createWithSpriteFrameName("blade1left.png");
	auto blade1right = CloseInWeapon::createWithSpriteFrameName("blade1right.png");
	auto meteorhammerleft = CloseInWeapon::createWithSpriteFrameName("meteorhammerleft.png");
	auto meteorhammerright = CloseInWeapon::createWithSpriteFrameName("meteorhammerright.png");
	auto wandleft = RangedWeapon::createWithSpriteFrameName("wandleft.png");
	auto wandright = RangedWeapon::createWithSpriteFrameName("wandright.png");

	auto bulletleft = Bullet::createWithSpriteFrameName("bulletleft.png");
	auto bulletright = Bullet::createWithSpriteFrameName("bulletright.png");
	auto elementalbulletleft = Bullet::createWithSpriteFrameName("bluefireleft.png");
	auto elementalbulletright = Bullet::createWithSpriteFrameName("bluefireright.png");
	/*weaponVec.push_back(gun1left);
	weaponVec.push_back(gun1right);
	weaponVec.push_back(gun2left);
	weaponVec.push_back(gun2right);
	weaponVec.push_back(gun3left);
	weaponVec.push_back(gun3right);
	weaponVec.push_back(swordleft);
	weaponVec.push_back(swordright);
	weaponVec.push_back(blade1left);
	weaponVec.push_back(blade1right);
	weaponVec.push_back(wandleft);
	weaponVec.push_back(wandright);
	weaponVec.push_back(meteorhammerleft);
	weaponVec.push_back(meteorhammerright);*/

	/////////////////////////////
	// 2. ������ʼ�������ǵ�ͼ����������skyworld��				hth
	//
	auto background = DrawNode::create();
	background->drawSolidRect(origin, destination, cocos2d::Color4F(195 / 255.0f, 176 / 255.0f, 145 / 255.0f, 1.0f));
	this->addChild(background, -10);
	/////////////////////////////
	// 3. ��ͼ��ʼ��											hth��cyf
	//
	_tiledmap = TMXTiledMap::create("map1.tmx");
	_tiledmap->setAnchorPoint(Vec2(0, 1));
	_tiledmap->setPosition(Vec2(origin.x + 320, origin.y + visibleSize.height - 70));
	this->addChild(_tiledmap, -1);
	/////////////////////////////
	// 4. С�֣���Boss����ʼ��								xyc
	//����

	/////////////////////////////
	// 5. Hero ��ʼ��										cyf
	//

	/////////////////////
	// 5.1 Hero �� Weapon ��װ								xyc
	//

	/////////////////////
	// 5.2 ���̼�����NPC��Hero�Ի���							cyf
	//
	/////////////////////
	// 5.2.1 ���̼������ƶ�����WASD��							cyf
	//

	/////////////////////
	// 5.2.2 ���̼�������������J��							cyf
	//

	/////////////////////////////
	// 5.2.3 ���̼���������������space��						cyf
	//

	/////////////////////
	// 5.2.3 ���̼��������ܣ���K��							cyf
	//

	/////////////////////
	// 5.2.4 ���̼���������������L��							xyc��cyf
	//

	/////////////////////
	// 5.3 ��ײ���
	//�������ͼ�飩����ʼ�����ƶ������������ҷ��ӵ�����ˣ����з��ӵ����ҷ�����˫���ӵ���ǽ�壩�����ڣ�
	/////////////////////
	// 5.3.1 ��ײ��⣨�����ͼ�飩							cyf
	//
	/////////////////////
	// 5.3.1.1 С�ּ����ʼ�����ƶ���������					xyc
	//����
	/////////////////////
	// 5.3.2 ��ײ��⣨�ҷ��ӵ�����ˣ����з��ӵ����ҷ�����˫���ӵ���ǽ�壩		cyf
	//
	/////////////////////
	// 5.3.3 ��ײ��⣨���ڣ�									cyf
	//

	/////////////////////////////
	// 6. ��������ʼ����Hero��Ѫ���������Լ���ң�ħ������һ�ࣩ				hth
	//

	/////////////////////////////
	// 7. �˵���ʼ��											hth
	//

	/////////////////////////////
	// 7.1 ���ļ���										hth
	//

	/////////////////////////////
	// 8 camera ��ʼ��										cyf
	//

	return true;
}

void WildMap::initBullet(std::shared_ptr<Damage> bullet) {
	auto physicsBody = PhysicsBody::createBox(
		bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);
	physicsBody->setTag(MY_BULLET);
	physicsBody->setCategoryBitmask(MY_BULLET);
	physicsBody->setCollisionBitmask(0x00);
	physicsBody->setContactTestBitmask(DOOR | NPC | WALL);

	bullet->addComponent(physicsBody);
}

void WildMap::initWall(Sprite *wall) {
	auto physicsBody = PhysicsBody::createBox(
		wall->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(WALL);
	physicsBody->setCategoryBitmask(WALL);
	physicsBody->setCollisionBitmask(HERO);
	physicsBody->setContactTestBitmask(MY_BULLET);

	wall->addComponent(physicsBody);
}

void WildMap::initLayer() {
	//wall
	auto layer2 = _tiledmap->getLayer("layer2");
}
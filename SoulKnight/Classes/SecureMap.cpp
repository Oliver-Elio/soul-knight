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

	/////////////////////
	// 1.2 ������Ϣ��ȡ
	//
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////
	// 1.3 ��Դ����
	//

	/////////////////////////////
	// 2. ������ʼ�������ǵ�ͼ����������skyworld��
	//

	/////////////////////////////
	// 3. ��ͼ��ʼ��
	//

	/////////////////////////////
	// 4. NPC��ʼ����addNPC������
	//

	/////////////////////////////
	// 5. Hero��ʼ����Hero��ʼ��Ӧ����һ��ѡ��Ӣ�۳�������ɣ�
	//    �˴γ�ʼ��������λ�ü�physicsBody����addHero������
	//

	/////////////////////
	// 5.1 ���̼�����NPC��Hero�Ի���
	//
	/////////////////////
	// 5.1.1 ���̼������ƶ�����WASD��
	//

	/////////////////////
	// 5.1.2 ���̼�������������J��
	//

	/////////////////////////////
	// 5.1.3 ���̼���������������space��
	//

	/////////////////////
	// 5.1.3 ���̼��������ܼ������õ����ã�
	//

	/////////////////////
	// 5.1.4 ���̼������������������õ����ã�
	//

	/////////////////////
	// 5.2 ��ײ��⣨NPC��Hero�Ի������ӵ���NPC�����ӵ���ǽ�壩
	//

	/////////////////////////////
	// 6. ��������ʼ����Hero��Ѫ���������Լ���ң�ħ������һ�ࣩ
	//

	/////////////////////////////
	// 7. �˵���ʼ��
	//

	/////////////////////////////
	// 7.1 ���ļ���
	//

	return true;
}

void SecureMap::addNPC(const std::string& spriteFrameName, cocos2d::Vec2 pos) {
	auto npc = cocos2d::Sprite::createWithSpriteFrameName(spriteFrameName);
	npc->setPosition(pos);

	auto physicsBody = cocos2d::PhysicsBody::createBox(
		npc->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(NPC);
	physicsBody->setCategoryBitmask(0x04);
	physicsBody->setCollisionBitmask(0x01);
	physicsBody->setContactTestBitmask(0x0A);

	npc->addComponent(physicsBody);
	this->addChild(npc, 30);
}

void SecureMap::addHero(std::shared_ptr<Hero> hero) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	hero->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	auto physicsBody = cocos2d::PhysicsBody::createBox(
		hero->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setTag(HERO);
	physicsBody->setCategoryBitmask(0x04);
	physicsBody->setCollisionBitmask(0x01);
	physicsBody->setContactTestBitmask(0x0A);

	hero->addComponent(physicsBody);
	this->addChild(hero.get(), 40);
}
#include "WildMap.h"

USING_NS_CC;

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
	/////////////////////
	// 1.2 ������Ϣ��ȡ
	//
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////
	// 1.3 ��Դ����											hth
	//

	/////////////////////
	// 1.3.1 �������ʼ������Ӧ�ӵ���ʼ����					hth
	//�뷨�������һ��vector<std::shared_ptr<Weapon>>����ǰ��ʼ���������������Թ�С�ֱ�����ʱֱ�Ӹ���Weapon

	/////////////////////////////
	// 2. ������ʼ�������ǵ�ͼ����������skyworld��				hth
	//

	/////////////////////////////
	// 3. ��ͼ��ʼ��											hth��cyf
	//

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
	//
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

void WildMap::addHero(std::shared_ptr<Hero> hero) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//hero->setPosition(Vec2(origin.x + visibleSize.width / 2,
		//origin.y + visibleSize.height / 2));

	this->addChild(hero.get(), 40);
}
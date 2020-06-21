#ifndef __WILD_MAP_H__
#define __WILD_MAP_H__

#include "GlobalVariable.h"
#include <ctime>
#include <random>

class WildMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(WildMap);

private:
	TMXTiledMap* _tiledmap;
	struct {
		unsigned int conductor : 1;
		unsigned int box : 1;
		unsigned int : 1;
		unsigned int : 1;
	} _interactStatus;

	Vec2 _initiativeHeroOffset;
	Vec2 _initiativeMapOffset;

	//С����Դ�����������䣩
	//std::vector<char> _roomStatus;//0��ʾδ���룬1��ʾ���ڷ����2��ʾ��̽��

	//ZOrder
	int _bulletZOrder;
	int _monsterZorder;

	int curRoomNum = 0;

	void initMember();
	void releaseMember();

	//���������ʼ��
	void initHero();
	void initEnemy(std::shared_ptr<Monster> monster, int roomNum);
	void initMyBullet(std::shared_ptr<Bullet> bullet);
	void initEnemyBullet(std::shared_ptr<Bullet> bullet);
	void initWall(Sprite *wall);
	void initDoor(Sprite *door);
	void initBox(Sprite *box);
	void initConductor(Sprite *conductor);
	void initItem(std::shared_ptr<Item> item);
	void initLayer();

	void monstersAi();

	void addMonsterInRoom();
	void addconductor();
	//void addItem(Item::Type type);
	//���̼���
	bool onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	bool onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//��ײ���
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactSeparate(cocos2d::PhysicsContact& contact);

	//����
	void interact();
	//����
	void shoot();
	//����
	void skill();

	void positionMonitor();

	void update(float delta);
};

#endif // __WILD_MAP_H__
#ifndef __WILD_MAP_H__
#define __WILD_MAP_H__

#include "GlobalVariable.h"
#include "ui/CocosGUI.h"

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

	cocos2d::ui::Slider *healthBar;
	cocos2d::ui::Slider *shieldBar;
	cocos2d::ui::Slider *magicBar;

	Vec2 _initiativeHeroOffset;
	Vec2 _initiativeMapOffset;

	//С����Դ�����������䣩
	//std::vector<char> _roomStatus;//0��ʾδ���룬1��ʾ���ڷ����2��ʾ��̽��

	//ZOrder
	int _bulletZOrder;
	int _monsterZorder;

	bool _conductorHasAdded = 0;

	int curRoomNum = 0;

	void initMember();
	void releaseMember();

	//���������ʼ��
	void initLayer();

	//void monstersAi();

	void addMonsterInRoom(int roomNum);
	void addMonsterInRooms();
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

	//�����л�
	void changeWeaponActive();
	//����
	void skill();

	void aiShoot(std::shared_ptr<Monster> monster);
	void aiMove(std::shared_ptr<Monster> monster);

	void positionMonitor();

	void update(float delta);
	void updateShield(float delta);
	void aiInTwoSec(float delta);
	void aiInThreeSec(float delta);
};

#endif // __WILD_MAP_H__
#ifndef __WILD_MAP_H__
#define __WILD_MAP_H__

#include "GlobalVariable.h"

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
	} interactStatus;
	//Vector<std::shared_ptr<Weapon>> weaponVec;
	Vec2 _initiativeHeroOffset;
	Vec2 _initiativeMapOffset;
	int bulletIndex;
	std::map<int, std::shared_ptr<Bullet>> bulletManagement;

	//�ӵ���ʼ��

	//���������ʼ��
	void initHero();
	void initEnemy(std::shared_ptr<Monster> monster);
	void initMyBullet(std::shared_ptr<Bullet> bullet);
	void initEnemyBullet(std::shared_ptr<Bullet> bullet);
	void initWall(Sprite *wall);
	void initDoor(Sprite *door);
	void initBox(Sprite *box);
	void initConductor(Sprite *conductor);
	void initItem(std::shared_ptr<Item> item);
	void initLayer();

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

	void update(float delta);
};

#endif // __WILD_MAP_H__
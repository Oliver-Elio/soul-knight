#ifndef _SECURE_MAP_H_
#define _SECURE_MAP_H_

#include "GlobalVariable.h"
#include <map>

class SecureMap : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void pausemenu(cocos2d::Ref* pSender);//pause

	// implement the "static create()" method manually
	CREATE_FUNC(SecureMap);

private:

	TMXTiledMap* _tiledmap;
	struct {
		unsigned int door : 1;
		unsigned int oldMan : 1;
		unsigned int hunter : 1;
		unsigned int : 1;
	} interactStatus;
	std::map<int, std::shared_ptr<Damage>> bulletManagement;
	int bulletIndex;

	//����NPCͼƬ��PhysicsBody
	Sprite *initNPC(const std::string& spriteFrameName);

	//����hero PhysicsBody
	void initHero();

	//������ʼ��
	void initBullet(std::shared_ptr<Damage> bullet);

	//���������ʼ��
	void initWall(Sprite *wall);
	void initDoor(Sprite *door);
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
};

#endif // _SECURE_MAP_H_#pragma once

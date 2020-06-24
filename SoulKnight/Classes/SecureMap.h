#ifndef _SECURE_MAP_H_
#define _SECURE_MAP_H_

#include "GlobalVariable.h"
#include "ui/CocosGUI.h"

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

	cocos2d::ui::Slider *healthBar;
	cocos2d::ui::Slider *shieldBar;
	cocos2d::ui::Slider *magicBar;

	void initMember();
	void releaseMember();

	//���������ʼ��
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
	//������,ʵ��,��ͬ��hero.h��changeweapon
	void changeWeaponActive();
	//����
	void skill();

	void updateHeroStatus(float delta);
	void updateShield(float delta);
};

#endif // _SECURE_MAP_H_#pragma once

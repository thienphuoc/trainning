#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"


class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	int getScore() {
		return score;
	}
private:
	void SpawnPipe(float dt);
	Pipe pipe;
	Bird* bird;


	cocos2d::PhysicsWorld* sceneWorld;
	void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
		sceneWorld = world;
	}

	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void GoToGameOverScene(float dt);
	bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
	void StopFlying(float dt);
	void update(float dt);
	unsigned int score;
	cocos2d::Label* scoreLabel;

};

#endif // __GAME_SCENE_H__

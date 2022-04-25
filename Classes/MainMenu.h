#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// exit game
	void menuCloseCallback(float dt);

	//goto game scene
	void GotoGameScene(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
private:
};

#endif // __MAIN_MENU_SCENE_H__

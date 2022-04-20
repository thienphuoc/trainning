#pragma once
#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(float dt);
    void GoToGameScene(float dt);

    CREATE_FUNC(MainMenuScene);
private:
};

#endif // __MAIN_MENU_SCENE_H__

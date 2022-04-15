#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

class AboutScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(AboutScene);
private:
    void ReturnMainMenu(float dt);
 
};

#endif // __ABOUT_SCENE_H__

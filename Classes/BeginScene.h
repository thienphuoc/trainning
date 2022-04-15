#ifndef __BEGIN_SCENE_H__
#define __BEGIN_SCENE_H__

#include "cocos2d.h"

class BeginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(BeginScene);
	
private:
    void GoToMainMenu(float dt);
};

#endif // __BEGIN_SCENE_H__

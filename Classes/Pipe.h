#ifndef __PIPE_SCENE_H__
#define __PIPE_SCENE_H__

#include "cocos2d.h"

class Pipe : public cocos2d::Scene
{
public:
    Pipe();
    void SpawnPipe(cocos2d::Layer* layer);
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif // __PIPE_SCENE_H__

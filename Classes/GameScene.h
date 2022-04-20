#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Definations.h"
#include "AI.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* continueScene(int playerSc, int tieSc, int computerSc);
    virtual bool init();
    //void menuCloseCallback(float dt);
    void setPauseGameState(bool state) {
        pauseGameState = state;
    }
    bool getPauseGameState() {
        return pauseGameState;
    }

    int countNullNodeOfMap(m_Node arr[]) {
        int count = 0;
        for (int i = 0; i < 9; i++) {
            if (arr[i] == DEFAULSE) {
                count++;
           }
        }
        return count;
    }
    CREATE_FUNC(GameScene);
private:
    
    

    bool pauseGameState;
    m_Node gridGame[9] = {DEFAULSE};
    m_Node turn;
    bool CheckWin(int index);
    bool isWin(int a, int b, int c);
    void setTouchDisabledAllButton(cocos2d::Scene* scene);
    void setTouchEnabledAllButton(cocos2d::Scene* scene);
    void showScore(cocos2d::Scene* scene);
    void addScreenOverlay(cocos2d::Scene* scene, m_Node player);
    m_Node playerWon = DEFAULSE;
    void highlight(int index);
    void returnMainMenu(float dt);
    void ContinueGame(int playerSc, int tieSc, int computerSc);
    AI *ai;
};

#endif // __GAME_SCENE_H__
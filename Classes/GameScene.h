#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Board.h"
#include "BoardView.h"

class GameScene : public cocos2d::Scene
{
public:
	static GameScene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	Board* board;
private:

	BoardView* boardView;
	void timeCountdown(ui::LoadingBar* loading, float time);

	float time;
	bool isPause;
	bool isMute;
	int refreshCount = REFRESH_COUNT;

	void rePlayGame(float dt);
	void continueGame(int score);
	void update(float dt);

};

#endif // __GAME_SCENE_H__

#ifndef __RANK_SCENE_H__
#define __RANK_SCENE_H__

#include "cocos2d.h"

struct LeaderBoardInfo
{
	std::string m_name;
	int m_score;

	LeaderBoardInfo() {}

	LeaderBoardInfo(std::string i_name, int i_score) :
		m_name(i_name),
		m_score(i_score)
	{

	}
};

class RankScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(RankScene);
	std::vector<LeaderBoardInfo*> leader;
private:
    void GoToMainMenu(float dt);
	void loadData();
	void showData();
};

#endif // __RANK_SCENE_H__

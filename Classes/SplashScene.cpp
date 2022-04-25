#include "SplashScene.h"
#include "MainMenu.h"
#include "Definitation.h"
#include "AudioManager.h"

#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
	AudioManager::playBackgroundMusic();
	AudioManager::setBackgroundVolume(0.4f);
	return SplashScene::create();
}

bool SplashScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto splashScene = CSLoader::getInstance()->createNode("layer/splash-scene.csb");
	this->addChild(splashScene);

	auto loadingBar = utils::findChild<ui::LoadingBar*>(this, "loading-bar");
	auto loadingText = utils::findChild<ui::Text*>(this, "loading-text");
	percent = loadingBar->getPercent();
	this->schedule([=](float dt) {
		percent++;
		if (percent % 3 == 0) {
			loadingText->setString("Loading.  ");
		}
		else if (percent % 3 == 1) {
			loadingText->setString("Loading.. ");
		}
		else {
			loadingText->setString("Loading...");
		}
		loadingBar->setPercent(percent);
		if (percent >= 100) {
			loadingText->setString("Please Wait!!!");
			this->scheduleOnce(schedule_selector(SplashScene::GotoMainMenu), SPLASH_SCENE_SHOW_TIME);
			this->unschedule("updateLoadingBarr");
		}
		}, 0.01f, "updateLoadingBarr");

	//loadingBar->autorelease();
	return true;
}

void SplashScene::GotoMainMenu(float dt)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
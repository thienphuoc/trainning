#include "MainMenu.h"
#include "AudioManager.h"
#include "GameScene.h"
#include "Definitation.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto mainMenu = CSLoader::getInstance()->createNode("layer/main-menu.csb");
	this->addChild(mainMenu);

	auto playButton = utils::findChild<ui::Button*>(this, "play-button");
	playButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();
		this->scheduleOnce(schedule_selector(MainMenu::GotoGameScene), 0);
		});

	auto quitButton = utils::findChild<ui::Button*>(this, "quit-button");
	quitButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();
		this->scheduleOnce(schedule_selector(MainMenu::menuCloseCallback), 0);
		});
	return true;
}

void MainMenu::menuCloseCallback(float dt)
{
	Director::getInstance()->end();
}

void MainMenu::GotoGameScene(float dt)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
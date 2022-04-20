#include "MainMenuScene.h"
#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definations.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();

    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), SPLASH_SCENE_SHOW_TIME);

    auto splashScene = CSLoader::getInstance()->createNode("csb/SplashScene.csb");
    this->addChild(splashScene);

    //SonarCocosHelper::GameCenter::signIn();

    return true;
}

void SplashScene::GoToMainMenuScene(float dt)
{
    auto gameScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_TRANSITION_TIME, gameScene));
}

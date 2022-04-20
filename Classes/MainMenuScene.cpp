#include "MainMenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = MainMenuScene::create();

    auto layer = Layer::create();

    scene->addChild(layer);
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto mainMenu = CSLoader::getInstance()->createNode("csb/mainmenu.csb");
    this->addChild(mainMenu);

    auto exitButton = mainMenu->getChildByName<ui::Button*>("exit_button");
    exitButton->setPressedActionEnabled(true);
    exitButton->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(MainMenuScene::menuCloseCallback), 0);
        });
    auto playButton = mainMenu->getChildByName<ui::Button*>("play_button");
    playButton->setPressedActionEnabled(true);
    playButton->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(MainMenuScene::GoToGameScene), 0);
        });


    return true;
}

void MainMenuScene::menuCloseCallback(float dt)
{
    Director::getInstance()->end();
}

void MainMenuScene::GoToGameScene(float dt)
{
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, gameScene));
}

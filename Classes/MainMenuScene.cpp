#include "MainMenuScene.h"
#include "rankScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AboutScene.h"


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //    //hien thi back ground
    //auto background = Sprite::create("../Resources/images/background.png");
    //background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// thay doi kick thuoc background vua man hinh
    //background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    //this->addChild(background);
    //    // end spawn background
    //auto logo = Sprite::create("../Resources/my_image/Logo.png");
    //logo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 5 * 4 + origin.y));
    //logo->setScale(visibleSize.width / (logo->getContentSize().width * 3), visibleSize.height / (logo->getContentSize().height * 3));
    //this->addChild(logo);

    //auto btnPlay = MenuItemImage::create("../Resources/images/play_button.png", "../Resources/images/play_button.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    //btnPlay->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
    //btnPlay->setScale(visibleSize.width / (btnPlay->getContentSize().width * 6), visibleSize.height / (btnPlay->getContentSize().height * 6));
    //
    //auto menu = Menu::create(btnPlay, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu);



    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);



    auto buttonPlay = mainMenu->getChildByName<ui::Button*>("play_button");
    buttonPlay->setPressedActionEnabled(true);
    buttonPlay->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(MainMenuScene::GoToGameScene),0);
        });
    auto buttonAbout = mainMenu->getChildByName<ui::Button*>("about_button");
    buttonAbout->setPressedActionEnabled(true);
    buttonAbout->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(MainMenuScene::GoToAboutScene), 0);
        });
    auto buttonRank = mainMenu->getChildByName<ui::Button*>("rank_button");
    buttonRank->setPressedActionEnabled(true);
    buttonRank->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(MainMenuScene::GoToRankScene), 0);
        });
    auto buttonExit = mainMenu->getChildByName<ui::Button*>("exit_button");
    buttonExit->setPressedActionEnabled(true);
    buttonExit->addClickEventListener([=](Ref*) {
        this->onExit();
        });

    return true;
}

void MainMenuScene::GoToGameScene(float dt) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
void MainMenuScene::GoToAboutScene(float dt) {
    auto scene = AboutScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
void MainMenuScene::GoToRankScene(float dt) {
    auto scene = RankScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


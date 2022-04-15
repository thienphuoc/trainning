#include "BeginScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "rapidjson/document.h"

USING_NS_CC;
using namespace network;



Scene* BeginScene::createScene()
{
    return BeginScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BeginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(schedule_selector(BeginScene::GoToMainMenu), 1);


    auto background = Sprite::create("../Resources/my_image/SplashBackground.jpg");
    background->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // thay doi kick thuoc background vua man hinh
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    return true;
}


void BeginScene::GoToMainMenu(float dt) {
    auto mainMenu = MainMenuScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(0.5, mainMenu));
}



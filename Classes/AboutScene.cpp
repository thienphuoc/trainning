#include "AboutScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
    return AboutScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

   /* auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    */
    
    auto aboutScene = CSLoader::getInstance()->createNode("csb/About.csb");
    this->addChild(aboutScene);

    auto buttonReturn = aboutScene->getChildByName<ui::Button*>("return");
    buttonReturn->setPressedActionEnabled(true);
    buttonReturn->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(AboutScene::ReturnMainMenu), 0);
        });






    /*__String* gameName = __String::createWithFormat("Flappy Bird!");
    auto currentScore = LabelTTF::create(gameName->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.1 * 0.5);
    currentScore->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height / 16 * 9 + origin.y));
    __String* tempScore = __String::createWithFormat("Flappy Bird!");
    auto currentScore = LabelTTF::create(tempScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.1 * 0.5);
    currentScore->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height / 16 * 9 + origin.y));


    this->addChild(currentScore);*/


    
    return true;
}

void AboutScene::ReturnMainMenu(float dt) {
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*auto background = Sprite::create("../Resources/images/leaderboard/leader_board_bg.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    this->addChild(background);


    auto reTry = MenuItemImage::create("../Resources/images/play_button.png", "../Resources/images/play_button.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    reTry->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
    reTry->setScale(visibleSize.width / (reTry->getContentSize().width * 6), visibleSize.height / (reTry->getContentSize().height * 6));
    
    auto mainMenuItem = MenuItemImage::create("../Resources/images/about_button.png", "../Resources/images/about_button.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
    mainMenuItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height *0.25 + origin.y));
    mainMenuItem->setScale(visibleSize.width / (mainMenuItem->getContentSize().width * 6), visibleSize.height / (mainMenuItem->getContentSize().height * 6));


    auto menu = Menu::create(reTry, mainMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    UserDefault* def = UserDefault::getInstance();

    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
    if (score > highScore) {
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }

    def->flush();


    __String* tempScore = __String::createWithFormat("YOUR SCORE: %i", score);

    auto currentScore = LabelTTF::create(tempScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.1 * 0.5);
    currentScore->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height / 16 * 9 + origin.y));

    this->addChild(currentScore);

    __String* tempHighScore = __String::createWithFormat("HIGH SCORE: %i", highScore);

    auto highScoreLable = LabelTTF::create(tempHighScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.1 * 0.5);
    highScoreLable->setColor(Color3B::YELLOW);
    highScoreLable->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height / 16 * 7 + origin.y));

    this->addChild(highScoreLable);*/

    auto gameOver = CSLoader::getInstance()->createNode("csb/GameOver.csb");
    this->addChild(gameOver);

    auto buttonRetry = gameOver->getChildByName<ui::Button*>("retry");
    buttonRetry->setPressedActionEnabled(true);
    buttonRetry->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(GameOverScene::GoToGameScene), 0);
        });


    auto buttonReturnMain = gameOver->getChildByName<ui::Button*>("return_menu");
    buttonReturnMain->setPressedActionEnabled(true);
    buttonReturnMain->addClickEventListener([=](Ref*) {
        this->scheduleOnce(schedule_selector(GameOverScene::GoToMainMenuScene), 0);
        });

    UserDefault* def = UserDefault::getInstance();

    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
    if (score > highScore) {
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }

    def->flush();


    __String* tempScore = __String::createWithFormat("Your Score: %i", score);

    auto currentScore = LabelTTF::create(tempScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.1 * 0.5);
    currentScore->setColor(Color3B::GREEN);
    currentScore->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.8 + origin.y));

    this->addChild(currentScore);

    __String* tempHighScore = __String::createWithFormat("Hight Score: %i", highScore);

    auto highScoreLable = LabelTTF::create(tempHighScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.15 * 0.5);
    highScoreLable->setColor(Color3B::ORANGE);
    highScoreLable->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.65 + origin.y));

    this->addChild(highScoreLable);
    return true;
}


void GameOverScene::GoToMainMenuScene(float dt) {
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}
void GameOverScene::GoToGameScene(float dt) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

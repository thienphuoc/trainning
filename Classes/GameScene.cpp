#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

        //hien thi back ground
    auto background = Sprite::create("../Resources/my_image/background.png");
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    this->addChild(background);


    /// <summary>
    /// tao khung vat ly
    /// </summary>
    /// <returns></returns>
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);


    auto edgeNode = Sprite::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::SpawnPipe), 0.005 * visibleSize.width);

    bird = new Bird(this);

    // bat su kien va cham
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    // su kien click
    auto onTouch = EventListenerTouchOneByOne::create();
    onTouch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(onTouch, this);

    score = 0;

    __String* tempScore = __String::createWithFormat("Your Score: %i", score);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "../Resources/fonts/Marker Felt.ttf", visibleSize.height * 0.04);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setPosition(Point(visibleSize.width * 0.90 + origin.x, visibleSize.height * 0.95 + origin.y));

    this->addChild(scoreLabel, 10000);


    this->scheduleUpdate();
    return true;
}

void GameScene::SpawnPipe(float dt) {
    //CCLOG("abc");
    pipe.SpawnPipe(this);
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) || (a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK && b->getCollisionBitmask() == BIRD_COLLISION_BITMASK)) {
        auto scene = GameOverScene::createScene(score);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
    }
    else if ((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == POINT_COLLISION_BITMASK) || (a->getCollisionBitmask() == POINT_COLLISION_BITMASK && b->getCollisionBitmask() == BIRD_COLLISION_BITMASK)) {
        score++;
        __String* tempScore = __String::createWithFormat("Your Score: %i", score);
        scoreLabel->setString(tempScore->getCString());
    }
    return true;
}

bool GameScene::onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event) {
    bird->Fly();
    this->scheduleOnce(schedule_selector(GameScene::StopFlying), 0.25);
    return true;
}
void GameScene::StopFlying(float dt) {
    bird->StopFlying();
}
void GameScene::update(float dt) {
    bird->Fall();
}





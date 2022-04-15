#include "Bird.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer* layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    flappyBird = Sprite::create("../Resources/images/bird.png");
    flappyBird->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);


    /// <summary>
    /// create a physicbody circle around the bird to check contact
    /// </summary>
    /// <param name="layer"></param>
    auto flappyBirdBody = PhysicsBody::createCircle(flappyBird->getContentSize().width / 2);
    flappyBirdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBirdBody->setContactTestBitmask(true);

    flappyBird->setPhysicsBody(flappyBirdBody);

    layer->addChild(flappyBird, 1000);

    isFalling = true;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Bird::Fall() {
    if (isFalling == true) {
        /*auto birdDown = RotateBy::create(0.25, 0, 90);
        flappyBird->runAction(birdDown);*/
        flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() - (0.0025 * visibleSize.height));
    }
    else {
        //flappyBird->setTexture("../Resources/my_image/birdUp.png");
        flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() + (0.00375 * visibleSize.height));
    }
}
#include "Pipe.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
//#include "MainMenuScene.h"

USING_NS_CC;

Pipe::Pipe()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}
void Pipe::SpawnPipe(cocos2d::Layer* layer) {
    auto topPipe = Sprite::create("../Resources/my_image/topPipe.png");
    auto bottomPipe = Sprite::create("../Resources/my_image/bottomPipe.png");

    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setContactTestBitmask(true);
    //bottomPipe->setTag(2);

    topPipe->setPhysicsBody(topPipeBody);
    bottomPipe->setPhysicsBody(bottomPipeBody);


    /// <summary>
    /// cố định k dơi tự do
    /// </summary>
    /// <param name="layer"></param>
    topPipeBody->setDynamic(false);
    bottomPipeBody->setDynamic(false);


    auto random = CCRANDOM_0_1();
    if (random < LOWER_SCREEN_PIPE_THRESHOLD) {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if (random > UPPER_SCREEN_PIPE_THRESHOLD) {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height / 2);

    topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition));
    bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("../Resources/my_image/birdUp.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));

    layer->addChild(topPipe);
    layer->addChild(bottomPipe);

    auto topPipeAction = MoveBy::create(0.05 * visibleSize.width, Point(-visibleSize.width * 3, 0));
    auto bottomPipeAction = MoveBy::create(0.05 * visibleSize.width, Point(-visibleSize.width * 3, 0));


    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);


    auto pointPipe = Sprite::create();
    auto pointPipeBody = PhysicsBody::createBox(Size(1, Sprite::create("../Resources/my_image/birdUp.png")->getContentSize().height* PIPE_GAP));
    pointPipeBody->setDynamic(false);
    pointPipeBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    pointPipeBody->setContactTestBitmask(true);

    pointPipe->setPhysicsBody(pointPipeBody);
    pointPipe->setPosition(Point(topPipe->getPositionX() + topPipe->getContentSize().width/2, topPipe->getPositionY() - (Sprite::create("../Resources/my_image/birdUp.png")->getContentSize().height * PIPE_GAP) / 2 - topPipe->getContentSize().height / 2));
    
    layer->addChild(pointPipe);

    auto pointPipeAction = MoveBy::create(0.05 * visibleSize.width, Point(-visibleSize.width * 3, 0));
    pointPipe->runAction(pointPipeAction);
}

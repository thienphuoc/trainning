#include "GameScene.h"
#include "Definitation.h"

#include "AudioManager.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
float pauseTime = 0;
float countTime = 1;

GameScene* GameScene::createScene()
{
	auto scene = GameScene::create();

	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto splashScene = CSLoader::getInstance()->createNode("layer/game-scene.csb");
	this->addChild(splashScene);

	isPause = false;
	isMute = false;
	board = new Board(MAP_ROWS, MAP_COLUMNS);
	boardView = BoardView::createBoardView(this, this->board);

	auto timeBar = utils::findChild<ui::LoadingBar*>(this, "time-bar");
	time = timeBar->getPercent();
	timeCountdown(timeBar, time);

	auto refreshCountText = utils::findChild<ui::Text*>(this, "number-swap");
	refreshCountText->setString("Swap Count: " + to_string(refreshCount));

	// swap button
	auto swapButton = utils::findChild<ui::Button*>(this, "swap-map-node");
	swapButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();
		if (refreshCount > 0)
		{
			auto backgroundGame = utils::findChild<cocos2d::Sprite*>(this, "background-game");
			boardView->swapPokemon(backgroundGame);
			refreshCount--;
			refreshCountText->setString("Swap Count: " + to_string(refreshCount));
		}
		else {
			swapButton->setBright(false);
			swapButton->setOpacity(180);
		}
		});
	//end

	//mute button
	auto muteButton = utils::findChild<ui::Button*>(this, "mute-button");
	muteButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();
		auto iconMute = utils::findChild<ui::ImageView*>(this, "mute-icon");
		if (!isMute)
		{
			AudioManager::stopAllMusic();
			iconMute->loadTexture("../Resources/images/mute.png");
			isMute = true;

		}
		else {
			AudioManager::setEffectVolume(0);
			AudioManager::playAllMusic();
			iconMute->loadTexture("../Resources/images/loudspeaker.png");
			isMute = false;
			AudioManager::setEffectVolume(1.0f);
		}
		
		});
	//end

	//replay button
	auto rePlayButton = utils::findChild<ui::Button*>(this, "replay-button");
	rePlayButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();

		this->scheduleOnce(schedule_selector(GameScene::rePlayGame), 0);
		});
	//end


	//Pause button
	auto pauseButton = utils::findChild<ui::Button*>(this, "pause-button");
	pauseButton->addClickEventListener([=](Ref*) {
		AudioManager::playSelectSoundEffect();
		if (!isPause) {
			// pause
			AudioManager::stopBackgroundMusic();

			pauseButton->loadTextureNormal("../Resources/images/playOrange.png");
			rePlayButton->setTouchEnabled(false);
			swapButton->setTouchEnabled(false);
			muteButton->setTouchEnabled(false);

			pauseTime = timeBar->getPercent();
			countTime = -1;
			timeCountdown(timeBar, pauseTime);
			isPause = true;
		}
		else {
			// end pause
			if (!isMute)
			{
				AudioManager::playBackgroundMusic();
			}
	
			pauseButton->loadTextureNormal("../Resources/images/pauseOrange.png");

			rePlayButton->setTouchEnabled(true);
			swapButton->setTouchEnabled(true);
			muteButton->setTouchEnabled(true);

			pauseTime = 0;
			countTime = 1;
			timeCountdown(timeBar, time);
			isPause = false;
		}
		if (auto backgroundGame = utils::findChild<cocos2d::Sprite*>(this, "background-game"))
		{
			boardView->reloadPokemon(backgroundGame, isPause);
		}
		});
	//end

	this->scheduleUpdate();
	return true;
}

/// <summary>
/// count downt from m_time(float) whith PERCENT_LOSS_PER_SECOND loss per second
/// </summary>
/// <param name="loading">type LoadingBar*</param>
/// <param name="m_time">type float</param>
void GameScene::timeCountdown(ui::LoadingBar* loading, float m_time)
{
	time = m_time;
	this->schedule([=](float delta) {
		if (countTime != -1)
		{
			time -= PERCENT_LOSS_PER_SECOND;
		}
		loading->setPercent(time);
		if (time <= pauseTime) {
			this->unschedule("updateLoadingBar");
		}
		}, countTime, "updateLoadingBar");
	
}
// end timeCountdown

/// <summary>
/// create a new GameScene map to replay the game
/// </summary>
/// <param name="dt"></param>
void GameScene::rePlayGame(float dt)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

/// <summary>
/// create a new map to continue play the game with current score(when win)
/// </summary>
/// <param name="score"></param>
void GameScene::continueGame(int score)
{
	GameScene* scene = GameScene::createScene();
	scene->board->Score = score;

	auto scoreText = utils::findChild<ui::Text*>(scene, "score-text");
	scoreText->setString("Score: " + to_string(scene->board->Score));

	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

/// <summary>
/// call the function continueGame(board->Score) to cotinue play game when all pokemon in map is deleted
/// call the function rePlayGame(0); to re play the game when over time
/// </summary>
/// <param name="dt"></param>
void GameScene::update(float dt)
{
	if (board->countPokemonInMap() == 0)
	{
		continueGame(board->Score);
		this->unscheduleUpdate();
	}
	if (time == 0)
	{
		rePlayGame(0);
		this->unscheduleUpdate();
	}
}

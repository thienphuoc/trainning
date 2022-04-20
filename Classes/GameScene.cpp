#include "GameScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
int playerScore;
int tieScore;
int computerScore;
Scene* GameScene::createScene()
{
	playerScore = 0;
	tieScore = 0;
	computerScore = 0;
	auto scene = GameScene::create();

	auto layer = Layer::create();

	scene->addChild(layer);
	
	return scene;
}

/// <summary>
/// create a new game with old score
/// </summary>
/// <param name="playerSc">old score of player</param>
/// <param name="tieSc">old score of tie</param>
/// <param name="computerSc">old score of computer</param>
/// <returns></returns>
Scene* GameScene::continueScene(int playerSc, int tieSc, int computerSc)
{
	playerScore = playerSc;
	tieScore = tieSc;
	computerScore = computerSc;
	auto scene = GameScene::create();

	auto layer = Layer::create();

	scene->addChild(layer);
	
	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// load file csb and add it in the scene
	auto gameScene = CSLoader::getInstance()->createNode("csb/gamescene.csb");
	this->addChild(gameScene);
	// end

	showScore(this);

	//initialize the dèaul value of turn is X(player turn) and state of pause game button is true(game is playing)
	turn = X;
	pauseGameState = true;
	ai = new AI(X);
	// end

	// get the button pause to event handling click
	auto pauseButton = utils::findChild<ui::Button*>(this, "pause-button");
	//auto backgroundPauseButton = pauseButton->getChildByName<ui::ImageView*>("background-pause-button");
	pauseButton->setPressedActionEnabled(true);
	pauseButton->addClickEventListener([=](Ref*) {
		if (pauseGameState) {
			pauseButton->loadTextureNormal(CONTINUE_BUTTON);
			pauseGameState = false;
			setTouchDisabledAllButton(this);
		}
		else {
			pauseButton->loadTextureNormal(PAUSE_BUTTON);
			pauseGameState = true;
			setTouchEnabledAllButton(this);
		}
		});
	//end


	// loop the map game
	for (int i = 0; i < 9; i++) {
		//create some string with value is name of image, button in file csb and get them to handling
		__String* buttonName = __String::createWithFormat("map_button_%i", i + 1);
		__String* imageName = __String::createWithFormat("map_image_%i", i + 1);
		auto nodeButton = utils::findChild<ui::Button*>(this, buttonName->getCString());
		auto imageButton = utils::findChild<ui::ImageView*>(this, imageName->getCString());
		//end 

		//nodeButton->setPressedActionEnabled(false);

		//handling the click event when click button in map
		nodeButton->addClickEventListener([=](Ref*) {

			gridGame[i] = turn;	//set value of map is value of player turn(player or computer)
			ai->PlacePiece(&gridGame, this);// AI turn

			nodeButton->setBright(false); // set node status is disable

			// call the funtion check win and handling the action when it return true
			if (CheckWin(i)) {
				//playerWon = gridGame[i];	//set the player win
				addScreenOverlay(this, playerWon); //call the func addScreenOverlay 
				setTouchDisabledAllButton(this);	//call the func setTouchDisabledAllButton
				pauseButton->setTouchEnabled(false);	//set touch event of pause button is disable
			} 
			else if (countNullNodeOfMap(gridGame) == 0) {
				playerWon = DEFAULSE;	//set the player win
				addScreenOverlay(this, playerWon); //call the func addScreenOverlay 
				setTouchDisabledAllButton(this);	//call the func setTouchDisabledAllButton
				pauseButton->setTouchEnabled(false);	//set touch event of pause button is disable
			}
			//end

			
			//set the data of image and add it in the node button
			imageButton->setScale(0.35);
			imageButton->loadTexture(X_IMAGE_PATH);
			nodeButton->setTouchEnabled(false);	//set touch event of node button is disable
			//end
			});
	}

	this->scheduleUpdate();
	return true;
}

/// <summary>
/// check if the game is won
/// </summary>
/// <param name="index">points under consideration</param>
/// <returns></returns>
bool GameScene::CheckWin(int index)
{
	if (isWin(0, 1, 2) || isWin(3, 4, 5) || isWin(6, 7, 8) || isWin(0, 3, 6) || isWin(1, 4, 7) || isWin(2, 5, 8) || isWin(0, 4, 8) || isWin(2, 4, 6)) {
		return true;
	}
	return false;
}

/// <summary>
/// check if three equal points in a line of gridMap
/// </summary>
/// <param name="a">point 1</param>
/// <param name="b">point 2</param>
/// <param name="c">point 3</param>
/// <returns></returns>
bool GameScene::isWin(int a, int b, int c)
{
	int arr[3] = { a, b, c };
	if (gridGame[a] == gridGame[b] && gridGame[b] == gridGame[c] && gridGame[c] != DEFAULSE) {
		//this->runAction(Sequence::create(highlight(arr[0]), NULL));

		for (int i = 0; i < 3; i++)
		{
			__String* buttonName = __String::createWithFormat("map_button_%i", arr[i]+1);
			__String* imageName = __String::createWithFormat("map_image_%i", arr[i]+1);
			auto button = utils::findChild<ui::Button*>(this, buttonName->getCString());
			auto image = utils::findChild<ui::ImageView*>(this, imageName->getCString());
			auto image_Square = Sprite::create(ORANGE_QUARE_PATH);
			image_Square->setPosition(Vec2(image->getPositionX(), image->getPositionY()));
			image_Square->setScale((button->getContentSize().width) / image_Square->getContentSize().width, (button->getContentSize().height) / image_Square->getContentSize().height);
			image_Square->setOpacity(400);
			button->addChild(image_Square);
		}
		playerWon = gridGame[a];
		return true;
	}
	else {
		return false;
	}
}


/// <summary>
/// add a screen overlay in game scene to show result
/// </summary>
/// <param name="scene">scene is this</param>
void GameScene::addScreenOverlay(cocos2d::Scene* scene, m_Node player)
{
	//get background and add screen overlay
	auto gameBackground = utils::findChild<ui::ImageView*>(scene, "background-game");
	auto sceneBackground = utils::findChild<ui::ImageView*>(scene, "background");
	auto image_White_Background = Sprite::create(WHITE_BACKGROUND);

	image_White_Background->setPosition(Vec2(gameBackground->getPositionX(), gameBackground->getPositionY()));
	image_White_Background->setOpacity(600);
	sceneBackground->addChild(image_White_Background);
	//end
	//add text
	auto resultGame = ui::Text::create();
	resultGame->setPosition(Vec2(scene->getContentSize().width * 0.5, scene->getContentSize().height * 0.5));
	//resultGame->setScale(5);
	resultGame->setFontSize(70);
	if (player == X) {
		playerScore++;
		resultGame->setString("You Win!");
		resultGame->setColor(Color3B(255, 51, 2));
	}
	else if (player == O) {
		computerScore++;
		resultGame->setString("You Lose!");
		resultGame->setColor(Color3B(0, 0, 0));
	}
	else {
		tieScore++;
		resultGame->setString("Tie!");
		resultGame->setColor(Color3B(0, 0, 255));
	}

	sceneBackground->addChild(resultGame);

	// end
	


	//add retry node and return home node
	auto retryNode = ui::Button::create();
	auto returnHomeNode = ui::Button::create();

	retryNode->loadTextureNormal(REPLAY_BUTTON);
	retryNode->setPosition(Vec2(scene->getContentSize().width * 0.3, scene->getContentSize().height * 0.3));
	retryNode->setScale(0.3);
	retryNode->addClickEventListener([=](Ref*) {
		ContinueGame(playerScore, tieScore, computerScore);
		});
	sceneBackground->addChild(retryNode);

	returnHomeNode->loadTextureNormal(RETURN_HOME_BUTTON);
	returnHomeNode->setPosition(Vec2(scene->getContentSize().width * 0.7, scene->getContentSize().height * 0.3));
	returnHomeNode->setScale(0.3);
	returnHomeNode->addClickEventListener([=](Ref*) {
		this->scheduleOnce(schedule_selector(GameScene::returnMainMenu), 0);
		});
	sceneBackground->addChild(returnHomeNode);
	//end

	//CCLOG("player Score: %i", playerScore);
	//CCLOG("computer Score: %i", computerScore);
	//CCLOG("tie Score: %i", tieScore);

}


void GameScene::highlight(int index)
{
	__String* buttonName = __String::createWithFormat("map_button_%i", index + 1);
	__String* imageName = __String::createWithFormat("map_image_%i", index + 1);
	auto button = utils::findChild<ui::Button*>(this, buttonName->getCString());
	auto image = utils::findChild<ui::ImageView*>(this, imageName->getCString());
	auto image_Square = Sprite::create(ORANGE_QUARE_PATH);
	image_Square->setPosition(Vec2(image->getPositionX(), image->getPositionY()));
	image_Square->setScale((button->getContentSize().width) / image_Square->getContentSize().width, (button->getContentSize().height) / image_Square->getContentSize().height);
	image_Square->setOpacity(400);
	button->addChild(image_Square);
}

/// <summary>
/// return main menu
/// </summary>
/// <param name="dt"></param>
void GameScene::returnMainMenu(float dt)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

/// <summary>
/// retry the game with old score
/// </summary>
/// <param name="playerSc">old score of player</param>
/// <param name="tieSc">old score of tie</param>
/// <param name="computerSc">old score of computer</param>
void GameScene::ContinueGame(int playerSc, int tieSc, int computerSc)
{
	auto scene = GameScene::continueScene(playerSc, tieSc, computerSc);
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


/// <summary>
/// set event touch is enable for all button
/// </summary>
/// <param name="scene"></param>
void GameScene::setTouchEnabledAllButton(cocos2d::Scene* scene)
{
	for (int i = 0; i < 9; i++)
	{
		__String* newbuttonName = __String::createWithFormat("map_button_%i", i + 1);
		auto newNodeButton = utils::findChild<ui::Button*>(scene, newbuttonName->getCString());
		if (gridGame[i] == DEFAULSE) {
			newNodeButton->setTouchEnabled(true);
		}

	}
}

/// <summary>
/// Show the score in game
/// </summary>
/// <param name="scene"></param>
void GameScene::showScore(cocos2d::Scene* scene)
{
	//draw score 
	auto playerScoreText = utils::findChild<ui::Text*>(scene, "player-score");
	__String* playerScoreString = __String::createWithFormat("Your Score: %i", playerScore);
	playerScoreText->setString(playerScoreString->getCString());
	 
	auto tieScoreText = utils::findChild<ui::Text*>(scene, "tie-score");
	__String* tieScoreString = __String::createWithFormat("Tie: %i", tieScore);
	tieScoreText->setString(tieScoreString->getCString());

	auto computerScoreText = utils::findChild<ui::Text*>(scene, "computer-score");
	__String* computerScoreString = __String::createWithFormat("Computer Score: %i", computerScore);
	computerScoreText->setString(computerScoreString->getCString());
	//end
}
/// <summary>
/// set event touch is disable for all button
/// </summary>
/// <param name="scene"></param>
void GameScene::setTouchDisabledAllButton(cocos2d::Scene* scene)
{
	for (int i = 0; i < 9; i++)
	{
		__String* newbuttonName = __String::createWithFormat("map_button_%i", i + 1);
		auto newNodeButton = utils::findChild<ui::Button*>(scene, newbuttonName->getCString());
		newNodeButton->setTouchEnabled(false);
	}
}

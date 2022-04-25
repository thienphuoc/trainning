#pragma once
#include "cocos2d.h"
#include "Definitation.h"
#include "Board.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class BoardView : public Layer
{
	
public:
	// create a BoardView to draw pokemon in map
	static BoardView* createBoardView(Scene *scene,Board* board);
	// end

	//create map game with Sprite and draw pokemon in it
	void showBoard();
	//end

	cocos2d::Sprite* background_game;
	pair<int, int> buttonIsClicked;

	// remove pokemon at row = row, column = column
	void removePokemon(int row, int column, cocos2d::Sprite* sprite);
	//end

	// spawn all pokemon in map
	void spawnPokemon(cocos2d::Sprite* sprite);
	//end

	// reload map and add some attributes in the pokemon button when the game have change (pause, delete pokemon)
	void reloadPokemon(cocos2d::Sprite* sprite, bool input_ispause);
	// end

	// swap pokemon locations in the map
	void swapPokemon(cocos2d::Sprite* sprite);
	// end

	// connect two pokemon in map
	void connectPokemons(int x, int y, int _x, int _y, cocos2d::Sprite* sprite);
	// connect two pokemon in map

	// get connect effect of two pokemon
	FiniteTimeAction* getConnectEffect(int x, int y, int _x, int _y);
	// end

	// return position of a point in map pokemon with origin is GameScene
	Vec2 positionOf(int row, int column);
	// end

	// add event click in all button pokemon
	void addEventClick(cocos2d::Sprite* sprite);
	// end

	// find path of two pokemon
	vector<pair<int, int>> findPath(int _x, int _y, int x, int y);
	// end

	CREATE_FUNC(BoardView);
private:

};



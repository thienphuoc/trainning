#pragma once
#include <vector>
#include <cocos2d.h>
#include <Definitation.h>
#include <string>

using namespace std;
class Board
{

public:
	int Score = 0;
	int map_rows, map_columns;
	vector<vector<int>> mapGameWithValueIsKeyOfPokemon;
	vector<pair<string, int>> urlOfPokemonAndQuantity;
	Board(int map_rows, int map_columns);
	int countAllPokemon();

	int countQuatityOfOnePokemonInMap(int kindPokemon);
	void setDataForPokemonQuantity();

	int getMapRows();
	int getMapColumns();
	void addPokemon(int x, int y, int type);
	int getPokemon(int x, int y);
	void removePokemon(int x, int y);
	int countPokemonInMap();


	void printMapGame();
	void printVector();
};
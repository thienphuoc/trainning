#include "Board.h"
#include <map>

Board::Board(int map_rows, int map_columns) :
	map_rows(map_rows),
	map_columns(map_columns),
	mapGameWithValueIsKeyOfPokemon(std::vector<std::vector<int>>(map_rows, std::vector<int>(map_columns, -1)))
{
	srand(time(NULL));
	setDataForPokemonQuantity();
	for (int i = 0; i < map_rows; ++i) {
		for (int j = 0; j < map_columns; ++j) {
			int type;
			do {
				type = rand() % QUANTITY_POKEMON;
			} while (countQuatityOfOnePokemonInMap(type+1) >= urlOfPokemonAndQuantity[type].second);

			addPokemon(i, j, type + 1);
		}
	}
}

int Board::countAllPokemon()
{
	int countPokemon = 0;
	for (int i = 0; i < map_rows; ++i) {
		for (int j = 0; j < map_columns; ++j) {
			if (mapGameWithValueIsKeyOfPokemon[i][j] != -1)
			{
				countPokemon++;
			}
		}
	}
	return countPokemon;
}

int Board::countQuatityOfOnePokemonInMap(int kindPokemon)
{
	int countPokemon = 0;
	for (int i = 0; i < map_rows; ++i) {
		for (int j = 0; j < map_columns; ++j) {
			if (mapGameWithValueIsKeyOfPokemon[i][j] == kindPokemon) {
				countPokemon++;
			}
		}
	}
	return countPokemon;
}

void Board::setDataForPokemonQuantity()
{
	for (int i = 0; i < QUANTITY_POKEMON; i++) {
		pair<string, int> node;
		node.first ="../Resources/myPokemons/" + to_string(i + 1) + ".png";
		node.second = MAX_QUANTITY_POKEMON_IN_MAP;
		urlOfPokemonAndQuantity.push_back(node);
	}
}

int Board::getMapRows()
{
	return map_rows;
}

int Board::getMapColumns()
{
	return map_columns;
}

void Board::addPokemon(int x, int y, int type)
{
	mapGameWithValueIsKeyOfPokemon[x][y] = type;
}

int Board::getPokemon(int x, int y)
{
	return mapGameWithValueIsKeyOfPokemon[x][y];
}

void Board::removePokemon(int x, int y)
{
	urlOfPokemonAndQuantity[mapGameWithValueIsKeyOfPokemon[x][y]-1].second--;
	mapGameWithValueIsKeyOfPokemon[x][y] = -1;
}

int Board::countPokemonInMap()
{
	int countPokemon = 0;
	for (int i = 0; i < map_rows; i++)
	{
		for (int j = 0; j < map_columns; j++)
		{
			if (mapGameWithValueIsKeyOfPokemon[i][j] != -1)
			{
				countPokemon++;
			}
		}
	}
	return countPokemon;
}



















void Board::printMapGame()
{
	for (int i = 0; i < mapGameWithValueIsKeyOfPokemon.size(); i++)
	{
		for (int j = 0; j < mapGameWithValueIsKeyOfPokemon[i].size(); j++)
		{
			CCLOG("abc: %i",mapGameWithValueIsKeyOfPokemon[i][j]);
		}
	}
}

void Board::printVector()
{
	for (int i = 0; i< 16; i++)
	{
		CCLOG("Abc: %i   %i", urlOfPokemonAndQuantity[i].first, urlOfPokemonAndQuantity[i].second);
	}
}



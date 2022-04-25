#include "BoardView.h"
#include "AudioManager.h"

bool isClicked;
Scene* scene;
Board* board;

/// <summary>
/// create a BoardView to draw pokemon in map
/// </summary>
/// <param name="input_scene">Scene: GameScene</param>
/// <param name="input_board">Board</param>
/// <returns></returns>
BoardView* BoardView::createBoardView(Scene* input_scene, Board* input_board)
{
	auto layer = BoardView::create();
	scene = input_scene;
	board = input_board;
	layer->showBoard();
	isClicked = false;
	return layer;
}
// end

/// <summary>
/// create map game with Sprite and draw pokemon in it
/// </summary>
void BoardView::showBoard()
{
	background_game = Sprite::create("../Resources/images/white-background.png");
	background_game->setName("background-game");
	background_game->setPosition(scene->getPositionX() + scene->getContentSize().width / 2, scene->getPositionY() + scene->getContentSize().height / 2);
	background_game->setContentSize(Size(WIDTH_OF_MAP_GAME, HEIGHT_OF_MAP_GAME));
	background_game->setOpacity(200);
	scene->addChild(background_game);
	spawnPokemon(background_game);
}
//end

/// <summary>
/// remove pokemon at row = row, column = column
/// </summary>
/// <param name="row">row of pokemon</param>
/// <param name="column">column of pokemon</param>
/// <param name="sprite">Sprite: it is background game</param>
void BoardView::removePokemon(int row, int column, cocos2d::Sprite* sprite)
{

	if (board->mapGameWithValueIsKeyOfPokemon[row][column] != -1)
	{
		board->Score += 5;
		board->removePokemon(row, column);
		reloadPokemon(sprite, false);
	}
	
}
//end 

/// <summary>
/// spawn all pokemon in map
/// </summary>
/// <param name="sprite">Sprite: it is background game</param>
void BoardView::spawnPokemon(cocos2d::Sprite* sprite)
{
	for (int x = 0; x < MAP_ROWS; x++)
	{
		for (int y = 0; y < MAP_COLUMNS; y++)
		{
			auto index = board->mapGameWithValueIsKeyOfPokemon[x][y];
			auto pikachu = ui::Button::create();
			pikachu->setName("button-" + to_string(x) + "-" + to_string(y));
			pikachu->setAnchorPoint(Vec2(0.5, 0.5));
			if (index != -1) {	
				pikachu->loadTextureNormal(board->urlOfPokemonAndQuantity[index - 1].first);
			}
			else {
				pikachu->loadTextureNormal(NO_BACKGROUND_URL);
				pikachu->setTouchEnabled(false);
			}

			pikachu->setScale(NODE_SIZE_WIDTH / pikachu->getContentSize().width, NODE_SIZE_HEIGHT / pikachu->getContentSize().height);
			pikachu->setPosition(Vec2(NODE_SIZE_WIDTH * 0.5 + y * NODE_SIZE_WIDTH, HEIGHT_OF_MAP_GAME - NODE_SIZE_HEIGHT * 0.5 - x * NODE_SIZE_HEIGHT));
			sprite->addChild(pikachu);
		}
	}
	addEventClick(sprite);
}
//end


/// <summary>
/// reload map and add some attributes in the pokemon button when the game have change (pause, delete pokemon)
/// </summary>
/// <param name="sprite">Sprite: background game</param>
/// <param name="input_ispause">bool: status of pause game</param>
void BoardView::reloadPokemon(cocos2d::Sprite* sprite, bool input_ispause)
{
	for (int x = 0; x < MAP_ROWS; x++)
	{
		for (int y = 0; y < MAP_COLUMNS; y++)
		{
			auto index = board->mapGameWithValueIsKeyOfPokemon[x][y];
			auto pikachu = utils::findChild<ui::Button*>(sprite, "button-" + to_string(x) + "-" + to_string(y));
			if (index == -1) {
				pikachu->loadTextureNormal(NO_BACKGROUND_URL);
				pikachu->setTouchEnabled(false);
			}
			else if (index != -1) {
				pikachu->loadTextureNormal(board->urlOfPokemonAndQuantity[index - 1].first);
			}
			if (input_ispause) {
				pikachu->setTouchEnabled(false);
			}
			else if (index != -1) {
				pikachu->setTouchEnabled(true);
			}
			
			pikachu->setScale(NODE_SIZE_WIDTH / pikachu->getContentSize().width, NODE_SIZE_HEIGHT / pikachu->getContentSize().height);
		}
	}
}
//end

/// <summary>
/// swap pokemon locations in the map
/// </summary>
/// <param name="sprite">Sprite: background game</param>
void BoardView::swapPokemon(cocos2d::Sprite* sprite)
{
	int count = 0;
	for (int a = 0; a < MAP_ROWS; a++)
	{
		for (int b = 0; b < MAP_COLUMNS; b++)
		{
			if (board->mapGameWithValueIsKeyOfPokemon[a][b] != -1)
			{
				board->mapGameWithValueIsKeyOfPokemon[a][b] = 99;
				count++;
			}
		}
	}
	srand(time(NULL));
	for (int i = 0; i < MAP_ROWS; ++i) {
		for (int j = 0; j < MAP_COLUMNS; j ++) {
			int type;
			do {
				type = rand() % QUANTITY_POKEMON;
			} while (board->countQuatityOfOnePokemonInMap(type + 1) >= board->urlOfPokemonAndQuantity[type].second && count > 0);
			if (board->mapGameWithValueIsKeyOfPokemon[i][j] == 99) {
				board->addPokemon(i, j, type + 1);
				count--;
			}
		}
	}
	reloadPokemon(sprite, false);
}
//end


/// <summary>
/// connect two pokemon in map
/// </summary>
/// <param name="x">int: coordinates of first point in map pokemon</param>
/// <param name="y">int: coordinates of first point in map pokemon</param>
/// <param name="_x">int: coordinates of second point in map pokemon</param>
/// <param name="_y">int: coordinates of second point in map pokemon</param>
/// <param name="sprite">Sprite: mapgame</param>
void BoardView::connectPokemons(int x, int y, int _x, int _y, cocos2d::Sprite* sprite)
{
	auto connectEffect = getConnectEffect(x, y, _x, _y);

	//pikachu->setName("button-" + to_string(x) + "-" + to_string(y));
	auto pikachu1 = utils::findChild<ui::Button*>(scene, "button-" + to_string(x) + "-" + to_string(y));
	auto pikachu2 = utils::findChild<ui::Button*>(scene, "button-" + to_string(_x) + "-" + to_string(_y));
	auto pokemonFade1 = TargetedAction::create(pikachu1, FadeOut::create(0.5));
	auto pokemonFade2 = TargetedAction::create(pikachu2, FadeOut::create(0.5));
	auto effectSpawn = Spawn::create(pokemonFade1, pokemonFade2, nullptr);


	// xoa node
	auto removePokemon1 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, x, y, sprite));
	auto removePokemon2 = CallFunc::create(CC_CALLBACK_0(BoardView::removePokemon, this, _x, _y, sprite));
	auto removePokemonSpawn = Spawn::create(removePokemon1, removePokemon2, nullptr);
	
	// run
	auto sequence = Sequence::create(connectEffect, effectSpawn, removePokemonSpawn, nullptr);
	scene->runAction(sequence);
}

/// <summary>
/// get connect effect of two pokemon
/// </summary>
/// <param name="x">int: coordinates of first point in map pokemon</param>
/// <param name="y">int: coordinates of first point in map pokemon</param>
/// <param name="_x">int: coordinates of second point in map pokemon</param>
/// <param name="_y">int: coordinates of second point in map pokemon</param>
/// <returns></returns>
FiniteTimeAction* BoardView::getConnectEffect(int x, int y, int _x, int _y)
{
	auto path = findPath(x, y, _x, _y);
	std::vector<Vec2> _path;
	for (auto p : path) {
		_path.push_back(positionOf(p.first, p.second));
	}

	auto emitter = ParticleSystemQuad::create(PATH_PLIST_URL);
	scene->addChild(emitter);
	float duration = 0.3f;
	emitter->setDuration(duration);
	emitter->setPosition(_path[0]);
	Vector<FiniteTimeAction*> actions;
	for (int i = 1; i < _path.size(); ++i) {
		actions.pushBack((FiniteTimeAction*)MoveTo::create(duration / (_path.size() - 1), _path[i]));
	}
	return TargetedAction::create(emitter, Sequence::create(actions));
}
//end

/// <summary>
/// return position of a point in map pokemon with origin is GameScene
/// </summary>
/// <param name="row"></param>
/// <param name="column"></param>
/// <returns></returns>
Vec2 BoardView::positionOf(int row, int column)
{
	return Vec2((scene->getContentSize().width - WIDTH_OF_MAP_GAME)/2 + NODE_SIZE_WIDTH / 2 + column* NODE_SIZE_WIDTH, scene->getContentSize().height - (scene->getContentSize().height - HEIGHT_OF_MAP_GAME)/2 - NODE_SIZE_HEIGHT / 2 - row * NODE_SIZE_HEIGHT);
}



/// <summary>
/// add event click in all button pokemon
/// </summary>
/// <param name="sprite">Sprite: mapgame</param>
void BoardView::addEventClick(cocos2d::Sprite* sprite)
{
	for (int x = 0; x < MAP_ROWS; x++)
	{
		for (int y = 0; y < MAP_COLUMNS; y++)
		{
			auto pikachu = utils::findChild<ui::Button*>(sprite, "button-" + to_string(x) + "-" + to_string(y));
			pikachu->addClickEventListener([=](Ref*) {
				if (board->mapGameWithValueIsKeyOfPokemon[x][y] != -1)
				{
					AudioManager::playSelectSoundEffect();
					if (!isClicked)
					{
						pikachu->setOpacity(170);
						buttonIsClicked = make_pair(x, y);
						isClicked = true;
					}
					else
					{
						if (board->mapGameWithValueIsKeyOfPokemon[buttonIsClicked.first][buttonIsClicked.second] == board->mapGameWithValueIsKeyOfPokemon[x][y])
						{
							auto path = findPath(buttonIsClicked.first, buttonIsClicked.second, x, y);
							if (path.size() >= 2 && path.size() <= 4) {
								AudioManager::playRemovePokemonSoundEffect();

								connectPokemons(buttonIsClicked.first, buttonIsClicked.second, x, y, sprite);
								buttonIsClicked = make_pair(-1, -1);
								isClicked = false;

								auto scoreText = utils::findChild<ui::Text*>(scene, "score-text");
								scoreText->setString("Score: " + to_string(board->Score));

							}
							else {
								AudioManager::playSelectIncorrectPokemonSoundEffect();


								pikachu->setOpacity(255);
								auto pikachuClicked = utils::findChild<ui::Button*>(sprite, "button-" + to_string(buttonIsClicked.first) + "-" + to_string(buttonIsClicked.second));
								pikachuClicked->setOpacity(255);
								buttonIsClicked = make_pair(-1, -1);
								isClicked = false;
							}
						}
						else {
							AudioManager::playSelectIncorrectPokemonSoundEffect();

							auto pikachuClicked = utils::findChild<ui::Button*>(sprite, "button-" + to_string(buttonIsClicked.first) + "-" + to_string(buttonIsClicked.second));
							pikachuClicked->setOpacity(255);
							buttonIsClicked = make_pair(-1, -1);
							isClicked = false;
						}

					}
				}

				});
			
		}
	}
}
//end

/// <summary>
/// find path of two pokemon
/// </summary>
/// <param name="_x">int: coordinates of second point in map pokemon</param>
/// <param name="_y">int: coordinates of second point in map pokemon</param>
/// <param name="x">int: coordinates of first point in map pokemon</param>
/// <param name="y">int: coordinates of first point in map pokemon</param>
/// <returns></returns>
vector<pair<int, int>> BoardView::findPath(int _x, int _y, int x, int y)
{
	std::vector<std::vector<int>> e(MAP_ROWS + 2, std::vector<int>(MAP_COLUMNS + 2, 0));
	for (int i = 0; i < MAP_ROWS; ++i)
	{
		for (int j = 0; j < MAP_COLUMNS; ++j)
		{
			e[i + 1][j + 1] = board->mapGameWithValueIsKeyOfPokemon[i][j] != -1;
		}
	}
	std::pair<int, int> s = { _x + 1, _y + 1 };
	std::pair<int, int> t = { x + 1, y + 1 };

	//BFS
	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };
	std::deque<std::pair<int, int>> q;
	std::vector<std::vector<std::pair<int, int>>> trace(e.size(), std::vector<std::pair<int, int>>(e[0].size(), std::make_pair(-1, -1)));
	q.push_back(t);
	trace[t.first][t.second] = std::make_pair(-2, -2);
	e[s.first][s.second] = 0;
	e[t.first][t.second] = 0;
	while (!q.empty()) {
		auto u = q.front();
		q.pop_front();
		if (u == s) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < e.size() && y >= 0 && y < e[0].size() && e[x][y] == 0) {
				if (trace[x][y].first == -1) {
					trace[x][y] = u;
					q.push_back({ x, y });
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

	//trace back
	std::vector<std::pair<int, int>> res;
	if (trace[s.first][s.second].first != -1) {
		while (s.first != -2) {
			res.push_back({ s.first - 1, s.second - 1 });
			s = trace[s.first][s.second];
		}
	}
	return res;
}
//end
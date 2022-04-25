#pragma once

#define SPLASH_SCENE_SHOW_TIME 0.0
#define TRANSITION_TIME 0.6

#define PERCENT_LOSS_PER_SECOND 1

#define QUANTITY_POKEMON 24
#define MAX_QUANTITY_POKEMON_IN_MAP (int)4

#define WIDTH_OF_MAP_GAME 672
#define HEIGHT_OF_MAP_GAME 448
#define NODE_SIZE_WIDTH 56
#define NODE_SIZE_HEIGHT 56

#define MAP_ROWS HEIGHT_OF_MAP_GAME/NODE_SIZE_HEIGHT
#define MAP_COLUMNS WIDTH_OF_MAP_GAME/NODE_SIZE_WIDTH

#define NO_BACKGROUND_URL "../Resources/images/no-background.png"
#define PATH_PLIST_URL "../Resources/path.plist"

#define URL_CORRECT_MP3 "../Resources/audios/dung.mp3"
#define URL_BACKGROUND_MUSIC_MP3 "../Resources/audios/nhacnen.mp3"
#define URL_INCORRECT_MP3 "../Resources/audios/sai.mp3"
#define URL_CLICK_MP3 "../Resources/audios/click.mp3"


#define REFRESH_COUNT 10
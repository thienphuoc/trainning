#pragma once
#define SPLASH_SCENE_SHOW_TIME 2.0
#define SPLASH_TRANSITION_TIME 0.6

#define X_IMAGE_PATH "../Resources/images/Cancel.png"
#define O_IMAGE_PATH "../Resources/images/alphabet.png"
#define ORANGE_QUARE_PATH "../Resources/images/squareOrange.png"
#define WHITE_BACKGROUND "../Resources/images/white-background.png"
#define PAUSE_BUTTON "../Resources/images/pause-button.png"
#define CONTINUE_BUTTON "../Resources/images/play.png"
#define REPLAY_BUTTON "../Resources/images/loading.png"
#define RETURN_HOME_BUTTON "../Resources/images/home.png"

enum m_Node {
    DEFAULSE,
    X,
    O
};

#define X_PIECE X
#define O_PIECE O
#define EMPTY_PIECE DEFAULSE

#define PLAYER_PIECE X_PIECE
#define AI_PIECE O_PIECE


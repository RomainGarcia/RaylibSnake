#ifndef SPACEINVADERSRAYLIB_CONSTANTS_H
#define SPACEINVADERSRAYLIB_CONSTANTS_H

#include <raylib.h>

namespace RE {
    // Cells
    const int CELL_SIZE = 30;
    const int CELL_COUNT = 25;
    const int GRID_OFFSET = 75;

    // Window
    static const int SCREEN_WIDTH = CELL_SIZE * CELL_COUNT + GRID_OFFSET * 2;
    static const int SCREEN_HEIGHT = CELL_SIZE * CELL_COUNT + GRID_OFFSET * 2;
    static const char* WINDOW_TITLE = "C++ Raylib Snake";
    static const int TARGET_FPS = 60;

    // Colors
    static const Color GAME_COLOR_GREEN = {173, 204, 96, 255};
    static const Color GAME_COLOR_DARK_GREEN = {43, 51, 24, 255};
    static const Color GAME_COLOR_BACKGROUND = GAME_COLOR_GREEN;

    // Game
    const float GLOBAL_GAME_SPEED = 1.0f;
    const float MOVEMENT_INTERVAL = 0.2f;


    // Directions
    const Vector2 DIRECTION_UP = {0, -1};
    const Vector2 DIRECTION_DOWN = {0, 1};
    const Vector2 DIRECTION_LEFT = {-1, 0};
    const Vector2 DIRECTION_RIGHT = {1, 0};

}

#endif

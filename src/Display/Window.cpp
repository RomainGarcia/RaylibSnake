#include "Window.h"
#include "Constants/Constants.h"

void RE::Window::Init() {
    InitWindow(RE::SCREEN_WIDTH, RE::SCREEN_HEIGHT, RE::WINDOW_TITLE);
    SetTargetFPS(RE::TARGET_FPS);
}

void RE::Window::Close() {
    CloseWindow();
}

void RE::Window::BeginDrawing() {
    ::BeginDrawing();
    ClearBackground(RE::GAME_COLOR_BACKGROUND);
}

void RE::Window::EndDrawing() {
    ::EndDrawing();
}

float RE::Window::GetVerticalCenter(int offset) {
    return static_cast<float>(GetScreenHeight() + offset) / 2;
}

float RE::Window::GetHorizontalCenter(int offset) {
    return static_cast<float>(GetScreenWidth() + offset) / 2;
}



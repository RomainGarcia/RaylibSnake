#include "Gui.h"

#include "Constants/Constants.h"

#include <raylib.h>
#include <utility>

std::weak_ptr<Font> RE::Gui::m_DefaultFont;

void RE::Gui::Init(std::weak_ptr<Font> defaultFont) {
    m_DefaultFont = std::move(defaultFont);
}

void RE::Gui::Update() {

}

void RE::Gui::Draw(int score, bool isRunning) {
    if (m_DefaultFont.expired()) {
        TraceLog(LOG_ERROR, "Gui::Draw: Default font is not set");
        return;
    }

    DrawRectangleLinesEx({
            static_cast<float>(GRID_OFFSET - 5),
            static_cast<float>(GRID_OFFSET - 5),
            static_cast<float>(CELL_SIZE * CELL_COUNT + 10),
            static_cast<float>(CELL_SIZE * CELL_COUNT + 10)
        },
        5,
        GAME_COLOR_DARK_GREEN
    );

    DrawFPS(10, 10);
    DrawText("C++ Raylib Snake", GRID_OFFSET - 5, 20, 40,GAME_COLOR_DARK_GREEN);

    auto text = isRunning ? TextFormat("Score: %i", score) : "Press WASD to restart";
    DrawText(text, GRID_OFFSET - 5, GRID_OFFSET + CELL_SIZE * CELL_COUNT + 10, 40,GAME_COLOR_DARK_GREEN);

}


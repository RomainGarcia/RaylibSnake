#include "Food.h"

#include "Constants/Constants.h"

void RE::Food::Update(float deltatime) {
    GameObject::Update(deltatime);
}

void RE::Food::Draw() {
    if (!m_Texture.expired()) {
        DrawTexture(
            *m_Texture.lock(),
            static_cast<int>(m_Position.x * CELL_SIZE + GRID_OFFSET),
            static_cast<int>(m_Position.y * CELL_SIZE + GRID_OFFSET),
            WHITE
        );
    }
}


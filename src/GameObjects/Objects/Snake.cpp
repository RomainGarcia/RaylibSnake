#include "Snake.h"

#include <raymath.h>
#include <algorithm>
#include <unordered_set>
#include <vector>

void RE::Snake::Reset() {
    m_Body = {{6,9}, {5, 9}, {4, 9}};
    m_CurrentDirection = DIRECTION_RIGHT;
    m_NextDirection = DIRECTION_RIGHT;
    m_LastMoveTime = 0.0;
    m_AddSegment = false;
}

void RE::Snake::Update(float deltatime) {
    GameObject::Update(deltatime);

    UpdateDirection();
    Move();
}

void RE::Snake::Draw() {
    for (auto & cell : m_Body) {
        DrawRectangleRounded({
                static_cast<float>(cell.x * CELL_SIZE + GRID_OFFSET),
                static_cast<float>(cell.y * CELL_SIZE + GRID_OFFSET),
                static_cast<float>(CELL_SIZE),
                static_cast<float>(CELL_SIZE)
            },
            0.5f,
            6,
            GAME_COLOR_DARK_GREEN
        );
    }
}

void RE::Snake::Move() {
    double currentTime = GetTime();
    if (currentTime - m_LastMoveTime < MOVEMENT_INTERVAL) {
        return;
    }
    m_LastMoveTime = currentTime;

    // Add a new segment at the front of the snake at the direction of movement
    m_Body.emplace_front(Vector2Add(m_Body[0], m_NextDirection));
    m_CurrentDirection = m_NextDirection;

    if (m_AddSegment) {
        m_AddSegment = false;
        return;
    }

    // Remove the last segment of the snake, only if the snake is not growing
    m_Body.pop_back();
}

void RE::Snake::UpdateDirection() {
    if (IsKeyPressed(KEY_W) && m_CurrentDirection != DIRECTION_DOWN) {
        m_NextDirection = DIRECTION_UP;
    }
    if (IsKeyPressed(KEY_S) && m_CurrentDirection != DIRECTION_UP) {
        m_NextDirection = DIRECTION_DOWN;
    }
    if (IsKeyPressed(KEY_A) && m_CurrentDirection != DIRECTION_RIGHT) {
        m_NextDirection = DIRECTION_LEFT;
    }
    if (IsKeyPressed(KEY_D) && m_CurrentDirection != DIRECTION_LEFT) {
        m_NextDirection = DIRECTION_RIGHT;
    }

}

bool RE::Snake::IsElementInBody(Vector2 position, bool ignoreHead) const {
    auto first = ignoreHead ? m_Body.begin() + 1 : m_Body.begin();
    return std::any_of(first, m_Body.end(), [position](const Vector2& bodyPart) {
        return Vector2Equals(bodyPart, position);
    });
}

Vector2 RE::Snake::GetRandomFreePosition() const {
    std::unordered_set<Vector2, Vector2Hash> occupied(m_Body.begin(), m_Body.end());
    std::vector<Vector2> freePositions;
    freePositions.reserve(CELL_COUNT * CELL_COUNT - occupied.size());
    for (int x = 0; x < CELL_COUNT; ++x) {
        for (int y = 0; y < CELL_COUNT; ++y) {
            Vector2 position = {static_cast<float>(x), static_cast<float>(y)};
            if (occupied.find(position) == occupied.end()) {
                freePositions.push_back(position);
            }
        }
    }

    if (freePositions.empty()) {
        return {-1, -1};
    }

    return freePositions[GetRandomValue(0, static_cast<int>(freePositions.size()) - 1)];
}



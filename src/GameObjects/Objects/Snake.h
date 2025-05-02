#ifndef RAYLIBSNAKE_SNAKE_H
#define RAYLIBSNAKE_SNAKE_H

#include "GameObjects/GameObject.h"
#include "Constants/Constants.h"

#include <raymath.h>
#include <deque>

namespace RE {
    struct Vector2Hash {
        std::size_t operator()(const Vector2& v) const {
            return std::hash<int>()(static_cast<int>(v.x)) ^ (std::hash<int>()(static_cast<int>(v.y)) << 1);
        }
    };

    class Snake: public GameObject {
    public:
        using GameObject::GameObject;
        void Reset();
        void Update(float deltatime) override;
        void Draw() override;
        Vector2 GetPosition() const override { return m_Body[0]; }
        bool IsElementInBody(Vector2 position, bool ignoreHead = false) const;
        void AddSegment() { m_AddSegment = true; }
        Vector2 GetRandomFreePosition() const;
    private:
        void Move();
        void UpdateDirection();

        std::deque<Vector2> m_Body = {{6,9}, {5, 9}, {4, 9}};
        Vector2 m_CurrentDirection = DIRECTION_RIGHT;
        Vector2 m_NextDirection = DIRECTION_RIGHT;
        double m_LastMoveTime = 0.0;
        bool m_AddSegment = false;
    };

} // RE

#endif

#ifndef RAYLIBBOILERPLATE_GAME_H
#define RAYLIBBOILERPLATE_GAME_H

#include "Display/Gui.h"
#include "GameObjects/Objects/Food.h"
#include "GameObjects/Objects/Snake.h"

namespace RE {

    class Game {
    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Draw();
    private:
        void CheckCollisionWithFood();
        void CheckCollisionWithEdges();
        void CheckCollisionWithTail();
        void GameOver();
        std::shared_ptr<Food> m_Food;
        std::shared_ptr<Snake> m_Snake;
        bool m_IsRunning = true;
        int m_Score = 0;
    };

} // RE

#endif

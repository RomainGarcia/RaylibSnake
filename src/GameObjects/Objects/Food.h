#ifndef RAYLIBSNAKE_FOOD_H
#define RAYLIBSNAKE_FOOD_H

#include "GameObjects/GameObject.h"

namespace RE {

    class Food: public GameObject {
    public:
        using GameObject::GameObject;
        void Update(float deltatime) override;
        void Draw() override;
    };

} // RE

#endif

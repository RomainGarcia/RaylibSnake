#ifndef SPACEINVADERSRAYLIB_GAMEOBJECT_H
#define SPACEINVADERSRAYLIB_GAMEOBJECT_H

#include "Constants/Enums.h"

#include <raylib.h>
#include <memory>

namespace RE {

    class GameObject {
    public:
        GameObject() = default;
        explicit GameObject(Vector2 initialPosition, int zindex = 0);
        GameObject(Vector2 initialPosition, float speed, int zindex = 0);
        GameObject(Vector2 initialPosition, float speed, const std::string& textureName, const std::string& texturePath, int zindex = 0);
        ~GameObject();

        virtual void Update(float deltatime);
        virtual void Draw();

        void Destroy() { m_Destroy = true; }
        bool IsDestroyed() const { return m_Destroy; }

        int GetZindex() const { return m_Zindex; }
        void SetZindex(int zindex) { m_Zindex = zindex; }

        bool IsActive() const { return m_IsActive; }
        void SetActive(bool isActive) { m_IsActive = isActive; }

        virtual Vector2 GetPosition() const { return m_Position; }
        void SetPosition(Vector2 position) { m_Position = position; }

        Rectangle GetBoxCollider() const;
        void SetBoxCollider(Rectangle boxCollider) { m_BoxCollider = boxCollider; }
        bool IsColliding(const Rectangle& other) const;

        void SetCollisionType(GameObjectCollisionType collisionType) { m_CollisionType = collisionType; }
        GameObjectCollisionType GetCollisionType() const { return m_CollisionType; }

        virtual void Damage(int amount) { m_Health -= amount; }

        int GetHealth() const { return m_Health; }
        bool IsAlive() const { return m_Health > 0; }

        // For debugging purposes
        void SetDrawBoxCollider(bool draw) { m_DrawBoxCollider = draw; }
        void DrawBoxCollider() const;
    protected:
        std::weak_ptr<Texture2D> m_Texture;
        Vector2 m_Position{0};
        float m_Speed = 500.0f;
        bool m_Destroy = false;
        int m_Zindex = 0;
        bool m_IsActive = true;
        GameObjectCollisionType m_CollisionType = GameObjectCollisionType::COLLISION_TYPE_NONE;

        int m_Health = 3;
    private:
        Rectangle m_BoxCollider{0};
        bool m_DrawBoxCollider = false;
    };

}

#endif

#include "GameObjects/GameObject.h"
#include "Resources/ResourceManager.h"

RE::GameObject::GameObject(Vector2 initialPosition, int zindex) {
    m_Position = initialPosition;
    m_Zindex = zindex;
}

RE::GameObject::GameObject(Vector2 initialPosition, float speed, int zindex) {
    m_Position = initialPosition;
    m_Speed = speed;
    m_Zindex = zindex;
}

RE::GameObject::GameObject(Vector2 initialPosition, float speed, const std::string& textureName, const std::string& texturePath, int zindex) {
    m_Position = initialPosition;
    m_Speed = speed;
    m_Zindex = zindex;
    m_Texture = ResourceManager::Instance().RegisterTexture(textureName, texturePath);
    SetBoxCollider({
            m_Position.x,
            m_Position.y,
            static_cast<float>(m_Texture.lock()->width),
            static_cast<float>(m_Texture.lock()->height)
    });
}

RE::GameObject::~GameObject() {
}

void RE::GameObject::Update(float deltatime) {
    if (!m_IsActive) {
        return;
    }
}


void RE::GameObject::Draw() {
    if (!m_IsActive) {
        return;
    }

    if (auto texture = m_Texture.lock()) {
        DrawTextureV(*texture, m_Position, WHITE);
    }

    DrawBoxCollider();
}

Rectangle RE::GameObject::GetBoxCollider() const {
    return Rectangle {
        m_Position.x,
        m_Position.y,
        m_BoxCollider.width,
        m_BoxCollider.height
    };
}

bool RE::GameObject::IsColliding(const Rectangle &other) const {
    return m_IsActive && CheckCollisionRecs(GetBoxCollider(), other);
}

void RE::GameObject::DrawBoxCollider() const {
    if (!m_DrawBoxCollider || !m_IsActive) {
        return;
    }
    DrawRectangleLinesEx(GetBoxCollider(), 1, RED);
}

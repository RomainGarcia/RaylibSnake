#include "Game.h"
#include "Display/Window.h"
#include "Resources/ObjectManager.h"
#include "Resources/ResourceManager.h"
#include "Audio/Audio.h"
#include "GameObjects/Objects/Food.h"
#include "Constants/Constants.h"
#include "raymath.h"

RE::Game::Game() {
    // Window
    Window::Init();

    // Audio
    RE::Audio::Init(); // Needs to be called before adding sounds

    auto eatSound = ResourceManager::Instance().RegisterSound("eat", "assets/sounds/eat.mp3");
    if (eatSound == nullptr) {
        TraceLog(LOG_ERROR, "Failed to load sound: %s", "eat");
    }

    auto wellSound = ResourceManager::Instance().RegisterSound("wall", "assets/sounds/wall.mp3");
    SetSoundVolume(*eatSound, 0.5f);
    SetSoundVolume(*wellSound, 0.5f);

    // Textures
    ResourceManager::Instance().RegisterTexture("food", "assets/graphics/food.png");

    // Font
    ResourceManager::Instance().RegisterFont("monogram", "assets/font/monogram.ttf", 32);

    // GUI
    RE::Gui::Init(ResourceManager::Instance().GetFont("monogram"));
}

RE::Game::~Game() {
    RE::Audio::Shutdown();
    ResourceManager::Instance().UnloadAll();
    Window::Close();
}

void RE::Game::Run() {
    // Spawn a food object
    m_Snake = ObjectManager::Spawn<RE::Snake>();
    m_Food = ObjectManager::Spawn<RE::Food>(m_Snake->GetRandomFreePosition(), 0, "food", "assets/graphics/food.png");
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void RE::Game::Update() {
    if (!m_IsRunning && (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_W))) {
        m_IsRunning = true;
    }

    if (!m_IsRunning) {
        return;
    }

    float deltatime = GetFrameTime();
    RE::ObjectManager::Update(deltatime);
    RE::Gui::Update();
    CheckCollisionWithFood();
    CheckCollisionWithEdges();
    CheckCollisionWithTail();
}

void RE::Game::Draw() {
    RE::Window::BeginDrawing();

    RE::ObjectManager::Draw();
    RE::Gui::Draw(m_Score, m_IsRunning);

    RE::Window::EndDrawing();
}

void RE::Game::CheckCollisionWithFood() {
    if (Vector2Equals(m_Snake->GetPosition(), m_Food->GetPosition())) {
        RE::Audio::PlaySound("eat");
        m_Food->SetPosition(m_Snake->GetRandomFreePosition());
        m_Snake->AddSegment();
        m_Score++;
    }
}

void RE::Game::CheckCollisionWithEdges() {
    auto snakePosition = m_Snake->GetPosition();
    if (snakePosition.x == -1 || snakePosition.x == RE::CELL_COUNT ||
        snakePosition.y == -1 || snakePosition.y == RE::CELL_COUNT) {
        GameOver();
    }
}

void RE::Game::CheckCollisionWithTail() {
    auto snakePosition = m_Snake->GetPosition();
    if (m_Snake->IsElementInBody(snakePosition, true)) {
        GameOver();
    }
}


void RE::Game::GameOver() {
    RE::Audio::PlaySound("wall");
    m_Snake->Reset();
    m_Food->SetPosition(m_Snake->GetRandomFreePosition());
    m_IsRunning = false;
    m_Score = 0;
}

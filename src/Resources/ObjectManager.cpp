#include "ObjectManager.h"
#include "GameObjects/GameObject.h"

std::map<int, std::vector<std::shared_ptr<RE::GameObject>>> RE::ObjectManager::s_Objects;
std::map<int, std::vector<std::shared_ptr<RE::GameObject>>> RE::ObjectManager::s_SpawnedObjects;

void RE::ObjectManager::Update(float deltatime) {
    for (auto& zindex: s_Objects) {
        for (auto& object: zindex.second) {
            object->Update(deltatime);
        }

    }

    DestroyObjects();
    SpawnedObjects();
}

void RE::ObjectManager::Draw() {
    for (auto& zindex: s_Objects) {
        for (auto &object: zindex.second) {
            object->Draw();
        }
    }
}

void RE::ObjectManager::DestroyObjects() {
    for (auto& zindex: s_Objects) {
        for (auto it = zindex.second.begin(); it != zindex.second.end();) {
            if ((*it)->IsDestroyed()) {
                it = zindex.second.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void RE::ObjectManager::SpawnedObjects() {
    for (auto& zindex: s_SpawnedObjects) {
        s_Objects[zindex.first].reserve(zindex.second.size());
        for (auto& object: zindex.second) {
            s_Objects[zindex.first].push_back(std::move(object));
        }
    }

    s_SpawnedObjects.clear();
}

size_t RE::ObjectManager::Count() {
    size_t count = 0;

    for (auto& zindex: s_Objects) {
        count += zindex.second.size();
    }

    return count;
}

void RE::ObjectManager::ClearObjects() {
    // Delete all objects
    s_Objects.clear();
    s_SpawnedObjects.clear();
}

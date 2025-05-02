#ifndef SPACEINVADERSRAYLIB_OBJECTMANAGER_H
#define SPACEINVADERSRAYLIB_OBJECTMANAGER_H

#include "GameObjects/GameObject.h"

#include <vector>
#include <memory>
#include <map>

namespace RE {

    class ObjectManager {
    public:
        static void Update(float deltatime);
        static void Draw();
        static std::map<int, std::vector<std::shared_ptr<GameObject>>>& GetObjects() { return RE::ObjectManager::s_Objects; }
        static size_t Count();

        template<typename T, typename... Args>
        static std::shared_ptr<T> Spawn(Args&&... args) {
            return SpawnWithZIndex<T>(0, std::forward<Args>(args)...);
        }

        template<typename T, typename... Args>
        static std::shared_ptr<T> SpawnWithZIndex(int zIndex, Args&&... args) {
            static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject for Spawn to work");
            auto object = std::make_shared<T>(std::forward<Args>(args)...);
            s_SpawnedObjects[zIndex].emplace_back(std::static_pointer_cast<GameObject>(object));
            return object;
        }

        static void ClearObjects();

    private:
        static void DestroyObjects();
        static void SpawnedObjects();
        static std::map<int, std::vector<std::shared_ptr<GameObject>>> s_Objects;
        static std::map<int, std::vector<std::shared_ptr<GameObject>>> s_SpawnedObjects;
    };

}

#endif

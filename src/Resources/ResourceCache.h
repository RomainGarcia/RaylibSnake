#ifndef RAYLIBBOILERPLATE_RESOURCECACHE_H
#define RAYLIBBOILERPLATE_RESOURCECACHE_H

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace RE {

    template <typename T>
    class ResourceCache {
    public:
        std::shared_ptr<T> Get(const std::string& key, std::function<T(const std::string&)> loader) {
            if (!resources.contains(key)) {
                resources[key] = std::make_shared<T>(loader(key));
            }
            return resources[key];
        }

        void Unload(const std::string& key, std::function<void(T&)> deleter) {
            auto it = resources.find(key);
            if (it != resources.end()) {
                deleter(*it->second);
                resources.erase(it);
            }
        }

        void UnloadAll(std::function<void(T&)> deleter) {
            for (auto& [_, res] : resources) {
                deleter(*res);
            }
            resources.clear();
        }

        bool Contains(const std::string& key) const {
            return resources.contains(key);
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<T>> resources;
    };


}

#endif

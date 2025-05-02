#ifndef RAYLIBBOILERPLATE_RESOURCEMANAGER_H
#define RAYLIBBOILERPLATE_RESOURCEMANAGER_H

#include <raylib.h>
#include "Resources/ResourceCache.h"

#include <string>
#include <unordered_map>

namespace RE {

    class ResourceManager {
    public:
        static ResourceManager& Instance();

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        // Registration
        std::shared_ptr<Texture2D> RegisterTexture(const std::string& name, const std::string& path);
        std::shared_ptr<Sound> RegisterSound(const std::string& name, const std::string& path);
        std::shared_ptr<Music> RegisterMusic(const std::string& name, const std::string& path);
        std::shared_ptr<Font> RegisterFont(const std::string& name, const std::string& path, int fontSize = 32);

        // Access
        std::shared_ptr<Texture2D> GetTexture(const std::string& name);
        std::shared_ptr<Sound> GetSound(const std::string& name);
        std::shared_ptr<Music> GetMusic(const std::string& name);
        std::shared_ptr<Font> GetFont(const std::string& name);

        // Unload
        void UnloadTexture(const std::string& name);
        void UnloadSound(const std::string& name);
        void UnloadMusic(const std::string& name);
        void UnloadFont(const std::string& name);

        // Cleanup
        void UnloadAll();

    private:
        ResourceManager() = default;
        ~ResourceManager();

        ResourceCache<Texture2D> m_Textures;
        ResourceCache<Sound> m_Sounds;
        ResourceCache<Music> m_Musics;
        ResourceCache<Font> m_Fonts;

        std::unordered_map<std::string, std::string> m_TexturePaths;
        std::unordered_map<std::string, std::string> m_SoundPaths;
        std::unordered_map<std::string, std::string> m_MusicPaths;
        std::unordered_map<std::string, std::string> m_FontPaths;
    };

}

#endif

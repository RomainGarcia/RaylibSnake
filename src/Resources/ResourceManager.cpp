#include <stdexcept>
#include "ResourceManager.h"

RE::ResourceManager& RE::ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

RE::ResourceManager::~ResourceManager() {
    UnloadAll();
}

// --- Register & Load Immediately ---

std::shared_ptr<Texture2D> RE::ResourceManager::RegisterTexture(const std::string& name, const std::string& path) {
    return m_Textures.Get(name, [path](const std::string&) {
        return LoadTexture(path.c_str());
    });
}

std::shared_ptr<Sound> RE::ResourceManager::RegisterSound(const std::string& name, const std::string& path) {
    return m_Sounds.Get(name, [path](const std::string&) {
        Sound sound = LoadSound(path.c_str());
        if (sound.stream.buffer == nullptr) {
            TraceLog(LOG_ERROR, TextFormat("Failed to load sound: %s", path.c_str()));
        }
        return sound;
    });
}

std::shared_ptr<Music> RE::ResourceManager::RegisterMusic(const std::string& name, const std::string& path) {
    return m_Musics.Get(name, [path](const std::string&) {
        return LoadMusicStream(path.c_str());
    });
}

std::shared_ptr<Font> RE::ResourceManager::RegisterFont(const std::string& name, const std::string& path, int fontSize) {
    return m_Fonts.Get(name, [path](const std::string&) {
        return LoadFont(path.c_str());
    });
}

// --- Get already-loaded resources (no throw) ---

std::shared_ptr<Texture2D> RE::ResourceManager::GetTexture(const std::string& name) {
    if (!m_Textures.Contains(name)) {
        return nullptr;
    }
    return m_Textures.Get(name, [](const std::string&) {
        return Texture2D{}; // ne sera jamais utilisé
    });
}

std::shared_ptr<Sound> RE::ResourceManager::GetSound(const std::string& name) {
    if (!m_Sounds.Contains(name)) {
        return nullptr;
    }
    return m_Sounds.Get(name, [](const std::string&) {
        return Sound{};
    });
}

std::shared_ptr<Music> RE::ResourceManager::GetMusic(const std::string& name) {
    if (!m_Musics.Contains(name)) {
        return nullptr;
    }
    return m_Musics.Get(name, [](const std::string&) {
        return Music{};
    });
}

std::shared_ptr<Font> RE::ResourceManager::GetFont(const std::string& name) {
    if (!m_Fonts.Contains(name)) {
        return nullptr;
    }
    return m_Fonts.Get(name, [](const std::string&) {
        return Font{};
    });
}

// --- Cleanup ---
void RE::ResourceManager::UnloadAll() {
    m_Textures.UnloadAll(::UnloadTexture);
    m_Sounds.UnloadAll(::UnloadSound);
    m_Musics.UnloadAll(::UnloadMusicStream);
    m_Fonts.UnloadAll(::UnloadFont);
}

void RE::ResourceManager::UnloadTexture(const std::string& name) {
    m_Textures.Unload(name, ::UnloadTexture);
}

void RE::ResourceManager::UnloadSound(const std::string& name) {
    m_Sounds.Unload(name, ::UnloadSound);
}

void RE::ResourceManager::UnloadMusic(const std::string& name) {
    m_Musics.Unload(name, ::UnloadMusicStream);
}

void RE::ResourceManager::UnloadFont(const std::string& name) {
    m_Fonts.Unload(name, ::UnloadFont);
}

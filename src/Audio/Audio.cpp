#include "Audio.h"
#include "Resources/ResourceManager.h"

void RE::Audio::Init() {
    InitAudioDevice();
}

void RE::Audio::Shutdown() {
    CloseAudioDevice();
}

void RE::Audio::PlaySound(const std::string& name) {
    auto sound = ResourceManager::Instance().GetSound(name);
    if (!sound) {
        TraceLog(LOG_ERROR, "Audio::PlaySound: Sound '%s' not found", name.c_str());
        return;
    }
    ::PlaySound(*sound);
}

void RE::Audio::PlayMusic(const std::string& name) {
    auto music = ResourceManager::Instance().GetMusic(name);
    if (!music) {
        TraceLog(LOG_ERROR, "Audio::PlayMusic: Music '%s' not found", name.c_str());
        return;
    }
    ::PlayMusicStream(*music);
}

void RE::Audio::StopMusic(const std::string& name) {
    auto music = ResourceManager::Instance().GetMusic(name);
    if (!music) {
        TraceLog(LOG_ERROR, "Audio::StopMusic: Music '%s' not found", name.c_str());
        return;
    }
    ::StopMusicStream(*music);
}

void RE::Audio::UpdateMusic(const std::string& name) {
    auto music = ResourceManager::Instance().GetMusic(name);
    if (!music) {
        TraceLog(LOG_ERROR, "Audio::UpdateMusic: Music '%s' not found", name.c_str());
        return;
    }
    UpdateMusicStream(*music);
}


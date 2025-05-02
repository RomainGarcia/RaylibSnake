#ifndef SPACEINVADERSRAYLIB_AUDIO_H
#define SPACEINVADERSRAYLIB_AUDIO_H

#include <raylib.h>
#include <unordered_map>
#include <string>
#include "Constants/Enums.h"

namespace RE {

    class Audio {
    public:
        static void Init();
        static void Shutdown();
        static void PlaySound(const std::string& name);
        static void PlayMusic(const std::string& name);
        static void StopMusic(const std::string& name);
        static void UpdateMusic(const std::string& name);
    };

}

#endif

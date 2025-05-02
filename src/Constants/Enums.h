#ifndef RAYLIBBOILERPLATE_ENUMS_H
#define RAYLIBBOILERPLATE_ENUMS_H

namespace RE {
    enum AudioSoundName {
        AUDIO_SOUND_NAME_EXPLOSION,
    };

    enum AudioMusicName {
        AUDIO_MUSIC_NAME_MUSIC,
    };

    enum class GameObjectCollisionType {
        COLLISION_TYPE_NONE,
        COLLISION_TYPE_PLAYER,
        COLLISION_TYPE_ALIEN,
        COLLISION_TYPE_MYSTERY_SHIP,
        COLLISION_TYPE_OBSTACLE,
        COLLISION_TYPE_LASER,
    };


}

#endif //RAYLIBBOILERPLATE_ENUMS_H

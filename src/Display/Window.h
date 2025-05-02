#ifndef SPACEINVADERSRAYLIB_WINDOW_H
#define SPACEINVADERSRAYLIB_WINDOW_H

#include <raylib.h>

namespace RE {
    class Window {
    public:
        static void Init();
        static void Close();

        static void BeginDrawing();
        static void EndDrawing();

        static float GetVerticalCenter(int offset = 0);
        static float GetHorizontalCenter(int offset = 0);
    };

}

#endif

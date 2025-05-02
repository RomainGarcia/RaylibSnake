#ifndef SPACEINVADERSRAYLIB_GUI_H
#define SPACEINVADERSRAYLIB_GUI_H

#include <raylib.h>
#include <string>
#include <memory>

namespace RE {

    class Gui {
    public:
        static void Init(std::weak_ptr<Font> defaultFont);
        static void Update();
        static void Draw(int score, bool isRunning);
    private:
        static std::weak_ptr<Font> m_DefaultFont;
    };

}

#endif

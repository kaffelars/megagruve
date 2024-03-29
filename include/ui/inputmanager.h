#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "windowmanager.h"
#include "uicontroller.h"

namespace inputmanager
{
    enum key_mods
    {
        mod_none = 0,
        mod_ctrl = 1,
        mod_shift = 2,
        mod_crab = 4
    };

    enum keytype
    {
        KEYTYPE_KEYBOARD,
        KEYTYPE_MOUSEBUTTON,
        KEYTYPE_MOUSESCROLL
    };

    enum keystatus
    {
        KS_DOWN,
        KS_UP
    };

    enum keyevent
    {
        KE_CLICKED,
        KE_HELD,
        KE_RELEASED
    };

    enum keys_enum
    {
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_ZOOMIN,
        KEY_ZOOMOUT,
        KEY_ZOOMUP,
        KEY_ZOOMDOWN,
        KEY_ROTATECAM,
        KEY_SELECT,
        KEY_INTERACT,
        KEY_MISC,
        KEY_ESCAPE,
        KEY_INV,
        KEY_TOGGLEFLYING,
        KEY_TOGGLEINFOBOX,
        KEY_RUNNING,
        KEY_SNEAKING,
        KEY_JUMP,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,
        KEY_LAST //for count
    };


    extern int recordpress;
    extern void recordnextpress();
    extern bool keyrecorded;

    void initialize();
    void logcursorpos();

    /*extern glm::ivec2 cursorpos;
    extern glm::ivec2 deltamove;
    extern glm::ivec2 mousetrappos;
    extern bool mousehidden;*/

    void hidemouse();
    void showmouse();

    glm::ivec2 getmousedelta();
    bool ismousehidden();

    glm::ivec2 getcursorpos();
    glm::ivec2 getcenterpos();


    void clearallkeyfunctions();
    void pausekeyfunctions();
    void unpausekey(keys_enum);
    void resumekeyfunctions();

    void resumeallkeyfunctions();
    void pauseallkeyfunctions();
    void pausekeyfunctionsexcept(std::vector<keys_enum> keys);

    void setkeyfunction(keys_enum keyid, std::function<void()> kclick, keyevent kevent);

    void processevent(SDL_Event& e);
    void processheldkeys();

    void clearheldkeys();

    struct keydata
    {
        bool held {false};
        bool clicked {false};
        int value {0};//for eks scroll
        keytype ktype {KEYTYPE_KEYBOARD};
        int32_t keypress {0};

        std::string keydescription; //eks "forward", "cancel" osv.

        std::function<void()> keyfunction[3] = {std::function<void()>(), std::function<void()>(), std::function<void()>()};//funker ikke for mus/scroll

        void setkeyclick(std::function<void()> kclick, keyevent kevent)
        {
            keyfunction[kevent] = kclick;
        }

        void clearkeyclicks()
        {
            for (int a = 0; a < 3; a++)
                keyfunction[a] = nullptr;
        }
        std::string getkeyname()
        {
            if (ktype == KEYTYPE_KEYBOARD)
            {
                return SDL_GetKeyName(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(keypress)));
            }
            else if (ktype == KEYTYPE_MOUSESCROLL)
            {
                return (keypress == 1 ? "Mouse scroll up" : "Mouse scroll down");
            }
            else if (ktype == KEYTYPE_MOUSEBUTTON)
            {
                if (keypress == 1)
                {
                    return "Left mouse button";
                }
                else if (keypress == 3)
                {
                    return "Right mouse button";
                }
                return "Mouse button " + std::to_string(keypress);
            }
            return "Key error";
        }

        keydata(std::string description, keytype ktyp, int32_t kpress) : ktype{ktyp}, keypress{kpress}, keydescription{description}
        {

        }
    };

    std::vector<keydata>& getkeydata();
};

#endif // INPUTMANAGER_H

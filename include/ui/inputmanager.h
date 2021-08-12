#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "windowmanager.h"
#include "uicontroller.h"

namespace inputmanager
{
    enum key_mods
    {
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
        KEY_MISC,
        KEY_ESCAPE,
        KEY_LAST //for count
    };

    struct b_key //bound key - inkluder mus
    {
        keytype ktype;

        int mouse; //bruk union?

        SDL_Scancode key; //to get: event->key.keysym.scancode
        uint8_t key_modifiers; //eks ctrl, shift osv. bit and for å sjekke

        std::string key_function; //eks "forward", "cancel" osv.

        void initialize_k(SDL_Scancode k, uint8_t m, std::string func)
        {
            ktype = KEYTYPE_KEYBOARD;
            key = k;
            key_modifiers = m;
            key_function = func;
        }

        void initialize_mb(int mousebutt, uint8_t m, std::string func)
        {
            ktype = KEYTYPE_MOUSEBUTTON;
            mouse = mousebutt;
            key_modifiers = m;
            key_function = func;
        }

        void initialize_ms(int mousescr, uint8_t m, std::string func)
        {
            ktype = KEYTYPE_MOUSESCROLL;
            mouse = mousescr; // -1 eller 1
            key_modifiers = m;
            key_function = func;
        }

        SDL_Keycode getkeycode()
        {
            if (ktype == KEYTYPE_KEYBOARD)
                return SDL_GetKeyFromScancode(key);
        }
    };

    extern int recordpress;
    extern b_key recordedpress;
    extern void recordnextpress();
    extern bool keyrecorded;

    std::string getkeyname(b_key& bkey);


    extern std::vector<b_key> bound_keys;

    void initialize();
    void refresh();
    void logcursorpos();

    extern glm::ivec2 cursorpos;

    extern glm::ivec2 deltamove;

    extern glm::ivec2 mousetrappos;

    extern bool mousehidden;

    void hidemouse();
    void showmouse();

    glm::ivec2 getmousedelta();
    bool ismousehidden();

    glm::ivec2 getcursorpos();

    struct keyinfo
    {
        bool held;
        bool clicked;
        int value;//for eks scroll

        keyinfo() //initialize først gang accesses i unordered mæp
        {
            held = false;
            clicked = false;
            value = 0;
        }
    };

    uint8_t getmodifiers();

    bool isscancodemodifier(SDL_Scancode scan);

    extern keyinfo mousescroll;//lag generisk også for f.eks. joystick?

    extern std::unordered_map<SDL_Scancode, keyinfo> keys;
    extern std::unordered_map<int, keyinfo> buttons;

    bool iskeyheld(int keyid);
    bool waskeyclicked(int keyid);
    int getkeyvalue(int keyid);

    extern std::vector<SDL_Scancode> clickedkeys;//holder hvilke keys som ble clicked forrige frame
    extern std::vector<int> clickedbuttons;

    void processevent(SDL_Event& e);

    extern uint8_t currentmodifiers; //hvilke mod keys som holdes down NÅ
};

#endif // INPUTMANAGER_H

#include "consts.h"
#include "inputmanager.h"


namespace inputmanager
{
    std::vector<b_key> bound_keys;
    std::unordered_map<SDL_Scancode, keyinfo> keys;
    std::unordered_map<int, keyinfo> buttons;
    glm::ivec2 cursorpos;
    glm::ivec2 deltamove;
    glm::ivec2 mousetrappos;
    keyinfo mousescroll;
    //glm::ivec2 inputmanager::cursorposold;
    bool mousehidden = false;

    uint8_t currentmodifiers = 0;

    int recordpress = 0;
    b_key recordedpress;

    std::vector<SDL_Scancode> clickedkeys;//holder hvilke keys som ble clicked forrige frame
    std::vector<int> clickedbuttons;
}

void inputmanager::initialize()
{
    std::cout << "initializing keys... "; //obs, lag så de kan endres
    inputmanager::bound_keys.clear(); //to make sure no double shenanigans

    for (int a = 0; a < KEY_LAST; a++)
        inputmanager::bound_keys.emplace_back(b_key());

    inputmanager::bound_keys[KEY_UP].initialize_k(SDL_SCANCODE_W, 0, "up");
    inputmanager::bound_keys[KEY_DOWN].initialize_k(SDL_SCANCODE_S, 0, "down");
    inputmanager::bound_keys[KEY_LEFT].initialize_k(SDL_SCANCODE_A, 0, "left");
    inputmanager::bound_keys[KEY_RIGHT].initialize_k(SDL_SCANCODE_D, 0, "right");

    inputmanager::bound_keys[KEY_ROTATECAM].initialize_mb(SDL_BUTTON_RIGHT, 0, "rotate cam");
    inputmanager::bound_keys[KEY_SELECT].initialize_mb(SDL_BUTTON_LEFT, 0, "select object");
    inputmanager::bound_keys[KEY_MISC].initialize_k(SDL_SCANCODE_C, 0, "misc");
    inputmanager::bound_keys[KEY_ZOOMUP].initialize_ms(1, inputmanager::mod_shift, "zoom up");
    inputmanager::bound_keys[KEY_ZOOMDOWN].initialize_ms(-1, inputmanager::mod_shift, "zoom down");

    inputmanager::bound_keys[KEY_ZOOMIN].initialize_ms(1, 0, "zoom in");
    inputmanager::bound_keys[KEY_ZOOMOUT].initialize_ms(-1, 0, "zoom out");

    inputmanager::bound_keys[KEY_ESCAPE].initialize_k(SDL_SCANCODE_ESCAPE, 0, "escape");

    std::cout << "done\n";
}

void inputmanager::hidemouse()//hides and locks mouse
{
    if (!inputmanager::ismousehidden())
    {
        SDL_ShowCursor(SDL_DISABLE);
        inputmanager::mousehidden = true;
        inputmanager::mousetrappos = inputmanager::getcursorpos();
    }
}

void inputmanager::showmouse()
{
    if (inputmanager::ismousehidden())
    {
        SDL_ShowCursor(SDL_ENABLE);
        inputmanager::mousehidden = false;
    }
}

bool inputmanager::ismousehidden()
{
    return inputmanager::mousehidden;
}

void inputmanager::logcursorpos()
{
    glm::ivec2 cursorposold = inputmanager::cursorpos;
    SDL_GetMouseState(&inputmanager::cursorpos.x, &inputmanager::cursorpos.y);

    inputmanager::deltamove = inputmanager::cursorpos - cursorposold;

    if (inputmanager::ismousehidden()) //mus låst
    {
        //inputmanager::deltamove = inputmanager::cursorpos - inputmanager::mousetrappos;
        inputmanager::cursorpos = inputmanager::mousetrappos;
        SDL_WarpMouseInWindow(windowmanager::sdlwindow, inputmanager::mousetrappos.x, inputmanager::mousetrappos.y);
    }
}

glm::ivec2 inputmanager::getcursorpos()
{
    return inputmanager::cursorpos;
}

glm::ivec2 inputmanager::getmousedelta()
{
    return inputmanager::deltamove;
}

void inputmanager::refresh()
{
    //kjøres på starten av hver frame før input sjekkes

    inputmanager::mousescroll.value = 0;

    for (SDL_Scancode s : clickedkeys) //disse keys ble clicked forrige frame
    {
        inputmanager::keys[s].clicked = false;
    }

    clickedkeys.clear();

    for (int b : clickedbuttons)
    {
        inputmanager::buttons[b].clicked = false;
    }

    clickedbuttons.clear();
}

bool inputmanager::iskeyheld(int keyid) //enum key
{
    keytype k = inputmanager::bound_keys[keyid].ktype;
    bool mainkey = false;
    uint8_t mods = 0;

    if (k == KEYTYPE_KEYBOARD)
    {
        SDL_Scancode s_key = inputmanager::bound_keys[keyid].key;
        mods = inputmanager::bound_keys[keyid].key_modifiers;

        mainkey = inputmanager::keys[s_key].held;
    }
    if (k == KEYTYPE_MOUSEBUTTON)
    {
        int button = inputmanager::bound_keys[keyid].mouse;
        mods = inputmanager::bound_keys[keyid].key_modifiers;

        mainkey = inputmanager::buttons[button].held;
    }
    if (k == KEYTYPE_MOUSESCROLL)
    {
        int scroll = inputmanager::bound_keys[keyid].mouse;
        mods = inputmanager::bound_keys[keyid].key_modifiers;
        mainkey = (inputmanager::mousescroll.value == scroll); //vil dette alltid funke? kan scroll være over +/-1?
    }

    uint8_t curmods = getmodifiers();

    return (mainkey && (!mods || (curmods & mods)));
}

std::string inputmanager::getkeyname(b_key& bkey)
{
    std::string keyname = "";

    if (bkey.ktype == KEYTYPE_KEYBOARD)
    {
        const char* ckeyname = SDL_GetKeyName(bkey.getkeycode()); //memory leak? nei

        keyname = ckeyname;
    }
    else
    {
        if (bkey.ktype == KEYTYPE_MOUSEBUTTON)
        {
            keyname = "mouse button " + std::to_string(bkey.mouse);//todo
        }
        if (bkey.ktype == KEYTYPE_MOUSESCROLL)
        {
            if (bkey.mouse > 0.0f)
            {
                keyname = "mouse scroll up";
            }
            else
            {
                keyname = "mouse scroll down";
            }
        }
    }

    if (bkey.key_modifiers & key_mods::mod_ctrl) keyname = "ctrl + " + keyname;
    if (bkey.key_modifiers & key_mods::mod_shift) keyname = "shift + " + keyname;

    return keyname;
}

void inputmanager::recordnextpress()
{
    recordpress = 1;
}

uint8_t inputmanager::getmodifiers()
{
    uint8_t mods = 0;

    if (inputmanager::keys[SDL_SCANCODE_LCTRL].held || inputmanager::keys[SDL_SCANCODE_RCTRL].held)
    {
        mods = mods | mod_ctrl;
    }

    if (inputmanager::keys[SDL_SCANCODE_LSHIFT].held || inputmanager::keys[SDL_SCANCODE_RSHIFT].held)
    {
        mods = mods | mod_shift;
    }

    return mods;
}

bool inputmanager::waskeyclicked(int keyid) //enum key
{
    bool mainkey = false;
    keytype k = inputmanager::bound_keys[keyid].ktype;
    uint8_t mods = 0;

    if (k == KEYTYPE_KEYBOARD)
    {
        SDL_Scancode s_key = inputmanager::bound_keys[keyid].key;
        mods = inputmanager::bound_keys[keyid].key_modifiers;

        mainkey = inputmanager::keys[s_key].clicked;
    }
    if (k == KEYTYPE_MOUSEBUTTON)
    {
        int button = inputmanager::bound_keys[keyid].mouse;
        mods = inputmanager::bound_keys[keyid].key_modifiers;

        mainkey = inputmanager::buttons[button].clicked;
    }
    if (k == KEYTYPE_MOUSESCROLL)
    {
        int scroll = inputmanager::bound_keys[keyid].mouse;
        mods = inputmanager::bound_keys[keyid].key_modifiers;
        mainkey = (inputmanager::mousescroll.value == scroll);
    }

    uint8_t curmods = getmodifiers();

    return (mainkey && ((curmods == mods) || (curmods & mods)));
}

int inputmanager::getkeyvalue(int keyid) //returner 1 hvis key held for annet enn scroll
{
    keytype k = inputmanager::bound_keys[keyid].ktype;

    if (k == KEYTYPE_MOUSESCROLL)
    {
        return inputmanager::mousescroll.value;
    }
    else
    {
        inputmanager::iskeyheld(keyid);
    }

    return 0;
}

bool inputmanager::isscancodemodifier(SDL_Scancode scan)
{
    if (scan == SDL_SCANCODE_LCTRL || scan == SDL_SCANCODE_RCTRL || scan == SDL_SCANCODE_LSHIFT || scan == SDL_SCANCODE_RSHIFT)
    {
        return true;
    }

    return false;
}


void inputmanager::processevent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        SDL_Scancode s_key = e.key.keysym.scancode;
        bool held = inputmanager::keys[s_key].held;
        if (held == false) //clicked
        {
            inputmanager::keys[s_key].clicked = true;
            clickedkeys.push_back(s_key);
        }
        inputmanager::keys[s_key].held = true;

        if (recordpress == 1 && isscancodemodifier(s_key) == false)
        {
            recordedpress.ktype = KEYTYPE_KEYBOARD;
            recordedpress.key = s_key;
            recordedpress.key_modifiers = getmodifiers();//obs
            recordpress = 2;
        }
    }

    if (e.type == SDL_KEYUP)
    {
        SDL_Scancode s_key = e.key.keysym.scancode;
        inputmanager::keys[s_key].held = false;
    }

    //if (!uicontroller::uimouse()) //denne blir fuckaroni med f.eks. keybinds
    //{
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int button = e.button.button;
            bool held = inputmanager::buttons[button].held;
            if (held == false) //clicked
            {
                inputmanager::buttons[button].clicked = true;
                clickedbuttons.push_back(button);
            }
            inputmanager::buttons[button].held = true;

            if (recordpress == 1)
            {
                recordedpress.ktype = KEYTYPE_MOUSEBUTTON;
                recordedpress.mouse = button;
                recordedpress.key_modifiers = getmodifiers();//obs
                recordpress = 2;
            }
        }

        if (e.type == SDL_MOUSEWHEEL)
        {
            inputmanager::mousescroll.value = e.wheel.y;

            if (recordpress == 1)
            {
                recordedpress.ktype = KEYTYPE_MOUSESCROLL;
                recordedpress.mouse = e.wheel.y;
                recordedpress.key_modifiers = getmodifiers();//obs
                recordpress = 2;
            }
        }
    //}

    if (e.type == SDL_MOUSEBUTTONUP)
    {
        int button = e.button.button;
        inputmanager::buttons[button].held = false;
    }

}

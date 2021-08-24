#include "consts.h"
#include "inputmanager.h"


namespace inputmanager
{
    glm::ivec2 cursorpos;
    glm::ivec2 deltamove;
    glm::ivec2 mousetrappos;
    //glm::ivec2 inputmanager::cursorposold;
    bool mousehidden = false;

    uint8_t currentmodifiers = 0;

    bool keyfunctionsactive = false;

    int recordpress = 0;
    //b_key recordedpress;

    uint8_t getmodifiers();

    //ny
    void addkey(keytype ktype, keys_enum keyenum, int32_t keypress, key_mods kmod, std::string description);
    uint32_t getkeyid(keytype ktype, int32_t keypress, key_mods kmod);
    void processkey(keytype ktype, int32_t keypress, key_mods kmod, keystatus kstatus);
    uint32_t getkeyidfromenum(keys_enum keyenum);
    std::vector<uint32_t> heldkeys;
    std::vector<keydata> keymap;
    std::unordered_map<uint32_t, uint32_t> keyidtokeymap;
    std::unordered_map<uint32_t, uint32_t> keyenumtokeymap;
}

uint32_t inputmanager::getkeyid(keytype ktype, int32_t keypress, key_mods kmod)
{
    union keyk
    {
        struct ss
        {
            uint8_t scancode; //hvorfor ikke bare ha ktype og keypress og kmods
            uint8_t button;
            uint8_t scroll;
            uint8_t kmods;
        } s;

        uint32_t i;
    };

    keyk k;
    k.s.scancode = 0;
    k.s.button = 0;
    k.s.scroll = 0;
    k.s.kmods = kmod;

    switch (ktype)
    {
    case KEYTYPE_KEYBOARD:
        k.s.scancode = keypress;
        break;
    case KEYTYPE_MOUSEBUTTON:
        k.s.button = keypress;
        break;
    case KEYTYPE_MOUSESCROLL:
        if (keypress == 1)
            k.s.scroll = 1;
        else if (keypress == -1)
            k.s.scroll = 2;
        break;
    }

    return k.i;
}

void inputmanager::processheldkeys()
{
    for (uint32_t k_id : heldkeys)
    {
        keydata& key = keymap[k_id];
        if (keyfunctionsactive && key.keyfunction[KE_HELD])
            key.keyfunction[KE_HELD]();
    }
}

void inputmanager::processkey(keytype ktype, int32_t keypress, key_mods kmod, keystatus kstatus)
{
    uint32_t kid = getkeyid(ktype, keypress, kmod);

    if (keyidtokeymap.find(kid) == keyidtokeymap.end()) return;

    uint32_t k_id = keyidtokeymap.at(kid);
    keydata& key = keymap[k_id];

    if (kstatus == KS_DOWN)
    {
        key.clicked = false;
        if (key.held == false)
        {
            key.clicked = true;
            if (keyfunctionsactive && key.keyfunction[KE_CLICKED])
                key.keyfunction[KE_CLICKED]();
        }
        heldkeys.push_back(k_id);
        key.held = true;

    }

    if (kstatus == KS_UP)
    {
        heldkeys.erase(std::remove(heldkeys.begin(), heldkeys.end(), k_id), heldkeys.end());
        key.held = false;
        key.clicked = false;
        if (keyfunctionsactive && key.keyfunction[KE_RELEASED])
            key.keyfunction[KE_RELEASED]();
    }
}

void inputmanager::processevent(SDL_Event& e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        {
            SDL_Scancode s_key = e.key.keysym.scancode;
            processkey(KEYTYPE_KEYBOARD, s_key, mod_none, KS_DOWN);
            break;
        }
    case SDL_KEYUP:
        {
            SDL_Scancode s_key = e.key.keysym.scancode;
            processkey(KEYTYPE_KEYBOARD, s_key, mod_none, KS_UP);
            break;
        }
    case SDL_MOUSEBUTTONDOWN:
        {
            int button = e.button.button;
            processkey(KEYTYPE_MOUSEBUTTON, button, mod_none, KS_DOWN);
            break;
        }
    case SDL_MOUSEBUTTONUP:
        {
            int button = e.button.button;
            processkey(KEYTYPE_MOUSEBUTTON, button, mod_none, KS_UP);
            break;
        }
    case SDL_MOUSEWHEEL:
        {
            if (e.wheel.y > 0)
                processkey(KEYTYPE_MOUSESCROLL, 1, mod_none, KS_DOWN);
            if (e.wheel.y < 0)
                processkey(KEYTYPE_MOUSESCROLL, -1, mod_none, KS_DOWN);
            break;
        }
    default:
        break;
    }

    processkey(KEYTYPE_MOUSESCROLL, 1, mod_none, KS_UP);
    processkey(KEYTYPE_MOUSESCROLL, -1, mod_none, KS_UP);
}

void inputmanager::addkey(keytype ktype, keys_enum keyenum, int32_t keypress, key_mods kmod, std::string description)
{
    keymap.emplace_back(keydata(description, ktype));
    uint32_t id = keymap.size()-1;

    uint32_t kid = getkeyid(ktype, keypress, kmod);

    keyidtokeymap.insert(std::pair(kid, id));
    keyenumtokeymap.insert(std::pair(keyenum, id));
}

uint32_t inputmanager::getkeyidfromenum(keys_enum keyenum)
{
    if (keyenumtokeymap.find(keyenum) == keyenumtokeymap.end()) return 0;
    return keyenumtokeymap.at(keyenum);
}

void inputmanager::setkeyfunction(keys_enum keyenum, std::function<void()> kclick, keyevent kevent)
{
    uint32_t keyid = getkeyidfromenum(keyenum);
    keymap[keyid].setkeyclick(kclick, kevent);
}

void inputmanager::clearallkeyfunctions()
{
    for (keydata& k : keymap)
    {
        k.clearkeyclicks();
    }
}

void inputmanager::pausekeyfunctions()
{
    keyfunctionsactive = false;
}

void inputmanager::resumekeyfunctions()
{
    keyfunctionsactive = true;
}

void inputmanager::initialize()
{
    std::cout << "initializing keys... "; //obs, lag så de kan endres
    addkey(KEYTYPE_KEYBOARD, KEY_ESCAPE, SDL_SCANCODE_ESCAPE, mod_none, "escape");
    addkey(KEYTYPE_KEYBOARD, KEY_1, SDL_SCANCODE_1, mod_none, "selection 1");
    addkey(KEYTYPE_KEYBOARD, KEY_2, SDL_SCANCODE_2, mod_none, "selection 2");
    addkey(KEYTYPE_KEYBOARD, KEY_3, SDL_SCANCODE_3, mod_none, "selection 3");
    addkey(KEYTYPE_KEYBOARD, KEY_4, SDL_SCANCODE_4, mod_none, "selection 4");
    addkey(KEYTYPE_KEYBOARD, KEY_5, SDL_SCANCODE_5, mod_none, "selection 5");
    addkey(KEYTYPE_KEYBOARD, KEY_6, SDL_SCANCODE_6, mod_none, "selection 6");
    addkey(KEYTYPE_KEYBOARD, KEY_7, SDL_SCANCODE_7, mod_none, "selection 7");
    addkey(KEYTYPE_KEYBOARD, KEY_8, SDL_SCANCODE_8, mod_none, "selection 8");
    addkey(KEYTYPE_KEYBOARD, KEY_9, SDL_SCANCODE_9, mod_none, "selection 9");
    addkey(KEYTYPE_KEYBOARD, KEY_0, SDL_SCANCODE_0, mod_none, "selection 10");

    addkey(KEYTYPE_MOUSESCROLL, KEY_ZOOMIN, 1, mod_none, "zoom in");
    addkey(KEYTYPE_MOUSESCROLL, KEY_ZOOMOUT, -1, mod_none, "zoom out");

    addkey(KEYTYPE_MOUSEBUTTON, KEY_SELECT, SDL_BUTTON_LEFT, mod_none, "select");

    addkey(KEYTYPE_KEYBOARD, KEY_UP, SDL_SCANCODE_W, mod_none, "up");
    addkey(KEYTYPE_KEYBOARD, KEY_DOWN, SDL_SCANCODE_S, mod_none, "down");
    addkey(KEYTYPE_KEYBOARD, KEY_LEFT, SDL_SCANCODE_A, mod_none, "left");
    addkey(KEYTYPE_KEYBOARD, KEY_RIGHT, SDL_SCANCODE_D, mod_none, "right");

    addkey(KEYTYPE_KEYBOARD, KEY_INV, SDL_SCANCODE_I, mod_none, "inventory");



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


void inputmanager::recordnextpress()
{
    recordpress = 1;
}

uint8_t inputmanager::getmodifiers()
{
    /*uint8_t mods = 0;

    if (inputmanager::keys[SDL_SCANCODE_LCTRL].held || inputmanager::keys[SDL_SCANCODE_RCTRL].held)
    {
        mods = mods | mod_ctrl;
    }

    if (inputmanager::keys[SDL_SCANCODE_LSHIFT].held || inputmanager::keys[SDL_SCANCODE_RSHIFT].held)
    {
        mods = mods | mod_shift;
    }

    return mods;*/
    return 0;
}

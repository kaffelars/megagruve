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

    bool cursorjusthidden = false;

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

    std::vector<bool> keypaused;
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

void inputmanager::clearheldkeys()
{
    heldkeys.clear();
}

void inputmanager::processheldkeys()
{
    for (uint32_t k_id : heldkeys)
    {
        keydata& key = keymap[k_id];
        if (!keypaused[k_id] && key.keyfunction[KE_HELD])
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
            if (!keypaused[k_id] && key.keyfunction[KE_CLICKED])
                key.keyfunction[KE_CLICKED]();
        }
        heldkeys.push_back(k_id);
        key.held = true;

    }

    if (kstatus == KS_UP)
    {
        if (std::find(heldkeys.begin(), heldkeys.end(), k_id) != heldkeys.end())
            heldkeys.erase(std::remove(heldkeys.begin(), heldkeys.end(), k_id), heldkeys.end());
        key.held = false;
        key.clicked = false;
        if (!keypaused[k_id] && key.keyfunction[KE_RELEASED])
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
            {
                processkey(KEYTYPE_MOUSESCROLL, 1, mod_none, KS_DOWN);
                processkey(KEYTYPE_MOUSESCROLL, 1, mod_none, KS_UP);
            }
            if (e.wheel.y < 0)
            {
                processkey(KEYTYPE_MOUSESCROLL, -1, mod_none, KS_DOWN);
                processkey(KEYTYPE_MOUSESCROLL, -1, mod_none, KS_UP);
            }

            break;
        }
    default:
        break;
    }
}

std::vector<inputmanager::keydata>& inputmanager::getkeydata()
{
    return keymap;
}

void inputmanager::addkey(keytype ktype, keys_enum keyenum, int32_t keypress, key_mods kmod, std::string description)
{
    keymap.emplace_back(keydata(description, ktype, keypress));
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

void inputmanager::pausekeyfunctionsexcept(std::vector<keys_enum> exceptionkeys)
{
    std::vector<uint32_t> exceptionkeysids;
    for (keys_enum& k : exceptionkeys)
    {
        exceptionkeysids.push_back(keyenumtokeymap[k]);
    }
    for (int a = 0; a < keymap.size(); a++)
    {
        if (std::find(exceptionkeysids.begin(), exceptionkeysids.end(), a) == exceptionkeysids.end())
        {
            keypaused[a] = true;
        }
        else
        {
            keypaused[a] = false;
        }
    }
}

void inputmanager::pauseallkeyfunctions()
{
    std::fill(keypaused.begin(), keypaused.end(), true);
}

void inputmanager::resumeallkeyfunctions()
{
    std::fill(keypaused.begin(), keypaused.end(), false);
}

void inputmanager::pausekeyfunctions()
{
    keyfunctionsactive = false;
}

void inputmanager::unpausekey(keys_enum)
{

}

void inputmanager::resumekeyfunctions()
{
    keyfunctionsactive = true;
}

void inputmanager::initialize()
{
    std::cout << "initializing keys... "; //obs, lag så de kan endres
    addkey(KEYTYPE_KEYBOARD, KEY_ESCAPE, SDL_SCANCODE_ESCAPE, mod_none, "Show menu/Exit menus or inventory");

    addkey(KEYTYPE_MOUSEBUTTON, KEY_SELECT, SDL_BUTTON_LEFT, mod_none, "Use");
    addkey(KEYTYPE_MOUSEBUTTON, KEY_INTERACT, SDL_BUTTON_RIGHT, mod_none, "Interact");

    addkey(KEYTYPE_KEYBOARD, KEY_UP, SDL_SCANCODE_W, mod_none, "Move forward");
    addkey(KEYTYPE_KEYBOARD, KEY_DOWN, SDL_SCANCODE_S, mod_none, "Move backward");
    addkey(KEYTYPE_KEYBOARD, KEY_LEFT, SDL_SCANCODE_A, mod_none, "Strafe left");
    addkey(KEYTYPE_KEYBOARD, KEY_RIGHT, SDL_SCANCODE_D, mod_none, "Strafe right");
    addkey(KEYTYPE_KEYBOARD, KEY_JUMP, SDL_SCANCODE_SPACE, mod_none, "Jump");

    addkey(KEYTYPE_KEYBOARD, KEY_INV, SDL_SCANCODE_I, mod_none, "Show inventory");

    addkey(KEYTYPE_KEYBOARD, KEY_TOGGLEFLYING, SDL_SCANCODE_F, mod_none, "Toggle flying");
    addkey(KEYTYPE_KEYBOARD, KEY_TOGGLEINFOBOX, SDL_SCANCODE_M, mod_none, "Toggle infobox");
    addkey(KEYTYPE_KEYBOARD, KEY_RUNNING, SDL_SCANCODE_LSHIFT, mod_none, "Hold to run");

    addkey(KEYTYPE_KEYBOARD, KEY_1, SDL_SCANCODE_1, mod_none, "Selection 1");
    addkey(KEYTYPE_KEYBOARD, KEY_2, SDL_SCANCODE_2, mod_none, "Selection 2");
    addkey(KEYTYPE_KEYBOARD, KEY_3, SDL_SCANCODE_3, mod_none, "Selection 3");
    addkey(KEYTYPE_KEYBOARD, KEY_4, SDL_SCANCODE_4, mod_none, "Selection 4");
    addkey(KEYTYPE_KEYBOARD, KEY_5, SDL_SCANCODE_5, mod_none, "Selection 5");
    addkey(KEYTYPE_KEYBOARD, KEY_6, SDL_SCANCODE_6, mod_none, "Selection 6");
    addkey(KEYTYPE_KEYBOARD, KEY_7, SDL_SCANCODE_7, mod_none, "Selection 7");
    addkey(KEYTYPE_KEYBOARD, KEY_8, SDL_SCANCODE_8, mod_none, "Selection 8");
    addkey(KEYTYPE_KEYBOARD, KEY_9, SDL_SCANCODE_9, mod_none, "Selection 9");
    addkey(KEYTYPE_KEYBOARD, KEY_0, SDL_SCANCODE_0, mod_none, "Selection 10");

    addkey(KEYTYPE_MOUSESCROLL, KEY_ZOOMIN, 1, mod_none, "Decrease selection");
    addkey(KEYTYPE_MOUSESCROLL, KEY_ZOOMOUT, -1, mod_none, "Increase selection");

    for (int a =0 ; a < keymap.size(); a++)
        keypaused.push_back(false);

    std::cout << "done\n";
}

glm::ivec2 inputmanager::getcenterpos()
{
    return glm::ivec2(settings::getisetting(settings::SET_SCREENX)/2, settings::getisetting(settings::SET_SCREENY)/2);
}

void inputmanager::hidemouse()//hides and locks mouse
{
    if (!ismousehidden())
    {
        SDL_ShowCursor(SDL_DISABLE);
        mousehidden = true;
        //inputmanager::mousetrappos = inputmanager::getcursorpos();
        glm::ivec2 cent = getcenterpos();
        cursorpos = cent;
        deltamove = glm::ivec2(0,0);
        cursorjusthidden = true;
        SDL_WarpMouseInWindow(windowmanager::sdlwindow, cent.x, cent.y);
    }
}

void inputmanager::showmouse()
{
    if (ismousehidden())
    {
        SDL_ShowCursor(SDL_ENABLE);
        mousehidden = false;
        cursorjusthidden = false;
    }
}

bool inputmanager::ismousehidden()
{
    return mousehidden;
}

void inputmanager::logcursorpos()
{
    if (!cursorjusthidden)
    {
        glm::ivec2 cursorposold = cursorpos;
        SDL_GetMouseState(&cursorpos.x, &cursorpos.y);

        //std::cout << cursorpos.x << " - " << cursorpos.y << " -- " << ismousehidden() << "\n";

        deltamove = cursorpos - cursorposold;

        if (inputmanager::ismousehidden()) //mus låst
        {
            glm::ivec2 cent = getcenterpos();
            deltamove = cursorpos - cent;
            cursorpos = cent;
            SDL_WarpMouseInWindow(windowmanager::sdlwindow, cent.x, cent.y);
        }
    }
    cursorjusthidden = false;
}

glm::ivec2 inputmanager::getcursorpos()
{
    return cursorpos;
}

glm::ivec2 inputmanager::getmousedelta()
{
    return deltamove;
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

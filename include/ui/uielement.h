#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "settings.h"
#include "uicontroller.h"
#include "uiwindow.h"

namespace uielement
{
    void resetcounter();

    void sliderint(int from, int to, int& into, int division = 0);

    void setposition(int x, int y);

    std::string counterstr();

    bool button(std::string text, glm::vec2 pos, glm::ivec2 buttonsize, bool disabled = false);
    bool buttonheld(std::string text, glm::vec2 pos, glm::ivec2 buttonsize);

    void beginwindow(std::string windowtitle, glm::vec2 windowpos, glm::vec2 windowsize, bool titlebar = false, bool scrollbar = false, bool background = true);
    void endwindow();

    //void inputtext();

    void text(std::string text, glm::vec2 pos);
    void text(std::string text);
    void centertext(std::string text, int y, int winwidth = 0);

    void setcursorpos(int cx, int cy);

    void addrect(glm::vec2 start, glm::vec2 rectsize, glm::vec3 col);

    void checkbox(bool &checked, glm::vec2 position);
}

#endif // UIELEMENT_H

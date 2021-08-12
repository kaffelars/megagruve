#include "consts.h"
#include "escbox.h"

namespace escbox
{

}

escbox::selection escbox::showescbox()
{
    int space = (settings::getscreeny() - 600) / 2;

    uielement::beginwindow("escb", glm::vec2(uicontroller::getcenterx(400.0f), space), glm::vec2(400, 600));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    float centerx = uicontroller::getwcenterx(300.0f, 400.0f);

    selection toreturn = selection::NONE;

    if (uielement::button("back to game", glm::vec2(centerx, 50.0f), glm::vec2(300.0f, 50.0f))) toreturn = selection::BACK;
    if (uielement::button("settings", glm::vec2(centerx, 200.0f), glm::vec2(300.0f, 50.0f))) toreturn = selection::SETTINGS;
    if (uielement::button("back to menu", glm::vec2(centerx, 400.0f), glm::vec2(300.0f, 50.0f))) toreturn = selection::MENU;
    if (uielement::button("quit", glm::vec2(centerx, 500.0f), glm::vec2(300.0f, 50.0f))) toreturn = selection::QUIT;

    uielement::endwindow();

    return toreturn;
}

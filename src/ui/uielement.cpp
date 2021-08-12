#include "consts.h"
#include "uielement.h"

namespace uielement
{
    namespace
    {
        int activefont = 0;
        int counter = 0;
        bool windowbegun = false;
        glm::vec2 curwindowsize = glm::vec2(0.0f);
    }
}

void uielement::resetcounter()
{
    counter = 0;
}

void uielement::sliderint(int from, int to, int& into, int division)
{
    std::string crab = "##slider"+counterstr();
    ImGui::SliderInt(crab.c_str(), &into, from, to);
    if (division)
    {
        into /= division;
        into *= division;
    }
    //ImGui::SliderInt(crab.c_str(), &into, from, to);
}

std::string uielement::counterstr()
{
    counter++;
    return std::to_string(counter-1);
}

void uielement::setposition(int x, int y)
{
    ImGui::SetCursorPosX(x);
    ImGui::SetCursorPosY(y);
}


void uielement::text(std::string text, glm::vec2 pos)
{
    setposition(pos.x, pos.y);

    ImGui::Text(text.c_str());
}

void uielement::centertext(std::string text, int y, int winwidth)
{
    if (winwidth == 0) winwidth = settings::getscreenx();

    setposition(uicontroller::getwcenterx(ImGui::CalcTextSize("text", nullptr).x, winwidth), y);
    ImGui::Text(text.c_str());
}

void uielement::text(std::string text)
{
    ImGui::Text(text.c_str());
}


bool uielement::button(std::string text, glm::vec2 pos, glm::ivec2 buttonsize, bool disabled) //negative pos = centered
{
    if (disabled)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
    }

    setposition(pos.x, pos.y);

    if (disabled)
    {
        ImGui::Button(text.c_str(), ImVec2(buttonsize.x, buttonsize.y));
        ImGui::PopStyleVar();
        return false;
    }
    else
    {
        return ImGui::Button(text.c_str(), ImVec2(buttonsize.x, buttonsize.y));
    }
}

void uielement::checkbox(bool &checked, glm::vec2 position)
{
    setposition(position.x, position.y);

    std::string flepsi = "##c" + counterstr();

    ImGui::Checkbox(flepsi.c_str(), &checked);
}

void uielement::addrect(glm::vec2 rectstart, glm::vec2 rectend, glm::vec3 col)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRectFilled(ImVec2(rectstart.x, rectstart.y), ImVec2(rectend.x, rectend.y), IM_COL32(col.r, col.g, col.b, 255));
}

void uielement::setcursorpos(int cx, int cy)
{
    ImGui::SetCursorPosX(cx);
    ImGui::SetCursorPosY(cy);
}


bool uielement::buttonheld(std::string text, glm::vec2 pos, glm::ivec2 buttonsize)
{
    uielement::button(text, pos, buttonsize);

    return ImGui::IsItemActive();
}


void uielement::beginwindow(std::string windowtitle, glm::vec2 windowpos, glm::vec2 windowsize, bool titlebar, bool scrollbar, bool background)
{
    ImGuiWindowFlags window_flags = 0;
    if (!titlebar) window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (!scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoNav;
    if (!background) window_flags |= ImGuiWindowFlags_NoBackground;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    //style

    ImGui::SetNextWindowPos(ImVec2(windowpos.x, windowpos.y));
    ImGui::Begin(windowtitle.c_str(), NULL, window_flags);
    ImGui::SetWindowSize(ImVec2(windowsize.x, windowsize.y));

    uicontroller::changefont(uicontroller::FONT_NORMAL);

    windowbegun = true;//kan dette bli fucked med windows i windows? går det an i utgangspunktet?
    curwindowsize = windowsize;
}

void uielement::endwindow()
{
    if (uicontroller::activefont > 0)
    {
        uicontroller::popfont();
        uicontroller::activefont = 0;
    }

    ImGui::End();
    windowbegun = false;
}

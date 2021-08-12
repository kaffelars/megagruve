#include "consts.h"
#include "uiwindow.h"

namespace uiwindow
{
    //hest e best
}



void uiwindow::progresswindow(std::string text, float progress)
{
    uielement::beginwindow("ptexto", glm::vec2(uicontroller::getcenterx(300.0f), 400), glm::vec2(300.0f, 100.0f));

    ImGui::Text(text.c_str());

    ImGui::ProgressBar(progress, ImVec2(280.0f, 30.0f));

    uielement::endwindow();
}

void uiwindow::tipwindow(std::string text)
{
    uielement::beginwindow("tiptexto", glm::vec2(uicontroller::getcenterx(1000.0f), uicontroller::ypos(-100.0f)), glm::vec2(1000.0f, 100.0f));

    ImGui::Text(text.c_str());

    uielement::endwindow();
}

void uiwindow::textwindow(std::string text)
{
    uielement::beginwindow("texto", glm::vec2(uicontroller::getcenterx(300.0f), 400), glm::vec2(300.0f, 40.0f));

    ImGui::Text(text.c_str());

    uielement::endwindow();
}

void uiwindow::debugwindow(float a, float b, float c)
{
    uielement::beginwindow("debugwind", glm::vec2(0.0f), glm::vec2(300.0f, 40.0f));

    ImGui::Text("%f, %f, %f", a, b, c);

    uielement::endwindow();
}

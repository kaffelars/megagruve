#ifndef UIWINDOW_H
#define UIWINDOW_H

#include "settings.h"
#include "uicontroller.h"
#include "uielement.h"

namespace uiwindow
{
    void debugwindow(float a, float b, float c);

    void textwindow(std::string text);
    void progresswindow(std::string text, float progress);
    void tipwindow(std::string text);
};

#endif // UIWINDOW_H

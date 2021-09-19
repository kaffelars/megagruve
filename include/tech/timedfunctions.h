#ifndef TIMEDFUNCTIONS_H
#define TIMEDFUNCTIONS_H


namespace timedfunctions
{
    void addtimedfunction(float timer, std::function<void()> timedfunc);
    void update();
};

#endif // TIMEDFUNCTIONS_H

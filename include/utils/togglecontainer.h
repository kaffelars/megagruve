#ifndef TOGGLECONTAINER_H
#define TOGGLECONTAINER_H


class togglecontainer
{
    public:
        togglecontainer();
        virtual ~togglecontainer();

        static void istoggled(int toggleid);
        static void toggleon(int toggleid);
        static void toggleoff(int toggleid);

        static void toggle(int toggleid);

    protected:

    private:
        static bool toggles[5];
};

#endif // TOGGLECONTAINER_H

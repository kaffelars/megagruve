#ifndef UIINGAME_H
#define UIINGAME_H



namespace uiingame
{
    void rendergameui();
    void initialize();

    void updateactionbaritems(bool updatebar);

    void updateinventory(bool update, bool alsobg);

    void hover();
    void click();
    void renderiteminfobox();

    int32_t getinvitemidbyposition(glm::ivec2 position);

    void toggleinventory();
}


#endif // UIINGAME_H

#ifndef UIINGAME_H
#define UIINGAME_H



namespace uiingame
{
    void rendergameui();
    void initialize();

    void updateactionbaritems(bool updatebar);

    bool showinginventory();
    void refreshui();
    void resetui();

    void toggleinventory(inventorytype invtype = inventorytype::none);
}


#endif // UIINGAME_H

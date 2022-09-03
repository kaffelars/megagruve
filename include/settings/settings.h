#ifndef SETTINGS_H
#define SETTINGS_H

#include "pugixml.hpp"


namespace settings
{
    enum esettings
    {
        SET_SCREENX, SET_SCREENY, SET_FOV, SET_CDIST, SET_AA, SET_TILERES, SET_VSYNC, SET_UISCALE, SET_FILTER, SET_CROSSHAIRSIZE, SET_CROSSHAIR, SET_LANGUAGE, SET_BBOX, SET_MBOX, SET_MAXTHREADS, SET_MOUSESENS
    };

    struct filterinfo
    {
        std::string name;
        glm::mat3x3 filter;
    };

    struct setting
    {
        std::string identifier;
        int type;
        int ivalue;
        float fvalue;
        std::string svalue;
        int group;

        setting(std::string id, int typ, int grp)
        {
            identifier = id;
            type = typ;
            group = grp;
        }
    };

    void loadsettings();
    void savesettings();

    void writedefaultsettings();

    void setisetting(int s, int value);
    void setfsetting(int s, float value);
    void setssetting(int s, std::string value);
    //static void setssetting(int s, std::string value);

    int getisetting(int s);
    float getfsetting(int s);
    std::string getssetting(int s);

    const std::vector<filterinfo>& getfilters();
    int getfilterindex(std::string filtername);
    glm::mat3x3 getfilter(int id);

    //extern std::vector<setting> setts;

    int getscreenx();
    int getscreeny();
    float getuiscale();

    float getfov();
}

#endif // SETTINGS_H

#include "consts.h"
#include "settings.h"

namespace settings
{
    namespace //private
    {
        std::vector<setting> setts;// = {};
    }
}

void settings::loadsettings()
{
    if (!settings::setts.empty()) settings::setts.clear();//renser settings

    //settings den skal lete etter
    setts.emplace_back(setting("screenx", 1, 0));//video
    setts.emplace_back(setting("screeny", 1, 0));
    setts.emplace_back(setting("fov", 1, 0));
    setts.emplace_back(setting("cdist", 1, 0));
    setts.emplace_back(setting("antialias", 1, 0));
    setts.emplace_back(setting("tileres", 1, 0));
    setts.emplace_back(setting("vsync", 1, 0));
    setts.emplace_back(setting("uiscale", 2, 0));
    setts.emplace_back(setting("language", 0, 1)); //game

    pugi::xml_document doc;

    std::string fname = "./data/settings.txt";
    pugi::xml_parse_result result = doc.load_file(fname.c_str());

    std::string settin[2] = {"video", "game"};


    int st = 0;
    for (int a = 0; a < 2; a++)
    {
        auto video = doc.child(settin[a].c_str());
        for (setting& s : setts)
        {
            if (s.group == a)
            {
                std::string str = video.child_value(s.identifier.c_str());
                if (str == "") break;

                if (s.type == 0) s.svalue = str;
                if (s.type == 1) s.ivalue = std::stoi(str);
                if (s.type == 2) s.fvalue = std::stof(str);

                st++;
            }
        }
    }

    if (st != setts.size())
    {
        std::cout << "settings error! ";
    }
}

void settings::writedefaultsettings()
{
    std::cout << "writing default settings... ";
    std::ofstream inifile;
    inifile.open("data/dorf.ini");
    inifile << "screenx" << "\n";
    inifile << "1" << "\n";
    inifile << "1920" << "\n";
    inifile << "screeny" << "\n";
    inifile << "1" << "\n";
    inifile << "1147" << "\n";
    inifile << "fov" << "\n";
    inifile << "1" << "\n";
    inifile << "75" << "\n";
    inifile << "cdist" << "\n";
    inifile << "1" << "\n";
    inifile << "13" << "\n";
    inifile << "aa" << "\n";
    inifile << "1" << "\n";
    inifile << "5" << "\n";
    inifile << "tileres" << "\n";
    inifile << "1" << "\n";
    inifile << "64" << "\n";
    inifile << "vsync" << "\n";
    inifile << "1" << "\n";
    inifile << "1" << "\n";
    inifile << "uiscale" << "\n";
    inifile << "2" << "\n";
    inifile << "1.0" << "\n";
    inifile << "-1" << "\n";

    inifile.close();
}

void settings::savesettings()
{
    if (!settings::setts.empty())
    {
        std::ofstream inifile;
        inifile.open("data/settings.txt");

        std::string settin[2] = {"video", "game"};

        for (int a = 0; a < 2; a++)
        {
            inifile << "<" << settin[a] << ">\n";
            for (setting& s: settings::setts)
            {
                if (s.group == a)
                {
                    inifile << "<" << s.identifier << ">";
                    if (s.type == 0) inifile << s.svalue;
                    if (s.type == 1) inifile << s.ivalue;
                    if (s.type == 2) inifile << s.fvalue;
                    inifile << "</" << s.identifier << ">";
                    inifile << "\n";
                }
            }
            inifile << "</" << settin[a] << ">\n";
        }

        inifile.close();
    }
}

void settings::setisetting(int s, int value)
{
    if (!settings::setts.empty())
    {
        settings::setts[s].ivalue = value;
        settings::savesettings();
    }
}

void settings::setssetting(int s, std::string value)
{
    if (!settings::setts.empty())
    {
        settings::setts[s].svalue = value;
        settings::savesettings();
    }
}

void settings::setfsetting(int s, float value)
{
    if (!settings::setts.empty())
    {
        settings::setts[s].fvalue = value;
        settings::savesettings();
    }
}

int settings::getisetting(int s)
{
    if (s < settings::setts.size())
        return settings::setts[s].ivalue;

    return -1;
}

float settings::getfsetting(int s)
{
    if (s < settings::setts.size())
        return settings::setts[s].fvalue;

    return -1;
}

std::string settings::getssetting(int s)
{
    if (s < settings::setts.size())
        return settings::setts[s].svalue;

    return "";
}

//functions for lazy people
int settings::getscreenx()
{
    return settings::getisetting(SET_SCREENX);
}

int settings::getscreeny()
{
    return settings::getisetting(SET_SCREENY);
}

float settings::getuiscale()
{
    return settings::getfsetting(SET_UISCALE);
}

float settings::getfov()
{
    return glm::radians((float)settings::getisetting(SET_FOV));
}

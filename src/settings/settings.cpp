#include "consts.h"
#include "settings.h"

namespace settings
{
    std::vector<setting> setts;// = {};
    std::vector<filterinfo> filters;
    void loadfilters();
}

void settings::loadsettings()
{
    if (!settings::setts.empty()) settings::setts.clear();//renser settings

    //settings to look for - make more flexible
    setts.emplace_back(setting("screenx", 1, 0));//video
    setts.emplace_back(setting("screeny", 1, 0));
    setts.emplace_back(setting("fov", 1, 0));
    setts.emplace_back(setting("cdist", 1, 0));
    setts.emplace_back(setting("antialias", 1, 0));
    setts.emplace_back(setting("tileres", 1, 0));
    setts.emplace_back(setting("vsync", 1, 0));
    setts.emplace_back(setting("uiscale", 2, 0));
    setts.emplace_back(setting("filter", 0, 0));
    setts.emplace_back(setting("crosshairsize", 1, 0));
    setts.emplace_back(setting("crosshair", 0, 0));
    setts.emplace_back(setting("language", 0, 1));//game
    setts.emplace_back(setting("bbox", 1, 1));
    setts.emplace_back(setting("mbox", 1, 1));
    setts.emplace_back(setting("maxthreads", 1, 1));
    setts.emplace_back(setting("mousesens", 1, 1));

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

    if (st != static_cast<int>(setts.size()))
    {
        std::cout << "settings error!\n";
    }

    loadfilters();
}

void settings::loadfilters()
{
    if (!filters.empty()) filters.clear();

    pugi::xml_document doc;

    std::string fname = "./data/filters.txt";
    pugi::xml_parse_result result = doc.load_file(fname.c_str());

    if (result)
    {
        for (pugi::xml_node p = doc.child("filter"); p; p = p.next_sibling("filter"))
        {
            filterinfo f;
            f.name = p.attribute("name").value();

            f.filter = glm::mat3x3(1.0f);
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    std::string row = "row"+std::to_string(y+1);
                    std::string col = "val"+std::to_string(x+1);
                    f.filter[y][x] = p.child(row.c_str()).attribute(col.c_str()).as_float();
                }
            }
            filters.push_back(f);

        }
    }
    else
    {
        std::cout << "filter loading error!\n\n\n\n\n\n";
    }
}

const std::vector<settings::filterinfo>& settings::getfilters()
{
    return filters;
}

int settings::getfilterindex(std::string filtername)
{
    if (filtername == "none") return -1;

    int index = 0;
    for (filterinfo& f: filters)
    {
        if (f.name == filtername) return index;
        index++;
    }
    return -1;
}

glm::mat3x3 settings::getfilter(int id)
{
    return filters[id].filter;
}

void settings::writedefaultsettings()
{

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

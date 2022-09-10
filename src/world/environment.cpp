#include "consts.h"
#include "environment.h"

#include "timekeeper.h"
#include "shadercontroller.h"
#include "maincharcontroller.h"
#include "camera.h"
#include "skybox.h"
#include "texturemanager.h"
#include "utils.h"
#include "particlemanager.h"
#include "randfunc.h"

namespace environment
{
    float currenttime = 9.0f; //0 - 24
    float timespeed = 1.0f;

    bool timemoving = true;

    float cloudposition = 0.0f;
    float cloudcover = 0.2f;

    float wind = 0.1f;

    GLuint starsid;
    bool starsinitialized = false;
    void initializestars();

    uint32_t raintexid = 0;

    rgbcolor fogcolors[9] = {
    rgbcolor{0.0f, 0.0f, 0.1f}, //0
    rgbcolor{0.0f, 0.0f, 0.1f}, //3
    rgbcolor{0.6f, 0.6f, 0.6f}, //6
    rgbcolor{0.9f, 0.9f, 0.9f}, //9
    rgbcolor{1.0f, 1.0f, 1.0f}, //12
    rgbcolor{1.0f, 1.0f, 1.0f}, //15
    rgbcolor{0.6f, 0.6f, 0.6f}, //18
    rgbcolor{0.0f, 0.0f, 0.1f}, //21
    rgbcolor{0.0f, 0.0f, 0.1f}}; //24

    rgbcolor skycolors[9] = {
    rgbcolor{0.0f, 0.0f, 0.0f}, //0
    rgbcolor{0.0f, 0.0f, 0.0f}, //3
    rgbcolor{0.2f, 0.0f, 0.4f}, //6
    rgbcolor{0.2f, 0.4f, 0.8f}, //9
    rgbcolor{0.2f, 0.5f, 0.9f}, //12
    rgbcolor{0.2f, 0.5f, 0.9f}, //15
    rgbcolor{0.3f, 0.2f, 0.4f}, //18
    rgbcolor{0.0f, 0.0f, 0.2f}, //21
    rgbcolor{0.0f, 0.0f, 0.0f}}; //24

    rgbcolor suncolors[9] = {
    rgbcolor{0.0f, 0.0f, 0.1f}, //0
    rgbcolor{0.0f, 0.0f, 0.1f}, //3
    rgbcolor{0.9f, 0.0f, 0.1f}, //6
    rgbcolor{0.9f, 0.9f, 0.9f}, //9
    rgbcolor{1.0f, 1.0f, 1.0f}, //12
    rgbcolor{1.0f, 1.0f, 1.0f}, //15
    rgbcolor{1.0f, 0.2f, 0.2f}, //18
    rgbcolor{0.0f, 0.0f, 0.1f}, //21
    rgbcolor{0.0f, 0.0f, 0.1f}}; //24

    float stars[9] =
    {
        1.0f,
        1.0f,
        0.3f,
        0.0f,
        0.0f,
        0.0f,
        0.3f,
        1.0f,
        1.0f,
    };


    float getcloudfactor();
}

void environment::sendrendererdata()
{
    rgbcolor fogcolor = getfogcolor();
    glm::vec2 fogdist;
    direction sundir = getsundir();//environment.getsundir();
    rgbcolor suncolor = getsuncolor();//environment.getsuncolor();

    fogdist.y = settings::getisetting(settings::SET_CDIST) * (chunkwidth);
    float cloudfactor = getcloudfactor();
    fogdist.y /= (1.0f + 3.0f * cloudfactor);
    fogdist.x = (fogdist.y / (3.0f));
    fogdist.x -= fogdist.x * cloudfactor * 4.0f;

    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform2f(shadercontroller::getuniformid("fogdist"), fogdist.x, fogdist.y);
    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
}

float environment::getcloudfactor()
{
    float cloudfactor = (cloudcover - 0.5f) * 2.0f;
    if (cloudfactor < 0.0f) cloudfactor = 0.0f;
    return cloudfactor;
}

void environment::changetime(float timetochange)
{
    currenttime += timetochange;
    if (currenttime > 24.0f) currenttime -= 24.0f;
}

void environment::resetenvironment()
{
    currenttime = 9.0f;
    cloudposition = 0.0f;
    cloudcover = 0.2f;
    wind = 0.1f;
}

void environment::initialize()
{
    raintexid = texturemanager::gettiletexturenumber("rain");
    resetenvironment();
    if (!starsinitialized) initializestars();
}

void environment::bindstarstexture(int texid)
{
    glActiveTexture(GL_TEXTURE0+texid);
    glBindTexture(GL_TEXTURE_CUBE_MAP, starsid);
}

void environment::initializestars()
{
    glGenTextures(1, &starsid);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, starsid);

    std::vector<uint8_t> stars[6];

    for (int a = 0; a < 6; a++)
    {
        for (int x = 0; x < 512; x++)
        {
            for (int y = 0; y < 512; y++)
            {
                stars[a].push_back(0);
            }
        }
    }

    int ex, ey, p;

    for (float a = 1; a < 1000; a++)
    {
        float ex = randfunc::noise(a * 6.49f, a * 2.11f, 0.013f);
        float ey = randfunc::noise(a * 2.91f, a * 5.77f, 0.013f);
        float ez = randfunc::noise(a * 2.121f, a * 1.31f, 0.013f);

        glm::vec3 sv = glm::normalize(glm::vec3(ex, ey, ez));

        glm::vec3 asv;
        asv.x = std::fabs(sv.x);
        asv.y = std::fabs(sv.y);
        asv.z = std::fabs(sv.z);

        p = -1;

        glm::vec2 exey = glm::vec2(0);

        if (asv.x > asv.y && asv.x > asv.z)
        {
            exey = glm::vec2(sv.z, sv.y);

            if (sv.x > 0.0f)
                p = 0;
            else
                p = 1;
        }

        if (asv.y > asv.x && asv.y > asv.z)
        {
            exey = glm::vec2(sv.x, sv.z);

            if (sv.y > 0.0f)
                p = 2;
            else
                p = 3;
        }

        if (asv.z > asv.x && asv.z > asv.y)
        {
            exey = glm::vec2(sv.x, sv.y);
            if (sv.z > 0.0f)
                p = 4;
            else
                p = 5;
        }

        exey = glm::normalize(exey);

        ex = 256 - 256 * exey.x;
        ey = 256 - 256 * exey.y;

        float star = (randfunc::noise(234.0f + a * 3.331f, 182.0f + a * 4.97f, 0.023f) + 1.0f) / 2.0f;

        if (p >= 0)
        {
            stars[p][ex + 512*ey] = star*255.0f;
        }
    }

    stars[0][222 + 512*371] = 255;
    stars[0][232 + 512*373] = 255;
    stars[0][240 + 512*365] = 255;
    stars[0][250 + 512*360] = 245;
    stars[0][251 + 512*350] = 255;
    stars[0][265 + 512*349] = 255;
    stars[0][268 + 512*359] = 255;


    //fill
    for (int a = 0; a < 6; a++)
    {
        glTexImage2D(
        GL_TEXTURE_CUBE_MAP_POSITIVE_X + a,
        0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, &stars[a][0]
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    starsinitialized = true;
}

void environment::toggletimemoving()
{
    timemoving = !timemoving;
}

float environment::getcurrenttime()
{
    return currenttime;
}

void environment::changecloudcover(float change)
{
    cloudcover += change;
    utils::clamp(cloudcover, 0.0f, 1.0f);
}

void environment::rain()
{
    //test regn - litt slow
    for (int x = -55; x < 55; x+=2)
    {
        for (int z = -55; z < 55; z+=2)
        {
            if (utils::randint(0, 140) == 2)
            {
                float px = maincharcontroller::getmaincharposition().x + x + ((float)utils::randint(0, 10) / 10.0f);
                float pz = maincharcontroller::getmaincharposition().z + z + ((float)utils::randint(0, 10) / 10.0f);
                particlemanager::addparticle(wposition{px, 0.5f, pz}, velocity(0.0f), raintexid, 10, 4000, 0, 0.7f, true);
            }
        }
    }
}

void environment::updatetime()
{
    if (!timemoving) return;

    currenttime += timekeeper::gettimefactor() * 0.001f * timespeed;

    if (currenttime > 24.0f) currenttime -= 24.0f;

    cloudposition += timekeeper::gettimefactor() * 0.0001f * wind;

    if (cloudposition > 255.0f) cloudposition -= 255.0f;

    if (cloudcover > 0.7f) rain();
}

direction environment::getsundir()
{
    float h = pi_value*2.0f * getcurrenttime() / 24.0f;

    return glm::normalize(direction(sin(h+0.11f), cos(h+pi_value), sin(h+0.31f)/1.7f));
}

rgbcolor environment::getsuncolor()
{
    float curtime = getcurrenttime();

    uint8_t ptone = (curtime / 3);
    uint8_t pttwo = ptone + 1;

    float factor = (curtime - (3.0f * ptone)) / 3.0f;

    rgbcolor suncol = suncolors[ptone] * (1.0f - factor) + suncolors[pttwo] * (factor);

    /*if (cloudcover > 0.5f)
    {
        suncol *= (1.0f - 2.0f * (cloudcover - 0.5f));
    }*/
    suncol *= (1.0f - getcloudfactor());

    return suncol;
}

float environment::getcloudcover()
{
    //cloudcover += 0.0001f;

    return cloudcover;
}

rgbcolor environment::getskycolor()
{
    float curtime = getcurrenttime();

    uint8_t ptone = (curtime / 3);
    uint8_t pttwo = ptone + 1;

    float factor = (curtime - (3.0f * ptone)) / 3.0f;

    return skycolors[ptone] * (1.0f - factor) + skycolors[pttwo] * (factor);
}

float environment::getstars()
{
    float curtime = getcurrenttime();

    uint8_t ptone = (curtime / 3);
    uint8_t pttwo = ptone + 1;

    float factor = (curtime - (3.0f * ptone)) / 3.0f;

    return stars[ptone] * (1.0f - factor) + stars[pttwo] * (factor);
}

rgbcolor environment::getfogcolor()
{
    float curtime = getcurrenttime();

    uint8_t ptone = (curtime / 3);
    uint8_t pttwo = ptone + 1;

    float factor = (curtime - (3.0f * ptone)) / 3.0f;

    float foglight = (1.0f - (1.4f * getcloudfactor()));
    if (foglight < 0.05f) foglight = 0.05f;

    return (fogcolors[ptone] * (1.0f - factor) + fogcolors[pttwo] * (factor)) * foglight;
}

void environment::renderskybox()
{
    shadercontroller::activateshader(shadercontroller::SH_SKY); //skybox shader

    direction sundir = getsundir();
    wposition eyepos = maincharcontroller::getmaincharposition();
    rgbcolor suncolor = getsuncolor();

    float lightfactor = (1.0f - (1.4f * getcloudfactor()));
    if (lightfactor < 0.05f) lightfactor = 0.05f;

    rgbcolor fogcolor = getfogcolor() * (1.0f - lightfactor) + getsuncolor() * lightfactor;
    rgbcolor skycolor = getskycolor();

    texturemanager::bindcloudtexture(0);
    bindstarstexture(1);

    //textureloader::bind2dtexture(0,0);

    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("skycolor"), skycolor.x, skycolor.y, skycolor.z);
    glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
    glUniform3f(shadercontroller::getuniformid("campos"), eyepos.x, eyepos.y, eyepos.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform2f(shadercontroller::getuniformid("cloudcover"), getcloudcover(), cloudposition);
    glUniform1f(shadercontroller::getuniformid("stars"), getstars());

    glUniform1i(shadercontroller::getuniformid("cloudtexture"), 0);
    glUniform1i(shadercontroller::getuniformid("starstexture"), 1);

    skybox::render();
}

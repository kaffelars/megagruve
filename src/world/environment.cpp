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

namespace environment
{
    float currenttime = 9.0f; //0 - 24
    float timespeed = 1.0f;

    bool timemoving = true;

    float cloudposition = 0.0f;
    float cloudcover = 0.2f;

    float wind = 0.1f;

    uint32_t raintexid = 0;
}

void environment::initialize()
{
    raintexid = texturemanager::gettiletexturenumber("rain");
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
            if (utils::randint(0, 140) ==2)
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
    rgbcolor suncolmax = rgbcolor(1.8f);
    direction sundir = getsundir();
    rgbcolor suncol = rgbcolor(0.0f);

    sundir.y += 0.2f;

    utils::clamp(sundir.y, 0.0f, 1.0f);

    if (sundir.y > 0.0f)
    {
        if (sundir.y < 0.5f)
        {
            suncol.r = 0.9f;
            suncol.g = suncolmax.g*sundir.y;
            suncol.b = suncolmax.b*sundir.y;

            float factor = glm::clamp((sundir.y-0.3f) / 0.2f, 0.0f, 1.0f);

            suncol.g *= factor;//*factor;
            suncol.b *= factor;//*factor;
            //suncol.r *= factor;
        }
        else
        {
            suncol = suncolmax * sundir.y;
        }
    }

    utils::clamp(suncol, 0.0f, 1.0f);

    if (cloudcover > 0.5f)
    {
        suncol *= (1.0f - 2.0f * (cloudcover - 0.5f));
    }

    return suncol;
}

float environment::getcloudcover()
{
    //cloudcover += 0.0001f;

    return cloudcover;
}

rgbcolor environment::getskycolor()
{
    rgbcolor skycolor = glm::vec3(0.2f, 0.5f, 0.9f);

    direction sundir = getsundir();
    sundir.y += 0.5f;
    sundir.y = glm::clamp(sundir.y, 0.0f, 1.0f);

    return skycolor * sundir.y;
}

rgbcolor environment::getfogcolor()
{
    /*rgbcolor skycolor = getskycolor();

    skycolor.r = skycolor.r*5.0f;
    skycolor.g = skycolor.g*3.0f;
    skycolor.b = skycolor.b*1.5f;*/

    rgbcolor skycolor = getsuncolor();

    return skycolor;
}

void environment::renderskybox()
{
    shadercontroller::activateshader(shadercontroller::SH_SKY); //skybox shader

    direction sundir = getsundir();
    wposition eyepos = maincharcontroller::getmaincharposition();
    rgbcolor suncolor = getsuncolor();
    rgbcolor fogcolor = getfogcolor();
    rgbcolor skycolor = getskycolor();

    texturemanager::bindcloudtexture(0);

    //textureloader::bind2dtexture(0,0);

    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("skycolor"), skycolor.x, skycolor.y, skycolor.z);
    glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
    glUniform3f(shadercontroller::getuniformid("campos"), eyepos.x, eyepos.y, eyepos.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform2f(shadercontroller::getuniformid("cloudcover"), getcloudcover(), cloudposition);

    skybox::render();
}

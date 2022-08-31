#include "consts.h"
#include "renderer.h"

#include "timekeeper.h"
#include "particlemanager.h"
#include "settings.h"

namespace renderer
{
    glm::vec4 mousedata = glm::vec4(0);
    hposition renderoffset = hposition{0.0f, 0.0f};

    float timer = 0.0f;
    int filterid = -1;
    glm::mat3x3 renderfilter = glm::mat3x3(1.0f);
}

glm::vec4& renderer::getmousedata()
{
    return mousedata;
}

void renderer::updaterenderfilter()
{
    filterid = settings::getfilterindex(settings::getssetting(settings::SET_FILTER));

    if (filterid >= 0)
        renderfilter = settings::getfilter(filterid);
}

void renderer::rendergame()
{
    timer += timekeeper::getdeltatime() / 1000.0f;
    if (timer > 31415.0f) timer -= 31415.0f;

    int screenx = settings::getisetting(settings::SET_SCREENX);
    int screeny = settings::getisetting(settings::SET_SCREENY);

    //rendering to gbuffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffercontroller::tilebuffer);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));

    //render tiles ------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilMask(0xFF);

    direction sundir = environment::getsundir();//environment.getsundir();
    rgbcolor suncolor = environment::getsuncolor();//environment.getsuncolor();
    rgbcolor fogcolor = environment::getfogcolor();//environment.getfogcolor();
    wposition campos = maincharcontroller::getmaincharcamera();
    float mcharlight = maincharcontroller::getmcharlight();

    shadercontroller::activateshader(shadercontroller::SH_MAIN);
    glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
    glUniform3f(shadercontroller::getuniformid("campos"), campos.x, campos.y, campos.z);
    glUniform1f(shadercontroller::getuniformid("mcharlight"), mcharlight);

    texturemanager::bindtiletextures(0);

    chunkcontroller::renderchunks(maincharcontroller::getviewdir(), maincharcontroller::getmaincharcamera());
    //------------------

    //destroy block
    maincharcontroller::renderdestroyblock();
    //

    //particles
    if (particlemanager::anyactiveparticles())
    {
        shadercontroller::activateshader(shadercontroller::SH_PARTICLE);
        glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
        glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
        glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
        glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
        glUniform3f(shadercontroller::getuniformid("campos"), campos.x, campos.y, campos.z);
        glUniform1f(shadercontroller::getuniformid("mcharlight"), mcharlight);

        particlemanager::renderparticles();
    }
    //

    //render sky -----
    glDisable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 0, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    environment::renderskybox();
    //----------------



    //tar 0.4 ms ... ------------------
    //reading pixel data!! alert!
    //https://www.roxlu.com/2014/048/fast-pixel-transfers-with-pixel-buffer-objects ?
    /*glm::ivec2 mousepos = inputmanager::getcursorpos();
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glReadPixels(settings::getisetting(settings::SET_SCREENX)/2,settings::getisetting(settings::SET_SCREENY)/2,1,1,GL_RGBA, GL_FLOAT, &mousedata);
    glReadBuffer(0);*/ //endret til blocktracer
    // --------------------------------



    //---------------------------------
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffercontroller::tilebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffercontroller::postbuffer);
    //glBlitFramebuffer(0, 0, screenx, screeny, 0, 0, screenx, screeny, GL_STENCIL_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, screenx, screeny, 0, 0, screenx, screeny, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    //rendering to post buffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffercontroller::postbuffer);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT
    //glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);


    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_KEEP, GL_REPLACE);


    //water
    shadercontroller::activateshader(shadercontroller::SH_WATER);
    glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
    glUniform3f(shadercontroller::getuniformid("campos"), campos.x, campos.y, campos.z);
    glUniform1i(shadercontroller::getuniformid("gbuf_rgb"), 0);
    glUniform1i(shadercontroller::getuniformid("gbuf_pos"), 1);
    glUniform1i(shadercontroller::getuniformid("gbuf_norm"), 2);
    glUniform1i(shadercontroller::getuniformid("tex"), 3);
    glUniform1f(shadercontroller::getuniformid("timer"), timer);
    glUniform1f(shadercontroller::getuniformid("mcharlight"), mcharlight);

    framebuffercontroller::activatebuffertextures();
    texturemanager::bindtiletextures(3);

    chunkcontroller::renderwater();
    //-----

    //scene (tiles et al)
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glDisable(GL_DEPTH_TEST);
    shadercontroller::activateshader(shadercontroller::SH_SCENE);

    framebuffercontroller::activatebuffertextures();

    glUniform1i(shadercontroller::getuniformid("gbuf_rgb"), 0);
    glUniform1i(shadercontroller::getuniformid("gbuf_pos"), 1);
    glUniform1i(shadercontroller::getuniformid("gbuf_norm"), 2);

    float filter = 0.0f;
    if (maincharcontroller::isunderwater()) filter = 1.0f;
    glUniform1f(shadercontroller::getuniformid("underwater"), filter);

    scenequad::render();
    framebuffercontroller::deactivatebuffertextures();
    //--------------


    //render selection
    if (maincharcontroller::getselectionmode() != maincharcontroller::SEL_NONE)
    {
        glDisable(GL_DEPTH_TEST);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        shadercontroller::activateshader(shadercontroller::SH_LINE);
        glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));

        maincharcontroller::renderselection();
    }


    //final rendering to screen
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));

    if (filterid == -1)
    {
        shadercontroller::activateshader(shadercontroller::SH_PP);
    }
    else
    {
        shadercontroller::activateshader(shadercontroller::SH_PPFILTER);
        glUniformMatrix3fv(shadercontroller::getuniformid("em"), 1, GL_FALSE, &(renderfilter[0][0]));
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebuffercontroller::postrgb);



    //lightc.bindstexture(1);

    scenequad::render();



    //render ingame ui
    uiingame::rendergameui();
}

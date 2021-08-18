#include "consts.h"
#include "renderer.h"

namespace renderer
{
    glm::vec4 mousedata = glm::vec4(0);
    hposition renderoffset = hposition{0.0f, 0.0f};
}

glm::vec4& renderer::getmousedata()
{
    return mousedata;
}

void renderer::rendergame()
{
    int screenx = settings::getisetting(settings::SET_SCREENX);
    int screeny = settings::getisetting(settings::SET_SCREENY);

    //rendering to gbuffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffercontroller::tilebuffer);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilMask(0xFF);

    direction sundir = environment::getsundir();//environment.getsundir();
    rgbcolor suncolor = environment::getsuncolor();//environment.getsuncolor();
    rgbcolor fogcolor = environment::getfogcolor();//environment.getfogcolor();
    wposition campos = maincharcontroller::getmaincharposition();

    shadercontroller::activateshader(shadercontroller::SH_MAIN);
    glUniformMatrix4fv(shadercontroller::getuniformid("pv"), 1, GL_FALSE, &(camera::getpvmatrix()[0][0]));
    glUniform3f(shadercontroller::getuniformid("sundir"), sundir.x, sundir.y, sundir.z);
    glUniform3f(shadercontroller::getuniformid("fogcolor"), fogcolor.x, fogcolor.y, fogcolor.z);
    glUniform3f(shadercontroller::getuniformid("suncolor"), suncolor.x, suncolor.y, suncolor.z);
    glUniform3f(shadercontroller::getuniformid("campos"), campos.x, campos.y, campos.z);

    texturemanager::bindtiletextures(0);

    chunkcontroller::renderchunks(maincharcontroller::getviewdir(), maincharcontroller::getmaincharposition());

    maincharcontroller::renderdestroyblock();


    //tar 0.4 ms ... ------------------
    //reading pixel data!! alert!
    glm::ivec2 mousepos = inputmanager::getcursorpos();
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glReadPixels(settings::getisetting(settings::SET_SCREENX)/2,settings::getisetting(settings::SET_SCREENY)/2,1,1,GL_RGBA, GL_FLOAT, &mousedata);
    glReadBuffer(0);
    // --------------------------------


    //---------------------------------
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffercontroller::tilebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffercontroller::postbuffer);
    glBlitFramebuffer(0, 0, screenx, screeny, 0, 0, screenx, screeny, GL_STENCIL_BUFFER_BIT, GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    //rendering to post buffer
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffercontroller::postbuffer);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);






    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    shadercontroller::activateshader(shadercontroller::SH_SCENE);

    glUniform1i(shadercontroller::getuniformid("gbuf_rgb"), 0);
    glUniform1i(shadercontroller::getuniformid("gbuf_pos"), 1);
    glUniform1i(shadercontroller::getuniformid("gbuf_norm"), 2);
    //glUniform1i(shadercontroller::getshader(1).texid[3], 3);
    //glUniform1i(shadercontroller::getshader(1).texid[4], 4);

    framebuffercontroller::activatebuffertextures();
    //lightc.bindstexture(3);
    //chunkc.bindstexture(4);

    scenequad::render();
    framebuffercontroller::deactivatebuffertextures();

    glStencilFunc(GL_EQUAL, 0, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    environment::renderskybox();

    //environment.renderskybox(camera);

    //sdlgl.framebufc.renderscenequad();

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
    glViewport(0, 0, settings::getisetting(settings::SET_SCREENX), settings::getisetting(settings::SET_SCREENY));

    shadercontroller::activateshader(shadercontroller::SH_PP);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebuffercontroller::postrgb);

    //lightc.bindstexture(1);

    scenequad::render();



    //render ingame ui
    uiingame::rendergameui();
}

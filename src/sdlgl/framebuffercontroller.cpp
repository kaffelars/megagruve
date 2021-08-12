#include "consts.h"
#include "framebuffercontroller.h"

namespace framebuffercontroller
{
    GLuint tilebuffer, tilepos, tilergb, tilenorm, tiledepth, postdepth, postbuffer, postrgb;
}

void framebuffercontroller::initialize()
{
    setupbuffers();
}


void framebuffercontroller::activatebuffertextures()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tilergb);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tilepos);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tilenorm);
    /*glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, gLight);*/
}

void framebuffercontroller::deactivatebuffertextures()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void framebuffercontroller::activatepostprocessingtextures()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, postrgb);
}

void framebuffercontroller::setupbuffers()
{
    std::cout << "setting up framebuffers\n";
    glActiveTexture(GL_TEXTURE0);
    glGenFramebuffers(1, &tilebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, tilebuffer);

    //ost
    int WIN_WIDTH = settings::getisetting(settings::SET_SCREENX);
    int WIN_HEIGHT = settings::getisetting(settings::SET_SCREENY);

    //rgb + specular

    glGenTextures(1, &tilergb);
    glBindTexture(GL_TEXTURE_2D, tilergb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tilergb, 0);

    //xyz pos + reflect
    glGenTextures(1, &tilepos);
    glBindTexture(GL_TEXTURE_2D, tilepos);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tilepos, 0);

    //xyz normal + ?
    glGenTextures(1, &tilenorm);
    glBindTexture(GL_TEXTURE_2D, tilenorm);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, tilenorm, 0);



    //
    GLuint attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};//, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(3, attachments);

    //GLuint attachments[1] = {GL_COLOR_ATTACHMENT0};//, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};//, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    //glDrawBuffers(1, attachments);

    //depth bøffer
    glGenRenderbuffers(1, &tiledepth);
    glBindRenderbuffer(GL_RENDERBUFFER, tiledepth);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIN_WIDTH, WIN_HEIGHT);
    //depth OG stencil
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, tiledepth);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, tiledepth);

    //
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "error i tryn - framebuffer error" <<std::endl;
    else std::cout << "bra tilebuffer-framebuffer satt opp " <<std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //1 her tegnes scenen for post processing
    glGenFramebuffers(1, &postbuffer);//husk at den også må slettes
    glBindFramebuffer(GL_FRAMEBUFFER, postbuffer);

    glGenTextures(1, &postrgb);
    glBindTexture(GL_TEXTURE_2D, postrgb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIN_WIDTH, WIN_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);//16f fordi hdr
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postrgb, 0);

    attachments[0] = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, attachments);

    //depth bøffer
    glGenRenderbuffers(1, &postdepth);
    glBindRenderbuffer(GL_RENDERBUFFER, postdepth);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIN_WIDTH, WIN_HEIGHT);
    //depth OG stencil
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_WIDTH, WIN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, postdepth);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, postdepth);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "error i tryn - post-framebuffer error" <<std::endl;
    else std::cout << "bra gpostbuffer-framebuffer satt opp " <<std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void framebuffercontroller::copydepthbuffer()
{
    int winwid = settings::getisetting(settings::SET_SCREENX);
    int winhei = settings::getisetting(settings::SET_SCREENY);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, tilebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postbuffer);
    glBlitFramebuffer(0, 0, winwid, winhei, 0, 0, winwid, winhei,
                      GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void framebuffercontroller::resizebuffers()
{
    //yes
    cleanup();
    setupbuffers();
}

void framebuffercontroller::blur()
{
    //int bufferid?
}

void framebuffercontroller::close()
{

}

void framebuffercontroller::cleanup()
{
    glDeleteTextures(1, &tilepos);
    glDeleteTextures(1, &tilergb);
    glDeleteTextures(1, &tilenorm);

    glDeleteTextures(1, &postrgb);
    glDeleteRenderbuffers(1, &tiledepth);
    glDeleteRenderbuffers(1, &postdepth);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &tilebuffer);
    glDeleteFramebuffers(1, &postbuffer);
}

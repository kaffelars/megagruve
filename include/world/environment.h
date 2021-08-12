#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H



namespace environment
{
    float getcurrenttime();
    void updatetime();

    direction getsundir();

    void renderskybox();

    rgbcolor getskycolor();
    rgbcolor getfogcolor();
    rgbcolor getsuncolor();

    float getcloudcover();
};

#endif // ENVIRONMENT_H

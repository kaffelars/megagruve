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

    void initialize();
    void resetenvironment();

    void sendrendererdata();

    void changetime(float timetochange);

    void changecloudcover(float change);

    void rain();

    float getcloudcover();
    void toggletimemoving();
};

#endif // ENVIRONMENT_H

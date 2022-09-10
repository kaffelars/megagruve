#ifndef UTILS_H
#define UTILS_H

//diverse utility functions

namespace utils
{
    float packu2f(uint8_t a, uint8_t b, uint8_t c);

    float packnormal(glm::vec3 normal); //må være normalisert
    float packnormal(float x, float y, float z);
    uint8_t pack4bitint(uint8_t fourbitone, uint8_t fourbittwo);

    float packrgb(glm::vec3 rgb);

    float packuvtex(float uva, float uvb, uint8_t texid);

    int randint(int minimum, int maximum);
    bool randbool();

    bool getfolders(std::string path, std::vector<std::string>& folders);

    float getpackednorm(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3);

    void clamp(int& toclamp, int minval, int maxval);
    void clamp(float& toclamp, float minval, float maxval);
    void clamp255(float& toclamp);
    void clamp255(int& toclamp);
    void clamp(rgbcolor& toclamp, float minval, float maxval);

    float getdist(glm::vec2 startpt, glm::vec2 endpt);

    glm::vec3 getcubemapnormal(int x, int y, int a, int texsize);
}


#endif // UTILS_H

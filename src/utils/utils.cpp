#include "consts.h"
#include "utils.h"


namespace utils
{
    float packu2f(uint8_t a, uint8_t b, uint8_t c)
    {
        uint32_t pack = (a << 16) | (b << 8) | c;
        return ((double)pack) / ((double) (1 << 24));
    }

    float getpackednorm(glm::vec3 p1,glm::vec3 p2,glm::vec3 p3)
    {
        glm::vec3 v1 = p2 - p1; glm::vec3 v2 = p3 - p1;
        glm::vec3 norm = glm::normalize(glm::cross(v1, v2));
        return packnormal(norm);
    }

    float packnormal(glm::vec3 normal) //må være normalisert
    {
        normal += glm::vec3(1.0f);
        normal /= 2.0f;

        return packu2f(normal.x*255, normal.y*255, normal.z * 255);
    }

    float packnormal(float x, float y, float z)
    {
        return packnormal(glm::vec3(x,y,z));
    }

    float packrgb(glm::vec3 rgb)
    {
        return packu2f(rgb.x*255, rgb.y*255, rgb.z * 255);
    }

    /*float packuvtex(glm:vec2 uv, uint8_t texid)
    {
        return packu2f(uv.x*255, uv.y*255, texid);
    }*/

    float packuvtex(float uva, float uvb, uint8_t texid)
    {
        return packu2f(uva*255, uvb*255, texid);
    }

    int randint(int minimum, int maximum)
    {
        return minimum + (rand()%(maximum-minimum+1));
    }

    bool randbool()
    {
        return randint(0, 1);
    }

    void clamp(rgbcolor& toclamp, float minval, float maxval)
    {
        clamp(toclamp.x, minval, maxval);
        clamp(toclamp.y, minval, maxval);
        clamp(toclamp.z, minval, maxval);
    }

    bool getfolders(std::string path, std::vector<std::string>& folders)
    {
        DIR *dir; struct dirent *diread;

        if ((dir = opendir(path.c_str())) != nullptr) {
            while ((diread = readdir(dir)) != nullptr) {
                std::string pepsimaxi(diread->d_name);
                if (pepsimaxi != "." && pepsimaxi != "..")
                    folders.push_back(pepsimaxi);
            }
            closedir (dir);
        } else {
            std::cout << "error dir open shiz i utils::getfolders\n";
            return false;
        }

        return true;
    }

    void clamp(int& toclamp, int minval, int maxval)
    {
        if (toclamp > maxval) toclamp = maxval;
        if (toclamp < minval) toclamp = minval;
    }

    void clamp(float& toclamp, float minval, float maxval)
    {
        if (toclamp > maxval) toclamp = maxval;
        if (toclamp < minval) toclamp = minval;
    }

    void clamp255(float& toclamp)
    {
        return clamp(toclamp, 0.0f, 255.0f);
    }

    void clamp255(int& toclamp)
    {
        return clamp(toclamp, 0, 255);
    }


    float getdist(glm::vec2 startpt, glm::vec2 endpt)
    {
        glm::vec2 delta = endpt - startpt;

        return sqrt(delta.x * delta.x + delta.y * delta.y);
    }

    glm::vec3 getcubemapnormal(int x, int y, int a, int texsize)
    {
        glm::vec3 normal = glm::vec3(0.0f);

        int ex = x - (texsize / 2);
        int ey = y - (texsize / 2);
        int ez = texsize / 2;

        if (a == 0) normal = glm::vec3(ez, -ey, ex);//x+
        if (a == 1) normal = glm::vec3(-ez, -ey, -ex);//x-

        if (a == 2) normal = glm::vec3(ex, ez, -ey);//y+

        if (a == 3) normal = glm::vec3(ex, -ez, ey);//y-

        if (a == 4) normal = glm::vec3(ex, -ey, -ez);//z+
        if (a == 5) normal = glm::vec3(-ex, -ey, ez);//z-

        return glm::normalize(normal);
    }
}

#include "consts.h"
#include "shadercontroller.h"


namespace shadercontroller
{
    void addshader(uint32_t shaderid, std::string filename, std::vector<std::string> uniforms);
    shader* getshader(int shadernum);

    namespace
    {
        std::unordered_map<uint32_t, shader> shaders;
        //std::vector<shader> shaders;
        shader* activeshader = nullptr;
    }
}

shader* shadercontroller::getshader(int shaderid)
{
    //std::cout << shaderid <<"herher\n";
    return &(shaders.at(shaderid));//trygt? jada, no stress
    //return &(shaders[shaderid]);//trygt? jada, no stress
}

void shadercontroller::addshader(uint32_t shaderid, std::string filename, std::vector<std::string> uniforms)
{
    //std::cout << shaderid << "settin\n";
    //shaders.emplace_back(filename, uniforms);

    shaders.emplace(std::piecewise_construct, std::forward_as_tuple(shaderid), std::forward_as_tuple(filename, uniforms)); //constructes directe i mappet for å unngå destructor crap
}

void shadercontroller::initialize()
{
    std::cout << "setting up shaders\r\n";

    addshader(SH_MAIN, "main", {"pv", "vpos", "sundir", "sunlight", "suncolor", "fogcolor", "campos", "mcharlight"});
    addshader(SH_SCENE, "scene", {"gbuf_rgb", "gbuf_pos", "gbuf_norm", "underwater"}); //"tiles",
    addshader(SH_SKY, "sky", {"sundir", "skycolor", "pv", "campos", "fogcolor", "suncolor", "cloudcover"});
    addshader(SH_PP, "postprocessing", {});
    addshader(SH_LINE, "line", {"pv", "vpos", "rgb"});
    addshader(SH_ICONS, "icon", {"screensize"});
    addshader(SH_WATER, "water", {"gbuf_rgb", "gbuf_pos", "gbuf_norm", "tex", "timer", "pv", "vpos", "sundir", "sunlight", "suncolor", "fogcolor", "campos", "mcharlight"});
    addshader(SH_PARTICLE, "particle", {"pv", "sundir", "sunlight", "suncolor", "fogcolor", "campos", "mcharlight"});
    addshader(SH_SIMPLEPARTICLE, "simpleparticle", {});

    std::cout << "shaders set up \r\n";

}

GLuint shadercontroller::getuniformid(std::string uniformname)
{
    return activeshader->getuniformid(uniformname);
}

void shadercontroller::activateshader(int shaderid)
{
    activeshader = getshader(shaderid);
    //std::cout << "xum";
    activeshader->activate();
    //std::cout << "asdasdasd";
}

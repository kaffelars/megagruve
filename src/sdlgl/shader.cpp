#include "consts.h"
#include "shader.h"

shader::shader(std::string filename, std::vector<std::string> uniformnames)
{
    std::cout << "setting up shader " << filename << "\n";
    shadername = filename;
    setupshader(filename);
    std::cout << "uniforms: ";
    for (std::string u:uniformnames)
    {
        GLuint uniformloc = glGetUniformLocation(shaderprogram, u.c_str());
        std::cout << u << " ";
        uniforms.emplace(u, uniformloc);
    }
    std::cout << "\n\n";
}

shader::~shader()
{
    //dtor
    cleanup();
}

void shader::cleanup()
{
    std::cout << "shader cleaning in progress (" << shadername << ")\n";

    glUseProgram(0);

    for (auto i : shaderids)
        glDetachShader(shaderprogram, i);

    glDeleteProgram(shaderprogram);

    for (auto i : shaderids)
        glDeleteShader(i);
}

void shader::setupshader(std::string filename)
{
    shaderprogram = glCreateProgram();

    std::string vertex = "data/shaders/" + filename + "vert.glsl";
    std::string fragment = "data/shaders/" + filename + "frag.glsl";

    loadshaderprogram(vertex, GL_VERTEX_SHADER);
    loadshaderprogram(fragment, GL_FRAGMENT_SHADER);

    std::cout << "shaders compiled";

    glLinkProgram(shaderprogram);

    std::cout << ", linked";

    int islinked;
    glGetProgramiv(shaderprogram, GL_LINK_STATUS, (int*)&islinked);

    if (!islinked)
        printlinkingerror(shaderprogram);

    activate();

    std::cout << " & activated\n";
}

void shader::activate()
{
    glUseProgram(shaderprogram);
}

GLuint shader::getuniformid(std::string uniformname)
{
    return uniforms.at(uniformname);
}

bool shader::loadshaderprogram(std::string shado, GLenum shadertype)
{
    std::cout << "loading shader: " << shado << "\n";

    std::ifstream filu(shado.c_str());
    std::stringstream buffer;
    buffer << filu.rdbuf();

    std::string shaderinnhold = buffer.str();

    char* src = const_cast<char*>(shaderinnhold.c_str());
    int32_t strsize = shaderinnhold.length();

    int shaderid = glCreateShader(shadertype);
    glShaderSource(shaderid, 1, &src, &strsize);
    glCompileShader(shaderid);

    int wascompiled = 0;
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &wascompiled);

    printcompilationlog(shaderid);

    if (wascompiled)
    {
        std::cout << "shader " << shado << " compiled\n";
        glAttachShader(shaderprogram, shaderid);
        shaderids.push_back(shaderid);
        return true;
    }

    return false;
}

void shader::printlinkingerror(int32_t shaderid)
{
    std::cout << "=======================================\n";
    std::cout << "linking error: ";

    int leng;
    glGetProgramiv(shaderid, GL_INFO_LOG_LENGTH, &leng);
    char* errorlog = new char[leng];
    glGetProgramInfoLog(shaderprogram, leng, &leng, errorlog);

    std::cout << errorlog << "\n";

    delete[] errorlog;
    return;
}

void shader::printcompilationlog(int32_t shaderid)
{
    int leng;
    glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &leng);

    if (leng)
    {
        char* infolog = new char[leng];
        glGetShaderInfoLog(shaderid, leng, &leng, infolog);

        std::cout << "compile info: " << infolog << "\n";

        delete[] infolog;
    }
}

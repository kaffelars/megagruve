#ifndef SHADER_H
#define SHADER_H

#include "consts.h"

class shader
{
    public:
        shader(std::string filename, std::vector<std::string> uniformnames);
        virtual ~shader();

        GLuint getuniformid(std::string uniformname);

        std::unordered_map<std::string, GLuint> uniforms;

        GLuint shaderprogram;

        std::vector<int32_t> shaderids;

        bool compileshader(int shaderid);

        GLuint projid, viewid, modelid, posid, pvmid, camposid, uisizeid, etcid, filterid, sunid, colid, fogid; //fucked
        GLuint texid[7];

        void activate();

        void cleanup();

        bool createshader(const std::string &filename, GLenum shadertype);
    protected:
    private:
        void printlinkingerror(int32_t shaderId);
        void printcompilationlog(int32_t shaderId);

        void setupshader(std::string filename);
        bool loadshaderprogram(std::string shado, GLenum shadertype);
};

#endif // SHADER_H

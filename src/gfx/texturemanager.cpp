#include "consts.h"
#include "texturemanager.h"

namespace texturemanager
{
    void loadtiletextures();
    void loadcloudtexture();
    void loadicontextures();

    std::unordered_map<std::string, uint32_t> texnametoid;

    GLuint tiletextureid;

    GLuint cloudtextureid;


    GLuint iconstextureid[3];

    std::unordered_map<std::string, uint32_t> iconnametoid[3];
    std::vector<uint32_t> itemtextotiletex;

    std::vector<std::string> tiletexturenames = {"debug", "water", "water_side", "dirt", "grass", "grass2", "grassydirt", "stone", "rock", "sand", "flag", "leaves", "rain", "blue", "log",
    "logtop", "grasstuft1", "grasstuft2", "planks", "cactus_side", "cactus_top", "littlegrass", "bookcase", "flower1", "flower2", "flower3",
    "chest_top", "chest_bottom", "chest_side", "chest_front", "chest_inside", "destroy1", "destroy2", "destroy3", "destroy4", "glowstone", "snow", "gravel", "ice", "green", "orb",
    "bedrock", "diamond_ore", "iron_ore", "coal_ore", "log_birch", "log_birch_top", "grass_side_overlay", "clay", "clay_hard", "brick", "door_lower", "door_upper", "grass_bottom", "grass_top",
    "flag1", "flag2", "flag3", "flag4", "flagpole", "crafting_table", "table_side", "white_tiles", "sandstone_block", "button"};
}


void texturemanager::bindtiletextures(int texid)
{
    glActiveTexture(GL_TEXTURE0+texid);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tiletextureid);
}

void texturemanager::bindcloudtexture(int texid)
{
    glActiveTexture(GL_TEXTURE0+texid);
    glBindTexture(GL_TEXTURE_2D, cloudtextureid);
}

void texturemanager::bindiconstexture(iconsizes iconsize,int texid)
{
    glActiveTexture(GL_TEXTURE0+texid);
    glBindTexture(GL_TEXTURE_2D_ARRAY, iconstextureid[iconsize]);
}

//fix bedre oppsett på code'n

void texturemanager::getbiometint(std::vector<rgbcolor255>& rgb)
{
    rgb.clear();

    std::string filo = "data/gfx/biometint.png";
    SDL_Surface* tileimg = IMG_Load(filo.c_str());
    uint8_t* pixels = (uint8_t*)tileimg -> pixels;

    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            uint8_t r = pixels[4*((int)x + 256 * (int)y)+0];
            uint8_t g = pixels[4*((int)x + 256 * (int)y)+1];
            uint8_t b = pixels[4*((int)x + 256 * (int)y)+2];

            rgb.push_back(rgbcolor255{r,g,b});
        }
    }


    SDL_FreeSurface(tileimg);
}

void texturemanager::loadicontextures()
{
    std::vector<std::string> folders = {"small", "medium", "large"};
    int sizes[3] = {10, 16, 24};
    std::vector<std::string> filenames[3]= {
    {"debug", "redheart", "halfheart", "halfblackheart", "blackheart", "yellowheart", "greenheart", "blueheart", "silverheart", "shield"},
    {"debug", "iron_pickaxe", "iron_axe", "iron_sword", "diamond_pickaxe", "apple", "apple_golden", "lightbulb", "green_wand", "red_wand", "totem", "fireball", "diamond", "wings", "star"},
    {"debug", "border", "selectedborder", "clickedborder"}
    };

    for (int a=0; a < 10; a++)
        filenames[1].push_back(std::to_string(a));

    //std::vector<std::string> tiletexturenames = {"debug", "water", "dirt", "grass", "grassydirt", "stone", "rock", "sand", "flag", "leaves", "blue", "log", "logtop", "grasstuft1", "grasstuft2", "planks", "cactus_side", "cactus_top"};

    for (int a = 0; a < 3; a++)
    {
        glGenTextures(1,&iconstextureid[a]);

        std::cout << "textur id: " << iconstextureid[a] << "\r\n";
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, iconstextureid[a]);

        int tileres = sizes[a];

        int layers = filenames[a].size();
        if (a == 1) layers += tiletexturenames.size();


        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, tileres, tileres, layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

        int layer = 0;

        for (std::string& texture : filenames[a])
        {
            std::string filo = "data/gfx/icons/"+folders[a] + "/" +texture+".png";
            SDL_Surface* tileimg = IMG_Load(filo.c_str());

            if (tileimg == NULL)
            {
                std::cout << "\nerror loading texture: " << texture << " - " << IMG_GetError() << "\n";
            }
            else
            {
                std::cout << "\ntexture " << texture << ".png loaded " << int(tileimg->w) << "x" << int(tileimg->h) << " - " << int(tileimg->format->BytesPerPixel) << " bytes/px\n";
            }

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
            0,                     //Mipmap number
            0,0,layer,                 //xoffset, yoffset, zoffset
            tileres,tileres,1,                 //width, height, depth
            GL_RGBA,                //format
            GL_UNSIGNED_BYTE,      //type
            tileimg->pixels);

            iconnametoid[a].insert({texture, layer});

            SDL_FreeSurface(tileimg);

            tileimg = nullptr;

            layer++;

            if (a == 1)
                itemtextotiletex.push_back(0);
        }

        if (a == 1)//tiletextures, fix bedre
        {
            for (std::string texture : tiletexturenames)
            {
                std::string filo = "data/gfx/tiles/" +texture+".png";
                SDL_Surface* tileimg = IMG_Load(filo.c_str());

                if (tileimg == NULL)
                {
                    std::cout << "\nerror loading texture: " << texture << " - " << IMG_GetError() << "\n";
                }
                else
                {
                    std::cout << "\ntexture " << texture << ".png loaded " << int(tileimg->w) << "x" << int(tileimg->h) << " - " << int(tileimg->format->BytesPerPixel) << " bytes/px\n";
                }

                uint8_t* processedpic = new uint8_t[tileres*tileres*4];
                for (int a= 0; a < tileres*tileres*4; a++)
                    processedpic[a] = 0;

                uint8_t* pixels = (uint8_t*)tileimg -> pixels;

                for (float ex = 0; ex < tileres; ex++)
                {
                    for (float ey = 0; ey < tileres; ey++)
                    {
                        //helt random - fix
                        /*int tx = (ex / 2.3f) + 1;
                        int ty = ((ey +(ex/2))/2.3f)+6;
                        int ux = (ex / 2.15f) + (ey / 2.15f)+1;
                        int uy = 4-(ex/5) + (ey/3);*/

                        /*int tx = ex / 2; //ikke bra
                        int ty = (ex / 4) + (tileres / 4) + (ey / 2);
                        int ux = (ex / 2) + (ey / 2);
                        int uy = (ey / 4) - (ex / 4) + (tileres / 4);

                        if (tx >= 0 && tx < tileres && ty >= 0 && ty < tileres && ux >= 0 && ux < tileres && uy >= 0 && uy < tileres)
                        {
                            for (int a = 0; a < 3; a++)
                            {
                                processedpic[a + 4*(tx + tileres * ty)] = pixels[4*(ex + tileres * ey)+a] / 1.5f;
                                processedpic[a+4*((tileres - tx - 1) + tileres * ty)] = pixels[a+4*(ex + tileres * ey)] / 2.5f;
                                processedpic[a+4*(ux + tileres * uy)] = pixels[a+4*(ex + tileres * ey)];
                            }
                            processedpic[3 + 4*(tx + tileres * ty)] = pixels[4*(ex + tileres * ey)+3];
                            processedpic[3+4*((tileres - tx - 1) + tileres * ty)] = pixels[3+4*(ex + tileres * ey)];
                            processedpic[3+4*(ux + tileres * uy)] = pixels[3+4*(ex + tileres * ey)];
                        }*/

                        float tx = ex;
                        float ty = ey;

                        for (int b = 0; b < 4; b++)
                        {
                            processedpic[b + 4*((int)tx + tileres * (int)ty)] = pixels[4*((int)ex + tileres * (int)ey)+b];
                        }
                    }
                }


                glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
                0,                     //Mipmap number
                0,0,layer,                 //xoffset, yoffset, zoffset
                tileres,tileres,1,                 //width, height, depth
                GL_RGBA,                //format
                GL_UNSIGNED_BYTE,      //type
                processedpic);

                iconnametoid[a].insert({texture, layer});

                SDL_FreeSurface(tileimg);
                delete processedpic;
                tileimg = nullptr;

                layer++;

                if (a == 1)
                    itemtextotiletex.push_back(gettiletexturenumber(texture));
            }
        }

        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }
}

void texturemanager::loadtiletextures()
{
    glGenTextures(1,&tiletextureid);

    std::cout << "textur id: " << tiletextureid << "\r\n";
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tiletextureid);

    int tileres = settings::getisetting(settings::SET_TILERES);
    if (tileres < 4 || tileres > 1024) tileres = 16;



    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, tileres, tileres, tiletexturenames.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    int layer = 0;

    for (std::string& texture : tiletexturenames)
    {
        std::string filo = "data/gfx/tiles/"+texture+".png";
        SDL_Surface* tileimg = IMG_Load(filo.c_str());

        if (tileimg == NULL)
        {
            std::cout << "\nerror loading texture: " << texture << " - " << IMG_GetError() << "\n";
        }
        else
        {
            std::cout << "\ntexture " << texture << ".png loaded " << int(tileimg->w) << "x" << int(tileimg->h) << " - " << int(tileimg->format->BytesPerPixel) << " bytes/px\n";
        }

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
        0,                     //Mipmap number
        0,0,layer,                 //xoffset, yoffset, zoffset
        tileres,tileres,1,                 //width, height, depth
        GL_RGBA,                //format
        GL_UNSIGNED_BYTE,      //type
        tileimg->pixels);

        texnametoid.insert({texture, layer});

        SDL_FreeSurface(tileimg);
        tileimg = nullptr;

        layer++;
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16); //add setting?
}

void texturemanager::loadcloudtexture()
{
    glGenTextures(1,&cloudtextureid);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cloudtextureid);

    std::string filo = "data/gfx/clouds.png";
    SDL_Surface* tileimg = IMG_Load(filo.c_str());
    int tileres = 512;

    if (tileimg == NULL)
    {
        std::cout << "error loading texture: " << filo << " - " << IMG_GetError() << "\n";
    }
    else
    {
        std::cout << "texture " << filo << ".png loaded " << int(tileimg->w) << "x" << int(tileimg->h) << " - " << int(tileimg->format->BytesPerPixel) << "\n";
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, tileres, tileres, 0, GL_RED, GL_UNSIGNED_BYTE, tileimg->pixels);

    SDL_FreeSurface(tileimg);
    tileimg = nullptr;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST);
}

uint32_t texturemanager::gettiletexturenumber(std::string texturename)
{
    if (texnametoid.find(texturename) == texnametoid.end()) return 0;
    return texnametoid.at(texturename);
}

uint32_t texturemanager::gettiletexturefromitemtexture(uint32_t itemtexid)
{
    return itemtextotiletex[itemtexid];
}

uint32_t texturemanager::geticontexturenumber(std::string texturename, iconsizes iconsize)
{
    if (iconnametoid[iconsize].find(texturename) == iconnametoid[iconsize].end()) return 0;
    return iconnametoid[iconsize].at(texturename);
}

void texturemanager::initialize()
{
    loadtiletextures();
    loadcloudtexture();
    loadicontextures();
}

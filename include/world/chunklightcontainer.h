#ifndef CHUNKLIGHTCONTAINER_H
#define CHUNKLIGHTCONTAINER_H


class chunklightcontainer
{
    public:
        chunklightcontainer();
        virtual ~chunklightcontainer();

        void filllayer(uint8_t layer, uint8_t value);
        uint8_t getvalue(uint8_t x, uint8_t y, uint8_t z);
        uint8_t getvalue(ctilepos xyz);

        void setvalue(uint8_t x, uint8_t y, uint8_t z, uint8_t value);
        void setvalue(ctilepos xyz, uint8_t value);

        void initialize();
        void deinitialize();

        uint8_t getinterpolatedvalue(float x, float y, float z, uint8_t direction);

    protected:

    private:
        struct lightlayer
        {
            uint8_t lightvalue;
            uint8_t* light;
        };

        std::vector<lightlayer> lightlayers;

        void allocate(uint8_t layer);
        void deallocate(uint8_t layer);
        uint8_t getlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z);
        void setlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z, uint8_t value);
};

#endif // CHUNKLIGHTCONTAINER_H

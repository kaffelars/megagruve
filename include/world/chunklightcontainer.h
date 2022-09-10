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
        uint8_t getinterpolatedvalue2(float x, float y, float z);
        void getinterpolatedvalues(float x, float y, float z, uint8_t direction, uint8_t (&sunlight)[4]);
        uint8_t getcorner(uint8_t x, uint8_t y, uint8_t z);

    protected:

    private:
        struct lightlayer
        {
            uint8_t lightvalue;
            uint8_t* light; //4 bit values packed
        };

        std::vector<lightlayer> lightlayers;

        void allocate(uint8_t layer);
        void deallocate(uint8_t layer);
        uint8_t getlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z);
        void setlvalue(uint8_t layer, uint8_t x, uint8_t y, uint8_t z, uint8_t value);

        uint8_t getfirstlvalue(uint8_t val);
        uint8_t getsecondlvalue(uint8_t val);

        void setfirstlvalue(uint8_t& refval, uint8_t val);
        void setsecondlvalue(uint8_t& refval, uint8_t val);
};

#endif // CHUNKLIGHTCONTAINER_H

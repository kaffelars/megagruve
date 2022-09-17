#ifndef CHUNKLIGHTPOINTS_H
#define CHUNKLIGHTPOINTS_H


class chunklightpoints
{
    public:
        chunklightpoints();
        virtual ~chunklightpoints();

        struct lightpoint
        {
            ctilepos ctpos;
            uint8_t light;
            bool hasbeenpropagated {false};
        };

        void addpoint(ctilepos ctpos, uint8_t lightstrength);
        const std::vector<lightpoint>& getlightpoints();
        void propagated();
        bool requestspropagation();

    protected:

    private:
        std::vector<lightpoint> lightpoints;
        bool needspropagation {false};
};

#endif // CHUNKLIGHTPOINTS_H

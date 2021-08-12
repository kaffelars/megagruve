#ifndef STATNUMBERS_H
#define STATNUMBERS_H


class statnumbers
{
    public:
        statnumbers();
        virtual ~statnumbers();

        int32_t maxhp {0};
        int32_t attack {0};
        int32_t defense {0};
        float movespeed {0.0f};
        float usespeed {0.0f};

    protected:

    private:
};

statnumbers operator+(const statnumbers& a, const statnumbers& b);

#endif // STATNUMBERS_H

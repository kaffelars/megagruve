#ifndef STATNUMBERS_H
#define STATNUMBERS_H


class statnumbers
{
    public:
        statnumbers();
        virtual ~statnumbers();

        enum stat
        {
            STAT_MAXHP, STAT_ATTACK, STAT_DEFENSE, STAT_MOVESPEED, STAT_USESPEED
        };

        void setstat(stat stattoset, float value);
        void changestat(stat stattochange, float valuetoadd);
        float getstat(stat stattoget);

        float statvalues[5] {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    protected:

    private:

};

statnumbers operator+(const statnumbers& a, const statnumbers& b);

#endif // STATNUMBERS_H

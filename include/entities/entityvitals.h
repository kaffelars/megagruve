#ifndef ENTITYVITALS_H
#define ENTITYVITALS_H


class entityvitals
{
    public:
        entityvitals(uint32_t maxhp, uint32_t armor);
        entityvitals();
        virtual ~entityvitals();

        enum s_effects
        {
            SE_POISON, SE_HEAL
        };

        struct s_effect
        {
            s_effects type;
            uint32_t strength;
            uint32_t duration;
        };

        std::vector<s_effect> statuseffects;

        void removestatuseffect(uint32_t index);
        void removestatuseffect(std::vector<s_effect>::iterator index);

        uint32_t hp {10};
        uint32_t maxhp {10};

        uint32_t armor {0};

        bool alive;

        void takedamage(uint32_t damage);
        void heal(uint32_t healing);

        bool isalive();

        void update();

    protected:

    private:
};

#endif // ENTITYVITALS_H

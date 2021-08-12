#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


class boundingbox
{
    public:
        struct box
        {
            point points[2];
        };

        boundingbox(box fbbox);
        boundingbox();

        virtual ~boundingbox();

        void changeboundingbox(box fbbox);
        box& getbox();

        bool collisionwith(box fbbox);

    protected:

    private:
        box bbox { { point{0.0f, 0.0f, 0.0f},point{1.0f,1.0f, 1.0f} } };
};

#endif // BOUNDINGBOX_H

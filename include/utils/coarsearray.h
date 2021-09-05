#ifndef COARSEARRAY_H
#define COARSEARRAY_H

#include "consts.h"

template <class T, int N>
class coarsearray
{
    private:
        T* data;
    public:
        coarsearray()
        {
            data = new T[N*N];
        }
        virtual ~coarsearray()
        {
            delete data;
        }

        void setdata(int x, int y, T datatoset)
        {
            data[x + N * y] = datatoset;
        }

        T getdata(int x, int y)
        {
            return data[x + N * y];
        }

        T getaverageddata(int x, int y)
        {
            //dette er fubar
            glm::ivec2 pts[3] = {glm::ivec2(0),glm::ivec2(0),glm::ivec2(0)};
            float weights[4] = {1.0f, 0.0f, 0.0f, 0.0f};

            if (x-1 % 3 == 0)
            {
                pts[0].x = 1;
                pts[2].x = 1;
            }
            else if (x-2 % 3 == 0)
            {
                pts[0].x = -1;
                pts[2].x = -1;
            }

            if (y-1 % 3 == 0)
            {
                pts[1].y = 1;
                pts[2].y = 1;
            }
            else if (y-2 % 3 == 0)
            {
                pts[1].y = -1;
                pts[2].y = -1;
            }

            if (pts[0].x && !pts[0].y) //horiz
            {
                weights[0] = 0.6666667f;
                weights[1] = 0.3333333f;
                weights[2] = 0.0f;
                weights[3] = 0.0f;
            }
            if (!pts[0].x && pts[0].y) //vert
            {
                weights[0] = 0.6666667f;
                weights[1] = 0.0f;
                weights[2] = 0.3333333f;
                weights[3] = 0.0f;
            }
            if (pts[0].x && pts[0].y) //skrå
            {
                weights[0] = 0.0f;
                weights[1] = 0.0f;
                weights[2] = 0.0f;
                weights[3] = 0.0f;
            }

            int hx = (x+1) / 3;
            int hy = (y+1) / 3;

            float totweight = 1.0f + weights[0] + weights[1] + weights[2];

            T averagedvalue = getdata(hx,hy) * weights[0];

            for (int a = 0; a < 3; a++)
                averagedvalue += getdata(hx + pts[0].x, hy + pts[0].y) * weights[a+1];// + getdata(hx + pts[1].x, hy + pts[1].y) + getdata(hx + pts[2].x, hy + pts[2].y) * 0.5f;

            return averagedvalue / totweight;
        }

    protected:


};

#endif // COARSEARRAY_H

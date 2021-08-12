#ifndef MULTIVEC_H
#define MULTIVEC_H

template <class T, int N>
class multivec
{
    private:
        T data[N];

    public:
        multivec()
        {
            for (int a =0; a < N; a++)
            {
                data[a] = 0;
            }
        }

        virtual ~multivec() {}

        normalize() //makes length = 1
        {
            T value;

            for (int a =0; a < N; a++)
            {
                value += (data[a] * data[a]);
            }

            if (value > 0)
            {
                value = sqrt(value);

                for (int a =0; a < N; a++)
                {
                    data[a] /= value;
                }
            }
        }

        unionize() //makes sum = 1
        {
            T value;

            for (int a =0; a < N; a++)
            {
                value += data[a];
            }

            if (value > 0)
            {
                for (int a =0; a < N; a++)
                {
                    data[a] /= value;
                }
            }
        }

        T& operator[](int a)
        {
            return data[a];
        }

        void add(int a, T value)
        {
            data[a] += value;
        }
};

#endif // MULTIVEC_H

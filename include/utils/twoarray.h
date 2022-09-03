#ifndef TWOARRAY_H
#define TWOARRAY_H

template <class T, int N>
class twoarray
{
    private:
        T* data;
    public:
        twoarray()
        {
            data = new T[N*N];
        }
        virtual ~twoarray()
        {
            delete [] data;
        }

        void setdata(int x, int y, T datatoset)
        {
            data[x + N*y] = datatoset;
        }

        T getdata(int x, int y)
        {
            return data[x + N*y];
        }
};

#endif // TWOARRAY_H

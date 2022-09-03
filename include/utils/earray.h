#ifndef EARRAY_H
#define EARRAY_H

template <class T>
class earray //2d array
{
    public:

        int widx, widy;
        T* arraydata;

        earray(int wx=0, int wy=0)
        {
            widx = wx;
            widy = wy;

            arraydata = nullptr;
        }

        virtual ~earray() {}

        void setdimensions(int wx, int wy)
        {
            widx = wx;
            widy = wy;
        }

        void setdimensions(glm::ivec2 w)
        {
            widx = w.x;
            widy = w.y;
        }

        void loadarray()
        {
            arraydata = new T[widx*widy];
        }

        bool arrayloaded()
        {
            if (arraydata == nullptr) return false;
            else return true;
        }

        void unloadarray()
        {
            delete[] arraydata;
            arraydata = nullptr;
        }

        void deinit()
        {
            unloadarray();
        }

        void fillarray(T d)
        {
            if (arraydata != nullptr)
            {
                for (int a = 0; a < widx*widy; a++)
                {
                    arraydata[a] = d;
                }
            }
        }

        inline T* getdatapointer()
        {
            return arraydata;
        }

        inline T getdata(int x, int y)
        {
            return arraydata[x + widx*y];
        }

        inline T getdatab(int x, int y, T defaultreturnvalue)
        {
            //samme som getdata, bare med litt sikkerhet
            if (x < 0 || y < 0 || x >= widx || y >= widy) return defaultreturnvalue;

            return arraydata[x + widx*y];
        }

        inline T &getelement(int x, int y)
        {
            return arraydata[x + widx*y];
        }

        inline void setdata(int x, int y, T d)
        {
            arraydata[x + widx*y] = d;
        }

    protected:

    private:
};

#endif // EARRAY_H

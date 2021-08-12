#ifndef DARRAY_H
#define DARRAY_H

template <class T>
class darray
{
    public:

        int widx, widy, widz;
        T* arraydata;

        darray(int wx=0, int wy=0, int wz=0)
        {
            widx = wx;
            widy = wy;
            widz = wz;

            arraydata = nullptr;
        }

        virtual ~darray() {}

        void setdimensions(int wx, int wy, int wz=1)
        {
            widx = wx;
            widy = wy;
            widz = wz;
        }

        void setdimensions(glm::ivec3 w)
        {
            widx = w.x;
            widy = w.y;
            widz = w.z;
        }

        void setdimensions(glm::ivec2 w)
        {
            widx = w.x;
            widy = w.y;
            widz = 1;
        }

        void loadarray()
        {
            arraydata = new T[widx*widy*widz];
        }

        bool arrayloaded()
        {
            if (arraydata == nullptr) return false;
            else return true;
        }

        void unloadarray()
        {
            delete arraydata;
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
                for (int a = 0; a < widx*widy*widz; a++)
                {
                    arraydata[a] = d;
                }
            }
        }

        inline T* getdatapointer()
        {
            return arraydata;
        }

        inline T getdata(int x, int y, int z)
        {
            return arraydata[x + widx*(z + y*widz)];//(y*(widz + (z*widy)))];
        }

        inline T getdata(int x, int y)
        {
            return arraydata[x + widx*y];//(y*(widz + (z*widy)))];
        }

        bool isinbounds(int x, int y)
        {
            if (x < 0 || y < 0 || x >= widx || y >= widy) return false;
            return true;
        }

        bool isinbounds(int x, int y, int z)
        {
            if (x < 0 || y < 0 || z < 0 || x >= widx || y >= widy || z >= widz) return false;
            return true;
        }

        inline T getdatab(int x, int y, int z, T defaultreturnvalue)
        {
            //samme som getdata, bare med litt sikkerhet
            if (x < 0 || y < 0 || z < 0 || x >= widx || y >= widy || z >= widz) return defaultreturnvalue;

            return arraydata[x + widx*(z + y*widz)];//(y*(widz + (z*widy)))];
        }

        inline T getdatab(int x, int y, T defaultreturnvalue)
        {
            //samme som getdata, bare med litt sikkerhet
            if (x < 0 || y < 0 || x >= widx || y >= widy) return defaultreturnvalue;

            return arraydata[x + widx*y];//(y*(widz + (z*widy)))];
        }

        inline T &getelement(int x, int y, int z)
        {
            return arraydata[x + widx*(z + y*widz)];
        }

        inline void setdata(int x, int y, int z, T d)
        {
            arraydata[x + widx*(z + y*widz)] = d;
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

#endif // DARRAY_H

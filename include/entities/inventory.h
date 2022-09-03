#ifndef INVENTORY_H
#define INVENTORY_H



class inventory
{
    public:
        inventory(int32_t invsiz = 16);
        virtual ~inventory();

        uint32_t invsize {16};
        uint32_t getinvsize();

        //bool additem(uint32_t itemid, uint32_t quantity);
        void resizeinv(uint32_t newsize);

        struct invitem
        {
            uint32_t itemid;
            uint32_t quantity;
        };

        bool positionininv(int32_t position);
        void swapitems(int32_t position1, int32_t position2);
        void swaporcombineitems(int32_t position1, int32_t position2);

        invitem& getinvitem(int32_t position);
        invitem removeinvitem(int32_t position);
        invitem emptyinvitem;
        void setinvitem(int32_t position, invitem item);

        bool additem(invitem itemtoadd);
        bool additem(std::string itemid, uint32_t quantity);

        std::vector<invitem> invitems;

        void clearinventory();
};

#endif // INVENTORY_H

#ifndef INVENTORY_H
#define INVENTORY_H



class inventory
{
    public:
        inventory(int32_t invsiz = 32);
        virtual ~inventory();

        uint32_t invsize {32};

        //bool additem(uint32_t itemid, uint32_t quantity);
        void resizeinv(uint32_t newsize);

        struct invitem
        {
            uint32_t itemid;
            uint32_t quantity;
        };

        invitem& getinvitem(uint32_t position);
        invitem emptyinvitem;

        bool additem(invitem itemtoadd);
        bool additem(std::string itemid, uint32_t quantity);

        std::vector<invitem> invitems;
};

#endif // INVENTORY_H

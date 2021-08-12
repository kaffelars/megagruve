#ifndef XMLDOC_H
#define XMLDOC_H

#include "pugixml.hpp"

class xmldoc
{
    public:
        xmldoc();
        virtual ~xmldoc();

        bool loadxmlfile(std::string xmlfile);

        std::string getdata(std::string tags);
        int getdataint(std::string tags);


    protected:

    private:
};

#endif // XMLDOC_H

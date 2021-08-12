#include "consts.h"
#include "xmldoc.h"

xmldoc::xmldoc()
{
    //ctor
}

xmldoc::~xmldoc()
{
    //dtor
}

std::string xmldoc::getdata(std::string tags)
{
    return "2";
}

int xmldoc::getdataint(std::string tags)
{
    return std::stoi(getdata(tags));
}

bool xmldoc::loadxmlfile(std::string xmlfile)
{

}

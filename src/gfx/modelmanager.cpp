#include "consts.h"
#include "modelmanager.h"

namespace modelmanager
{
    model emptymodel;
}

model& modelmanager::getemptymodel()
{
    return emptymodel;
}

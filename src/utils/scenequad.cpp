#include "consts.h"
#include "scenequad.h"

namespace scenequad
{
    namespace
    {
        vaocontainer squad;
    }
}

void scenequad::initialize()
{
    squad.cleanvbos();

    squad.initialize(1, vaocontainer::typo::TRIANGLES, 4);

    squad.addvalues(0, -1, 1, 0, 1);
    squad.addvalues(0, -1, -1, 0, 0);
    squad.addvalues(0, 1, -1, 1, 0);

    squad.addvalues(0, -1, 1, 0, 1);
    squad.addvalues(0, 1, -1, 1, 0);
    squad.addvalues(0, 1, 1, 1, 1);

    squad.setvbos();
}

void scenequad::render()
{
    squad.render();
}

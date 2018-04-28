#include "level.h"

Level::MAPLinker::MAPLinker()
{
    Level.MAPLinker.MAPLinkerRecord.clear();
    Level.MAPLinker.MAPLinkerRecord.push_back({\0, \0, \0, \0, \0, \0, \0, \0, \0, \0, \0, \0});
}

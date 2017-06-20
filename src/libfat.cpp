#include "libfat.hpp"
#include <string.h>

FatTable::FatTable(std::shared_ptr<Disk> disk, int clusterSize) :
    disk(disk),
    clusterSize(clusterSize),
    sectors(disk->sectorsTotal)
{

}

std::shared_ptr<FatFileEntry> FatTable::searchFile(std::string name) {
    for(auto& fileEntry : files)
        if(fileEntry.fileName == name)
            return std::shared_ptr<FatFileEntry>(&fileEntry);

    return nullptr;
}

bool FatTable::addFile(std::string name, const char *buffer, int size) {
    if(searchFile(name))
        return false;
}

int FatTable::searchFreeCluster(int startAt) {
    int first;
    int count = 0;

    // Looking for clusterSize contiguous unused sectors
    for(int i = startAt; i < sectors.size(); ++i) {
        FatSectorEntry& sectorEntry = sectors[i];
        if(count == 0)
            first = i;

        if(!sectorEntry.used)
            ++count;
        else
            count = 0;

        if(count == clusterSize)
            return first;
    }

    return -1;
}

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

    int clusterByteSize = SIZE_CLUSTER * clusterSize;
    int clusters = size / clusterByteSize;

    if(size % clusterByteSize)
        clusters += 1;

    for(int i = 0; i < clusters; ++i) {
        int freeCluster = searchFreeCluster();
        if(freeCluster == -1)
            return false;

        const char * data = buffer + i * clusterByteSize;

        for(int j = 0; j < clusterSize; ++j)
            sectors[j].used = 1;
    }

    return true;
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

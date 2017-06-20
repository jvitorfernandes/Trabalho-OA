#ifndef LIBFAT_H
#define LIBFAT_H

#include <string>
#include <vector>
#include <memory>

#include "disk.hpp"
#include "default_params.hpp"

using namespace std;

typedef struct FatFileEntry {
    string fileName;
    int firstSector;
} FatFileEntry;

typedef struct FatSectorEntry {
    int used;
    int eof;
    int next;
} FatSectorEntry;

class FatTable {
public:
    FatTable(Disk& disk, int clusterSize = SIZE_CLUSTER);

    std::shared_ptr<FatFileEntry> searchFile(std::string name);

    bool addFile(std::string name, const char *buffer, int size);

    int searchFreeCluster(int startAt = 0);

    std::shared_ptr<Disk> disk;
    int clusterSize;
    std::vector<FatFileEntry> files;
    std::vector<FatSectorEntry> sectors;
};

#endif // LIBFAT_H

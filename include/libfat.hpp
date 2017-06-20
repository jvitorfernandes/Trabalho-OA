#ifndef LIBFAT_H
#define LIBFAT_H

#include <string>
#include <vector>
#include <memory>

#include "disk.hpp"
#include "default_params.hpp"

using namespace std;

class FatFileEntry {
public:
    FatFileEntry() : firstSector(0) {};

    string fileName;
    int firstSector;
};

class FatSectorEntry {
public:
    FatSectorEntry() : used(0), eof(0), next(0) {};

    int used;
    int eof;
    int next;
};

class FatTable {
public:
    FatTable(std::shared_ptr<Disk> disk, int clusterSize = SIZE_CLUSTER);

    std::shared_ptr<FatFileEntry> searchFile(std::string name);

    bool addFile(std::string name, const char *buffer, int size);

    int searchFreeCluster(int startAt = 0);

    std::shared_ptr<Disk> disk;
    int clusterSize;
    std::vector<FatFileEntry> files;
    std::vector<FatSectorEntry> sectors;
};

#endif // LIBFAT_H

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
    FatFileEntry() : firstSector(0), size(0) {};

    string fileName;
    int firstSector;
    int size;
};

class FatSectorEntry {
public:
    FatSectorEntry(int used = 0, int eof = 0, int next = 0) :
        used(used), eof(eof), next(next) {

    }
    int used;
    int eof;
    int next;
};

class FatTable {
public:
    FatTable(std::shared_ptr<Disk> disk, int clusterSize = SIZE_CLUSTER);

    std::shared_ptr<FatFileEntry> searchFile(std::string name);

    bool addFile(std::string name, const char *buffer, int size);

    /* Finds the next free cluster, considering that sectors in 'marked'
     * are already used. */
    int findFirstFreeCluster(std::vector<int> marked = {});

    /* Finds all the free clusters in the given cylinder, considering
     * that sectors in 'marked' are already used. */
    std::vector<int> findFreeClustersSameCylinder(int firstCluster, std::vector<int> marked = {});

    /* Finds the first free nClusters or an empty vector in case it can't */
    std::vector<int> findFreeClusters(int nClusters);

    /* Reads the file */
    bool readFile(std::string name, std::vector<char> &buffer);

    std::shared_ptr<Disk> disk;
    int clusterSize;
    std::vector<FatFileEntry> files;
    std::vector<FatSectorEntry> sectors;
};

#endif // LIBFAT_H

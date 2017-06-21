#include "libfat.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

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

    /* Get the number of whole clusters that will be used by the file */
    int clusterByteSize = SIZE_SECTOR_IN_BYTES * clusterSize;
    int nClusters = ceil((size + 0.0) / clusterByteSize);
    int nSectors = ceil((size + 0.0)/SIZE_SECTOR_IN_BYTES);

    /* Effectively get the indexes of the clusters that will be used */
    std::vector<int> clusters = findFreeClusters(nClusters);
    if(clusters.size() == 0)
        return false;

    std::vector<int> sectors_to_write;
    int clusterI = 0;

    /* List the sectors to be written */
    while(nSectors > 0) {
        if(nSectors <= clusterSize) {
            for(int i = 0; i < nSectors; ++i) {
                sectors_to_write.push_back(clusters[clusterI] + i);
            }
            nSectors = 0;
        }
        else {
            for(int i = 0; i < clusterSize; ++i) {
                sectors_to_write.push_back(clusters[clusterI] + i);
            }
            nSectors -= clusterSize;
            ++clusterI;
        }
    }

    int bytesWritten = 0;
    for(int i = 0; i < sectors_to_write.size() - 1; ++i) {
        int sector = sectors_to_write[i];

        int byteInd = sector * SIZE_SECTOR_IN_BYTES;
        bytesWritten += SIZE_SECTOR_IN_BYTES;

        disk->setSector(sector, buffer + byteInd);

        sectors[sector].used = 1;
        sectors[sector].next = sectors_to_write[i + 1];
        sectors[sector].eof = 0;
    }

    int lastSector = sectors_to_write[sectors_to_write.size() - 1];
    sectors[lastSector].used = 1;
    sectors[lastSector].next = -1;
    sectors[lastSector].eof = 1;

    std::vector<char> lastBytes(SIZE_SECTOR_IN_BYTES);
    for(int i = 0; i < size - bytesWritten; ++i)
        lastBytes[i] = buffer[bytesWritten + i];
    disk->setSector(lastSector, &(lastBytes[0]));

    FatFileEntry entry;
    entry.fileName = name;
    entry.firstSector = clusters[0];
    entry.size = size;
    files.push_back(entry);

    return true;
}

int FatTable::findFirstFreeCluster(std::vector<int> marked) {
    int first;
    int count = 0;

    int nCylinders = disk->tracksPerSurface;
    int nSurfaces = disk->tracksPerCylinder;

    for(int track = 0; track < nSurfaces; ++track) {
        for(int cylinder = 0; cylinder < nCylinders; ++cylinder) {
            count = 0;

            for(int sector0 = 0; sector0 < disk->sectorsPerTrack; sector0 += clusterSize) {

                bool isFree = true;
                int ind0 = disk->fromPhysical(cylinder, track, sector0);

                for(int i = 0; i < clusterSize; ++i) {
                    int ind = ind0 + i;
                    FatSectorEntry& sectorEntry = sectors[ind];

                    if(sectorEntry.used || std::find(marked.begin(), marked.end(), ind) != marked.end()) {
                        isFree = false;
                        break;
                    }
                }

                if(isFree)
                    return ind0;
            }
        }
    }

    return -1;
}

std::vector<int> FatTable::findFreeClustersSameCylinder(int firstCluster, std::vector<int> marked) {
    std::vector<int> clusters;

    int cylinder0, track0, sector0;
    disk->toPhysical(firstCluster, cylinder0, track0, sector0);

    for(int track = 0; track < disk->tracksPerCylinder; ++track) {
        int ind = disk->fromPhysical(cylinder0, track, sector0);
        bool isFree = true;

        for(int i = 0; i < clusterSize; ++i) {
            if(sectors[ind + i].used || std::find(marked.begin(), marked.end(), ind) != marked.end()) {
                isFree = false;
                break;
            }
        }

        if(isFree)
            clusters.push_back(ind);
    }

    return clusters;
}


std::vector<int> FatTable::findFreeClusters(int nClusters) {
    std::vector<int> clusters;

    while(nClusters > 0) {
        int firstCluster = findFirstFreeCluster(clusters);

        if(firstCluster == -1)
            return std::vector<int>();

        std::vector<int> clustersCylinder = findFreeClustersSameCylinder(firstCluster, clusters);

        if(clustersCylinder.size() >= nClusters) {
            while (clustersCylinder.size() > nClusters)
                clustersCylinder.pop_back();

            for (int ind : clustersCylinder)
                clusters.push_back(ind);
            return clusters;
        }

        for (int ind : clustersCylinder) {
            clusters.push_back(ind);
        }
        nClusters -= clustersCylinder.size();
    }
}

bool FatTable::readFile(std::string name, std::vector<char> &buffer) {
    buffer.clear();

    auto entry = searchFile(name);
    if(entry == nullptr)
        return false;

    buffer.clear();
    int firstSector = entry->firstSector;

    FatSectorEntry sectorEntry(0, 0, firstSector);
    int sector;
    int n_iter = 0;

    do {
        sector = sectorEntry.next;
        sectorEntry = sectors[sector];

        const Sector &diskSector = disk->sectors[sector];
        for(int i = 0; i < SIZE_SECTOR_IN_BYTES; ++i)
            buffer.push_back(diskSector.data[i]);

        ++n_iter;
    } while(sectorEntry.eof != 1 && n_iter < 1000000);

    if(n_iter >= 1000000) {
        buffer.clear();
        std::cout << "INFINITE LOOPS" << std::endl;
        return false;
    }
    buffer.resize(entry->size);
    return true;
}
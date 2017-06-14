#include "disk.h"

Disk::Disk(int tracksPerSurface, int tracksPerCylinder, int sectorsPerTrack, int blockSize) :
    tracksPerSurface(tracksPerSurface),
    tracksPerCylinder(tracksPerCylinder),
    sectorsPerTrack(sectorsPerTrack),
    blockSize(blockSize),
    sectorsTotal(tracksPerSurface * tracksPerCylinder * sectorsPerTrack),
    sectors(tracksPerSurface * tracksPerCylinder * sectorsPerTrack) {


}

int Disk::from_physical(int cylinder, int track, int sector) {
    return
        cylinder * sectorsPerTrack * tracksPerCylinder +
        track * sectorsPerTrack +
        sector;
}

void Disk::to_physical(int sectorIndex, int &cylinder, int &track, int &sector) {
    cylinder = sectorIndex / (sectorsPerTrack * tracksPerCylinder);
    sectorIndex = sectorIndex % (sectorsPerTrack * tracksPerCylinder);

    track = sectorIndex / sectorsPerTrack;
    sector = sectorIndex % sectorsPerTrack;
}


int Disk::find_free_sector(int sectorIndex, int blockSize) {
    if(sectorIndex % blockSize != 0)
        sectorIndex += blockSize - sectorIndex % blockSize;

    for(int i = sectorIndex; i < sectorsTotal; i += blockSize) {
        if(sectors[i] == 0)
            return i;
    }
    return -1;
}

int Disk::find_free_sector(int cylinder, int track, int sector, int blockSize) {
    int sectorIndex = from_physical(cylinder, track, sector);
    return find_free_sector(sectorIndex, blockSize);
}

void Disk::set_sector(int sectorIndex, int value) {
    sectors[sectorIndex] = value;
}

void Disk::set_sector(int cylinder, int track, int sector, int value) {
    int sectorIndex = from_physical(cylinder, track, sector);
    set_sector(sectorIndex, value);
}

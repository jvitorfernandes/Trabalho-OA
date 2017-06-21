//
// Created by diogenes on 20/06/17.
//

#include "disk.hpp"
#include <cstring>

Disk::Disk(int tracksPerSurface, int tracksPerCylinder, int sectorsPerTrack) :
        tracksPerSurface(tracksPerSurface),
        tracksPerCylinder(tracksPerCylinder),
        sectorsPerTrack(sectorsPerTrack),
        sectorsTotal(tracksPerSurface * tracksPerCylinder * sectorsPerTrack),
        sectors(tracksPerSurface * tracksPerCylinder * sectorsPerTrack) {

}

int Disk::fromPhysical(int cylinder, int track, int sector) {
    return
        cylinder * sectorsPerTrack * tracksPerCylinder +
        track * sectorsPerTrack +
        sector;
}

void Disk::toPhysical(int sectorIndex, int &cylinder, int &track, int &sector) {
    cylinder = sectorIndex / (sectorsPerTrack * tracksPerCylinder);
    sectorIndex = sectorIndex % (sectorsPerTrack * tracksPerCylinder);

    track = sectorIndex / sectorsPerTrack;
    sector = sectorIndex % sectorsPerTrack;
}

void Disk::setSector(int sectorIndex, const char * buffer) {
    Sector &sector = sectors[sectorIndex];
    memcpy(sector.data, buffer, SIZE_SECTOR_IN_BYTES);
}

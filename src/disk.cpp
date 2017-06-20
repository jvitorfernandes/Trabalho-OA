//
// Created by diogenes on 20/06/17.
//

#include "disk.hpp"

Disk::Disk(int tracksPerSurface, int tracksPerCylinder, int sectorsPerTrack) :
        tracksPerSurface(tracksPerSurface),
        tracksPerCylinder(tracksPerCylinder),
        sectorsPerTrack(sectorsPerTrack),
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

void Disk::set_sector(int sectorIndex, int value) {
    sectors[sectorIndex] = value;
}

void Disk::set_sector(int cylinder, int track, int sector, int value) {
    int sectorIndex = from_physical(cylinder, track, sector);
    set_sector(sectorIndex, value);
}

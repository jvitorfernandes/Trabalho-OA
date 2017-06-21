//
// Created by diogenes on 20/06/17.
//

#ifndef DISK_HPP
#define DISK_HPP


#include <vector>
#include "default_params.hpp"

typedef struct Sector {
    char data[SIZE_SECTOR_IN_BYTES];
} Sector;

class Disk {
public:
    Disk(
            int tracksPerSurface = TRACKS_PER_SURFACE,
            int tracksPerCylinder = TRACKS_PER_CILINDER,
            int sectorsPerTrack = SECTORS_PER_TRACK);

    int fromPhysical(int cylinder, int track, int sector);
    /* Gives the sector index given the physical coordinates. */

    void toPhysical(int sectorIndex, int &cylinder, int &track, int &sector);
    /* Returns the physical coordinates given the sector number. */

    void setSector(int sectorIndex, const char *buffer);
    /* Sets the value of the given sector */

    /* Should implement this as getter/setter methods, but ain't no time for that */
    int tracksPerSurface, tracksPerCylinder, sectorsPerTrack;
    int sectorsTotal;

    std::vector<Sector> sectors;
};

#endif // DISK_HPP

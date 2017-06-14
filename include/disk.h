#ifndef DISK_H
#define DISK_H

#include <vector>

class Disk {
public:
    Disk(int tracksPerSurface, int tracksPerCylinder, int sectorsPerTrack, int blockSize = 1);

    int from_physical(int cylinder, int track, int sector);
    /* Gives the sector index given the physical coordinates. */

    void to_physical(int sectorIndex, int &cylinder, int &track, int &sector);
    /* Returns the physical coordinates given the sector number. */

    int find_free_sector(int sectorIndex, int blockSize = 1);
    /* Finds the first free sector, starting from the given sector. */

    int find_free_sector(int cylinder, int track, int sector, int blockSize = 1);
    /* Finds the first free sector, starting from the given physical coordinates. */

    void set_sector(int sectorIndex, int value);
    /* Sets the value of the given sector */

    void set_sector(int cylinder, int track, int sector, int value);
    /* Sets the value of the sector with the given physical coordinates. */
private:
    int tracksPerSurface, tracksPerCylinder, sectorsPerTrack, blockSize;
    int sectorsTotal;

    std::vector<int> sectors;
};

#endif // DISK_H

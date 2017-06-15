#ifndef LIBDRIVE_H
#define LIBDRIVE_H

#define TRACKS_PER_CILINDER 5
#define SECTORS_PER_TRACK 60
#define TRACKS_PER_SURFACE 10
#define SIZE_SECTOR 512
#define SIZE_CLUSTER 4
#define TIME_SEEK_AVR 4
#define TIME_SEEK_MIN 1
#define TIME_LATENCY_AVR 6
#define TIME_TRANSFER 12

#define MAX_SECTORS (TRACKS_PER_CILINDER * TRACKS_PER_SURFACE * SECTORS_PER_TRACK)
#define MAX_FILES 10

#include <string>

using namespace std;

typedef struct FatFileEntry {
    string file_name;
    int first_sector;
} FatFileEntry;

typedef struct FatSectorEntry {
    int used;
    int eof;
    int next;
} FatSectorEntry;

typedef struct FatTable {
    FatFileEntry entries[MAX_FILES];
    FatSectorEntry sectors[MAX_SECTORS];
    int number_files;
} FatTable;

/**
 * Gets the sector number of the given physical address
 */
int fat_physical_to_sector(int cylinder, int track, int sector);

/**
 * This function searches for the file with the given name in the FAT table,
 * returning the corresponding entry if the file is found or NULL otherwise.
 */
FatFileEntry * fat_search_file(FatTable * table, const string name);

/**
 * This function adds the contents in the buffer to the FatTable.
 */
FatFileEntry * fat_add_file(FatTable * table, const string name, const string buffer, int length);

#endif // LIBDRIVE_H

#include "libfat.h"
#include <string.h>

FatFileEntry * fat_search_file(FatTable * table, const char * name) {
    if(table == NULL)
        return NULL;
    
    // Loop sequentially through all files in the FAT table, looking for a matching name
    for(int i = 0; i < table->number_files; ++i) {
        FatFileEntry *file_entry = &(table->entries[i]);
        
        if(strcmp(file_entry->file_name, name) == 0)
            return file_entry;
    }
    
    return NULL;
}

int fat_physical_to_sector(int cylinder, int track, int sector) {
    return
        cylinder * SECTORS_PER_TRACK * TRACKS_PER_SURFACE +
        track * TRACKS_PER_SURFACE +
        sector;
}

static int _fat_search_free_cluster(FatTable * table, int start_at = 0) {
    if(table == NULL)
        return -1;
    
    int first;
    int count = 0;
    
    // Looking for SIZE_CLUSTER contiguous unused sectors
    for(int i = start_at; i < MAX_SECTORS; ++i) {
        FatSectorEntry * entry = &(table->sectors[i]);
        
        if(count == 0)
            first = i;
        
        if(!entry->used)
            ++count;
        else
            count = 0;
        
        if(count == SIZE_CLUSTER)
            return first;
    }
    
}

FatFileEntry * fat_add_file(FatTable * table, const char * name, const char * buffer, int length) {
    if(fat_search_file(table, name) != NULL)
        return NULL;
    
    
}

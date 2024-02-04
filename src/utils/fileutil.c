
#include "fileutil.h"
#include <stdio.h>

size_t get_filesize(char *filepath){
    
    FILE* fp = fopen(filepath, "r");

    if (fp == NULL){
        fprintf(stderr, "%s\n", "[!] Error opening file to get filesize");
        return 0;
    }

    fseek(fp, 0, SEEK_END);

    size_t filesize = ftell(fp);

    rewind(fp);

    return filesize;
}

size_t load_file(char *filepath, char *buffer, size_t offset){

    // !!! Bounds checking is not done here, always gets handled by the caller

    FILE* fp = fopen(filepath, "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Error opening file to load\n");
        return 0;
    }

    fseek(fp, 0, SEEK_END);

    size_t filesize = ftell(fp);
    rewind(fp);

    size_t bytes_read = fread(buffer + offset, 1, filesize, fp);

    if (bytes_read != filesize){
        fprintf(stderr, "[!] Possibly incomplete load (%ld/%ld)\n", bytes_read, filesize);
    }

    return bytes_read;
}

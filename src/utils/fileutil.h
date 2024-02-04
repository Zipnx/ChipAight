#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

size_t get_filesize(char* filepath);
size_t load_file(char* filepath, char* buffer, size_t offset);

#endif

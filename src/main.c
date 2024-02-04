
#include "emu/cpu.h"
#include "emu/memory.h"

#include "utils/fileutil.h"

int main(void){

    struct CPU* cpu = init_cpu();

    if (cpu == NULL) return 1;

    printf("CPU: %p\n", cpu);

    printf("Filesize: %ld\n", get_filesize("./tests/junk.dat"));

    char* idk = malloc(20);

    load_file("./tests/junk.dat", idk, 0);

    printf("Data: \"%s\"\n", idk);

    return 0;
}

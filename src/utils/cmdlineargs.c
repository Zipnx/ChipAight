
#include "cmdlineargs.h"
#include <bits/getopt_core.h>
#include <stdio.h>

void print_help(char* progname){
    // TODO: Add more as i add more options

    // First print the usage
    print_usage(progname);

    // The explain the args
    fprintf(stderr, "\nChipAight - A minimalist (barely working) Chip 8 emulator\n");

    return;
}

void print_usage(char* progname){

    fprintf(stderr, "Usage: %s [ROMFILE]\n", progname);

    return;
}

bool handle_arg(struct CmdParams* params, int opt, char** args, int argcount){
    
    switch (opt){

    case 'h':
        print_help(args[0]);
        return false;

    }

    return true;
}

void fill_default_args(struct CmdParams *params){
    
    params->windowWidth = 512;
    params->windowHeight = 256;

    params->screenDisplay = true;

}

struct CmdParams* parse_args(int argc, char** argv){
    
    if (argc < 2) {
        print_usage(argv[0]);
        return NULL;
    }

    struct CmdParams* parsed = (struct CmdParams*)malloc(sizeof (struct CmdParams));

    if (parsed == NULL){
        fprintf(stderr, "[!] Error allocating memory to parse cmdline arguments\n");
        return NULL;
    }

    fill_default_args(parsed);

    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1){

        if (!handle_arg(parsed, opt, argv, argc)){
            free(parsed);
            return NULL;
        }


    }
    
    
    if (optind < argc){
        parsed->rompath = argv[optind];
    }

    if (parsed->rompath == NULL){
        fprintf(stderr, "[!] No romfile supplied\n");
        free(parsed);
        return NULL;
    }

    return parsed;
}

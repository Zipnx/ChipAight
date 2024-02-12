#ifndef CMDLINEARGS_H
#define CMDLINEARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>

struct CmdParams {
    
    // Path to the specified rom file to run
    char* rompath;

    int windowWidth;
    int windowHeight;

    bool screenDisplay;

};

void print_help(char* progname);
void print_usage(char* progname);

void fill_default_args(struct CmdParams* params);

bool handle_arg(struct CmdParams* params, int opt, char** args, int argcount);

struct CmdParams* parse_args(int argc, char** argv);

#endif

#include "gyb.h"
#define gyb_help "gyb interpreter\n    <input.gyb>    run the *.gyb file using the gyb interpreter\n    -v             print version information\n    -h             print this help dialog\n    -d             parse a *.gyb file and print out the disassembly\n"
#define gyb_version "gyb 0.0.0\n"

void boot(int argc, uint8_t **argv) {
    ture_t *ture = init_ture(); 
    run_load(ture, argv[1]);
    ture_print_heap(ture);
    run_argv(ture, argc, argv);
    ture_print_heap(ture);
    ture_print_stack(ture);
    run_ture(ture); exit(0);
}

void inspect(int argc, uint8_t **argv) {
    ture_t *ture = init_ture(); run_dasm(ture, argv[2]); exit(0);
}

int main(int argc, uint8_t **argv) {
    switch(argc) {
        case 1: error(gyb_help); break;
        case 2:
            // if given flags 
            if(argv[1][0] == '-') {
                if (argv[1][2] != 0) { error("gyb given unknown flag \"%s\"\n", argv[1]); }
                switch(argv[1][1]) {
                case 'v': printf(gyb_version); exit(0); break;
                case 'h': printf(gyb_help); exit(0); break;
                case 'd': error("gyb disassembly requires a filename after the \"-d\" flag\n"); break;
                default: error("gyb given unknown flag \"-%c\"\n", argv[1][1]); break;
                }}
            // else given a file with no arguments
            else { boot(argc, argv); }
            break;
        default:
            if ( argv[1][0] == '-' ) {
                if (argv[1][1] == 'd' && argv[1][2] == 0 ) { inspect(argc, argv); } 
                else { error("gyb given unknown flag \"%s\"\n", argv[1]); }
            } else { boot(argc, argv); } break;
    }
    return 0;
}
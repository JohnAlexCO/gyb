#include "gyb.h"

/*void instr(uint8_t opcode, uint8_t arg0, uint16_t arg1, uint64_t arg2){
    instruction_t *instruction = (instruction_t*)malloc(sizeof(instruction_t));
    instruction->opcode=opcode; 
    instruction->arg0 = arg0; instruction->arg1 = arg1;
    if ( opcode < 0x99 ) { instruction->arg2 = arg2; }
    print_instruction(instruction); free(instruction);
}*/

#define gyb_help "gyb interpreter\n    <input.gyb>    run the *.gyb file using the gyb interpreter\n    -v             print version information\n    -h             print this help dialog\n    -d             parse a *.gyb file and print out the disassembly\n"
#define gyb_version "gyb 0.0.0\n"

int main(int argc, uint8_t **argv) {
    ture_t *ture = init_ture(); run_argv(ture, argc, argv);
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
            else { run_load(ture, argv[1]); run_ture(ture); exit(0); }
            break;
        default:
            if ( argv[1][0] == '-' ) {
                if (argv[1][1] == 'd' && argv[1][2] == 0 ) { run_dasm(ture, argv[2]); } 
                else { error("gyb given unknown flag \"%s\"\n", argv[1]); }
            } else { run_load(ture, argv[1]); run_ture(ture); exit(0); } break;
    }
    return 0;
}
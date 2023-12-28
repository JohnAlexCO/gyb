#include "include.h"
/*
    TODO LIST:
    - Opcodes: syscall and interrupt 
    - Syscalls: read and write, modify close
*/
int main ( int argc, char *argv[]){
    ifEndian(); init(argc, argv);
    stepper();
    return 0;
}
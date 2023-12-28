#include "brk.c"
#include "file.c"

/*
            file.c
    0   read    <- Not implemented
    1   write   <- Only partially implemented
    2   open
    3   close
    8   lseek
            brk.c
    12  brk
            syscall.c
    60  exit

*/

void syscall_exit(){
    integer code = *(integer*)breg.value;
    exit(code);
}
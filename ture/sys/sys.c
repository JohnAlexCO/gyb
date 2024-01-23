#include "read.c"
#include "write.c"
#include "open.c"
#include "close.c"
#include "brk.c"
#include "exit.c"

void init_fdtable(){
    for(int i=3; i < fd_table_size-1;i++){ fd_table[i] = NULL; }
    for(int i=0; i < 3; i++){ 
        fd_table[i] = (file_t*)malloc(sizeof(file_t));
        switch(i) { 
            case 0: strncpy(fd_table[i]->name, "stdin", 5); break; 
            case 1: strncpy(fd_table[i]->name, "stdout", 6); break; 
            case 2: strncpy(fd_table[i]->name, "stderr", 6); break; 
        }
        fd_table[i]->content = malloc(sizeof(uint8_t)*fd_stdbuffsize);
        fd_table[i]->index = 0;
        fd_table[i]->size = 0;
    }
}

void ture_syscall(ture_t *ture){
    //printf("syscall %x\n\ta = %lx\n\tb = %lx\n\tc = %lx\n\td = %lx\n", ture->ar, ture->ar, ture->br, ture->cr, ture->dr);
    switch(ture->ar){
        case 0: syscall_read(ture); break;
        case 1: syscall_write(ture); break;
        case 2: syscall_open(ture); break;
        case 3: syscall_close(ture); break;
        case 12: syscall_brk(ture); break;
        case 60: syscall_exit(ture); break;
        default: error("unknown syscall %d\n", ture->ar);
    }
}
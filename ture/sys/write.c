void syscall_write(ture_t *ture) {

    uint64_t fd =       ture->br;
    uint64_t buffer =   ture->cr;
    uint64_t size =     ture->dr;

    switch(fd){
        case fd_stdin:
            error("syscall_write unable to output to stdin\n"); break;
        // We don't actually care about updating the "file" for stdout and stderr, just printing 
        case fd_stderr:
            for (int i=0; i<size; i++){
                uint8_t c = ture_heap_get(ture, buffer+i, 1);
                if ( c == 0 ) { break; } fprintf(stderr, "%c", c);
            } break;
        case fd_stdout: 
            for (int i=0; i<size; i++){
                uint8_t c = ture_heap_get(ture, buffer+i, 1);
                if ( c == 0 ) { break; } printf("%c", c);
            } break;
        default:
            if(fd_table[fd] == NULL){error("syscall_write given invalid file descriptor %d\n", fd);}
            // void file_write(ture_t *ture, file_t *file, uint64_t buffer, uint64_t size);
            file_write(ture, fd_table[fd], buffer, size);
            break;  
    }
    ture->ar = size;



}
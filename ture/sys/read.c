// https://man7.org/linux/man-pages/man2/read.2.html
void syscall_read(ture_t *ture) {
    /* 
        return value is how far this syscall indexed
        getting back the content read then would basically look like 
            char *string[];
            start = (char*)file->content[file->index] - ture->ar;
            strncpy(string, start, ture->ar);
    */

    uint64_t fd =       ture->br;
    uint64_t buffer =   ture->cr;
    uint64_t size =     ture->dr;

    switch(fd){
        case fd_stdout: case fd_stderr:
            error("syscall_read unable to read into stdout or stderr\n"); break;
        case fd_stdin:
            // Read the content from stdin to the file_t for stdin
            fd_table[fd]->index = 0;
            fgets(fd_table[fd]->content, fd_stdbuffsize, stdin);
            fd_table[fd]->index =   strnlen(fd_table[fd]->content, fd_stdbuffsize);
            // then clone it into the buffer in our heap 
            for (int i=0; i<fd_table[fd]->index; i++){
                ture_heap_set(ture, buffer+i, sizeof(uint8_t), fd_table[fd]->content[i]);
            } ture_heap_set(ture, buffer+fd_table[fd]->index+1, sizeof(uint8_t), 0);
            break;
        default:
            if(fd_table[fd] == NULL){error("syscall_read given invalid file descriptor %d\n", fd);}
            //FILE *fptr = fopen(fd_table[fd]->name, "rb"); --- line is redundant
            uint64_t x = fd_table[fd]->index; file_read(ture, fd_table[fd], buffer, size);
            size = fd_table[fd]->index - x;     // update this so it can be used as our return value
            break;
    }
    ture->ar = size;
}
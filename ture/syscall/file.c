// https://man7.org/linux/man-pages/man2/open.2.html
#define file_descriptors_g_files 32
#define file_descriptors_g_nbuf 256
#define file_descriptors_g_filebuff 1024 * 1024 * 8
typedef struct { 
    char filename[file_descriptors_g_nbuf]; 
    char *content;  
    integer flags; 
    integer mode; 
    integer offset; 
    integer size; 
} file_t;
file_t *file_descriptors[file_descriptors_g_files];
#define file_descriptors_g_stdin    0
#define file_descriptors_g_stdout   1
#define file_descriptors_g_stderr   2

#define sysopen_g_flag_r    1   // "0_RDONLY", read only
#define sysopen_g_flag_w    2   // "0_WRONLY", write only
#define sysopen_g_flag_rw   4   // "0_RDWR", allows reading and writing
#define sysopen_g_flag_a    8   // "0_APPEND", write content to the end of the file
#define sysopen_g_flag_t    16  // "0_TRUNC", deletes the content of the file if it exists
#define sysopen_g_flag_c    32  // "0_CREAT", create a file if it does not exist
void syscall_open() {
    char *filename = (char *)((char *)heap_block + *(integer*)breg.value); // Assume that breg contains a pointer (within the ture's heap) to the filename
    integer flags = *(integer*)creg.value; // Check flags and mode
    integer mode = *(integer*)dreg.value;
    integer noset = 0;  if( (flags&1) != 0 ){ noset++;} if( (flags&2) != 0 ){ noset++;} if( (flags&4) != 0 ){ noset++;}
    if(noset != 1){ fprintf(stderr, "syscall_open: flags must contain one of (0_RDONLY, 0_WRONLY, 0_RDWR)\n"); exit(1); }
    for ( int i = 3; i < file_descriptors_g_files; i++){
        if ( file_descriptors[i] != NULL ){
            strncpy(file_descriptors[i]->filename, filename, strlen(filename));
            file_descriptors[i]->flags = flags; 
            file_descriptors[i]->mode = mode; 
            file_descriptors[i]->offset = 0;
            file_descriptors[i]->size = 0;
            file_descriptors[i]->content = (char*)malloc(sizeof(char)*file_descriptors_g_filebuff);
            *(integer*)areg.value = i+3;
            return;
        }
    } fprintf(stderr, "syscall_open: unable to open new file handle\n"); exit(1);
}

void syscall_close(){
    integer fd = *(integer*)breg.value;
    if( fd < 3 && fd >= 0 ){ fprintf(stderr, "syscall_close: stdin, stdout, and stderr cannot be closed\n"); exit(1); }
    if ( file_descriptors[fd] == NULL ){ fprintf(stderr, "syscall_close: no file open with fd %d\n", fd); exit(1); }
    free(file_descriptors[fd]->content);
    file_descriptors[fd] = NULL;
}

#define syslseek_g_mode_set     1 // the modes are calld "whence" in the manpages
#define syslseek_g_mode_current 2
#define syslseek_g_mode_end     3
/*
    We're gonna slightly deviate from the standard implementation of lseek
    by saying that if the ture tries to seek outside the bounds of the file itself,
    we're just going to error out the process
*/
void syscall_lseek(){
    integer fd = *(integer*)breg.value;
    integer offset = *(integer*)creg.value;
    integer whence = *(integer*)dreg.value;
    if( file_descriptors[fd]== NULL ){ fprintf(stderr, "syscall_lseek: given invalid file descriptor %d\n", fd); exit(1); }
    switch(whence){
        case syslseek_g_mode_set: {
            if(offset > file_descriptors[fd]->size){ fprintf(stderr, "syscall_lseek: offset %d exceeds bounds of file\n", offset); exit(1); }
            file_descriptors[fd]->offset = offset;
        } break;

        case syslseek_g_mode_current: {
            if(offset > file_descriptors[fd]->size + file_descriptors[fd]->offset){ fprintf(stderr, "syscall_lseek: offset %d+%d exceeds bounds of file\n", file_descriptors[fd]->offset, offset); exit(1); }
            file_descriptors[fd]->offset += offset;
        } break;

        case syslseek_g_mode_end: {
            if(offset != 0){ fprintf(stderr, "syscall_lseek: nonzero offset from end exceeds bounds of file\n"); exit(1); }
            file_descriptors[fd]->offset = file_descriptors[fd]->size;
        }

        default: {
            fprintf(stderr, "syscall_lseek: given invalid whence value\n", fd); exit(1);
        } break;
        
    }
}

void syscall_read(){
    integer fd;
    integer buffer;
    integer size;

    fprintf(stderr, "syscall_read: read syscall not yet implemented\n"); exit(1);
}
void syscall_write(){
    integer fd = *(integer*)breg.value;
    integer buffer = *(integer*)creg.value;
    integer size = *(integer*)dreg.value;
    switch(fd){
        case file_descriptors_g_stdin: {
            fprintf(stderr, "syscall_write: not allowed to write to stdin\n"); exit(1);
        } break;
        case file_descriptors_g_stdout: {
            if ( buffer+size > *(integer*)kreg.value ) { fprintf(stderr, "syscall_write: sigsegfault given buffer 0x%x and size %d\n", buffer, size); exit(1); }
            for(int i=buffer; i<buffer+size; i++){
                fprintf(stdout, (char*)(heap_block + i));
            }
        } break;
        case file_descriptors_g_stderr: {
            if ( buffer+size > *(integer*)kreg.value ) { fprintf(stderr, "syscall_write: sigsegfault given buffer 0x%x and size %d\n", buffer, size); exit(1); }
            for(int i=buffer; i<buffer+size; i++){
                fprintf(stderr, (char*)(heap_block + i));
            }
        } break;
        default: {
            if (file_descriptors[fd] == NULL ) { fprintf(stderr, "syscall_write: given invalid file descriptor %d\n", fd); exit(1); }
            fprintf(stderr, "syscall_write: writing to real file not yet implemented\n"); exit(1);
        } break; 
    }
}

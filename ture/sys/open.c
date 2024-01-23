#define fd_open_buffersize 1024 * 1024 * 4
void syscall_open(ture_t *ture) {

    uint64_t buffer = ture->br;
    uint64_t fd = 0;

    FILE *fp = fopen((char*)(buffer + ture->heap), "rb+");
    if ( fp == NULL ) { 
        ture->ar = -1; 
        fprintf(stderr, "syscall_open failed to open file, returning -1\n"); 
        return; 
    }
    fclose(fp);
    for(uint64_t i=3; i<fd_table_size;i++){
        if(fd_table[i]==NULL) {
            // make the file handle 
            fd_table[i]->content = (char*)malloc(fd_open_buffersize*sizeof(uint8_t));
            strncpy(fd_table[i]->name, (char*)(buffer + ture->heap), 64);
            fd_table[i]->index = 0;
            fd_table[i]->size = 0;
            // then return 
            ture->ar = i; return;
        }
    } error("syscall_open unable to create file handle\n");
    
}
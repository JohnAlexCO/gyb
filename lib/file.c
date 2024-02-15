/*typedef struct {
    char name[255];
    char *content;
    uint64_t index;
} file_t;*/

void file_read  (ture_t *ture, file_t *file, uint64_t buffer, uint64_t size) {
    FILE *fp = fopen(file->name, "rb"); if ( fp == NULL ) { error("unable to open file"); }
    fseek(fp, file->index, SEEK_SET); // clone file over 
    char *tmp = (void*)malloc(sizeof(uint8_t) * size + 1); fread(tmp, 1, size, fp);
    for(int i=0; i<size; i++) { ture_heap_set(ture, buffer+i, 1, tmp[i]); }
    uint64_t end = ftell(fp); // put seek distance into ar, then update fd index
    ture->ar = end - file->index;
    file->index = end;
    fclose(fp); free(tmp);
}

void file_write (ture_t *ture, file_t *file, uint64_t buffer, uint64_t size) {
    FILE *fp = fopen(file->name, "w+"); if ( fp == NULL ) { error("unable to open file"); }
    fseek(fp, file->index, SEEK_SET); // clone file over 
    for(int i=0; i<size; i++) { fprintf(fp, "%c", ture_heap_get(ture, buffer+i, 1)); }
    uint64_t end = ftell(fp); // put seek distance into ar, then update fd index
    ture->ar = end - file->index;
    file->index = end;
}
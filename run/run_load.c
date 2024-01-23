void run_load(ture_t *ture, char *filename) {
    /* 
        ture->ir will hold the address where argv ends after init_argv is called,
        if it isn't in a "nice" spot, though, move it over a little 
    */
    uint64_t address = ture->ir;
    uint64_t offset = 8-(address%8);
    address +=  offset; ture->kr += offset; ture->ir += offset;

    // Read File into Memory 
    FILE *file = fopen(filename, "rb"); // Create file handle 
    if ( file == NULL ) { error("gyb unable to open file \"%s\"\n", filename); }
    fseek(file, 0, SEEK_END); // Get file length 
    uint64_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *buffer = (uint8_t *)malloc(file_size); // Read the file into a buffer of uint8_t
    if (buffer == NULL) { error("Unable to allocate memory for file read\n"); }
    fread(buffer, sizeof(uint8_t), file_size, file); // Read the file into our buffer and close it 
    fclose(file);

    // Then move the program into our heap 
    ture->kr += file_size; ture->heap = realloc(ture->heap, ture->kr);
    for(uint64_t i=0; i<file_size;i++){ ture->heap[address+i] = buffer[i]; }
}
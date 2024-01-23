void run_dasm(ture_t *ture, char *filename) {

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

    // Then begin disassembly
    uint64_t cursor = 0;
    while ( cursor < file_size ) {
        uint64_t opcode =   (uint64_t)*(uint8_t*)(buffer + cursor);
        uint64_t arg0  =   (uint64_t)*(uint8_t*)(buffer + cursor + 1);
        uint64_t arg1  =   (uint64_t)*(uint16_t*)(buffer + cursor + 2);
        uint64_t arg2  =   (uint64_t)*(uint64_t*)(buffer + cursor + 4);
        //if ( instruction->opcode < 0x99 ) { cursor += (96/8); } else { cursor += (32/8); }
        print_opname(opcode);
        if (opcode < 0x99) { printf(" %u %lx\n", arg0, arg2); cursor += (96/8); } 
        else { printf(" %u %u\n", arg0, arg1); cursor += (32/8); }
    }

}
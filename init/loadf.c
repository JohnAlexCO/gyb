char *init_loadf_readFile(char *filePath);
char *help = "gyb version 0.0.0 -- usage: gyb <*.gyb file>\n";
char *version = "gyb version 0.0.0\n";

void init_loadf(int argc, char *argv[]){
    switch(argc){
        case 2: {
            if(strncmp(argv[1], "-h", 3)==0 || strncmp(argv[1], "--help", 7)==0){printf(help); exit(0);}
            if(strncmp(argv[1], "-v", 3)==0 || strncmp(argv[1], "--version", 10)==0){printf(version); exit(0);}
            char *content = init_loadf_readFile(argv[1]);
            *(integer*)kreg.value = strlen(content);
            heap_block = content;
        } break;
        case 1: {
            printf(help); exit(0);
        } break;
        default: {
            fprintf(stderr, "gyb expects one file as input\n"); exit(1);
        } break;
    }
}


char *init_loadf_readFile(char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) { fprintf(stderr, "gyb_init: unable to open file %s\n", filePath); exit(1); }
    // Determine the file size
    fseek(file, 0, SEEK_END);
    integer fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) { fprintf(stderr, "gyb_init: unable to allocate memory\n"); exit(1); }
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) { fprintf(stderr, "gyb_init: error reading file\n"); exit(1); }
    buffer[fileSize] = '\0';
    fclose(file);
    return buffer;
}

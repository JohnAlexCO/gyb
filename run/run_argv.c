void run_argv(ture_t *ture, int argc, uint8_t **argv) {
    uint64_t index = ture->kr; uint64_t argvx = 0; uint64_t len;
    for (uint64_t i=1; i < argc; i++) { argvx += strnlen(argv[i], 128); } ture->kr += argvx + (argc-1);
    argvx = 0; for (uint64_t i=argc-1; i > 0; i--) {
        len = strnlen(argv[i], 128);
        for(uint64_t j=0; j<len; j++){ ture->heap[index+argvx+j] = argv[i][j]; }
        ture->heap[index+argvx+len] = 0;
        ture_stack_push(ture, index+argvx); argvx += len + 1;
    }   ture_stack_push(ture, argc-1);
}
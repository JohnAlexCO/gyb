void run_argv(ture_t *ture, int argc, uint8_t **argv) {
    uint64_t argvx; uint64_t len;
    // make sure there will be room for argc/argv on the heap 
    argvx = 0;
    for (uint64_t i=1; i < argc; i++) { argvx += strnlen(argv[i], 128); } ture->kr = argvx + (argc-1);

    // Then actually initialize argc/argv starting from the last argument and moving towards the first
    argvx = 0; for (uint64_t i=argc-1; i > 0; i--) {
        len = strnlen(argv[i], 128);
        for(uint64_t j=0; j<len; j++){ ture->heap[argvx+j] = argv[i][j]; }
        ture->heap[argvx+len] = 0;
        ture_stack_push(ture, argvx); argvx += len + 1;
    }   ture_stack_push(ture, argc-1);

    // Finish up by setting the instruction pointer to where this new data ends 
    ture->ir = argvx;
}
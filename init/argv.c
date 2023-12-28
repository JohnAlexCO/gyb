// https://gist.github.com/Gydo194/730c1775f1e05fdca6e9b0c175636f5b
void init_argv(int argc, char *argv[]){
    if(argc > 32){fprintf(stderr, "init_argv: ture unable to handle more than 32 command arguments\n"); exit(1);}
    // push argc to the stack 
    integer argl = 0;
    // determine the total lengths of the cli arguments
    for(int i=0; i<argc;i++){ argl += strlen(argv[i]); }
    // allocate room in the heap for our command arguments
    *(integer*)breg.value = *(integer*)kreg.value + argl + 1;
    syscall_brk();
    // Push them onto the stack in reversed order and clone them into the heap
    integer index = *(integer*)kreg.value;
    for ( int i=argc-1; i>=0;i-- ) {
        stack_push(&index);
        strncpy(heap_block + index - strlen(argv[i]), argv[i], strlen(argv[i]));
        index -= strlen(argv[i]);    
    } stack_push(&argc);
}
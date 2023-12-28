void syscall_brk() {
    integer nbrk = *(integer*)breg.value;
    heap_block = realloc(heap_block, nbrk);
    if (heap_block == 0) { fprintf(stderr, "syscall_brk: Memory allocation failed.\n"); exit(1); } 
    *(integer*)kreg.value = nbrk;
    *(integer*)areg.value = nbrk;
}
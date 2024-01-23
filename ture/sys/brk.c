void syscall_brk (ture_t *ture) {
    uint64_t nbrk = ture->br; ture->heap = (void*)realloc(ture->heap, nbrk); 
    if (ture->heap == NULL) { error("sys_brk failed to reallocate heap\n"); }
    ture->kr = nbrk; ture->ar = nbrk;
}
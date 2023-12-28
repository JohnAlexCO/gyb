void *heap_block = NULL; // Initialize to NULL initially

void state_print(){
    printf("areg %8lx\tbreg %8lx\tcreg %8lx\tdreg %8lx\n", *(integer*)areg.value, *(integer*)breg.value, *(integer*)creg.value, *(integer*)dreg.value );
    printf("ireg %8lx\tsreg %8lx\tkreg %8lx\n", *(integer*)ireg.value, *(integer*)sreg.value, *(integer*)kreg.value );
    printf("zreg %8lx\toreg %8lx\n", *(integer*)zreg.value, *(integer*)oreg.value);
}

void heap_print() {
    /*for(int i=0; (i*8) < *(integer*)kreg.value; i++){
        if(i % 8 == 0){printf("\n");}
        printf("%8lx ", *(integer*)(heap_block + (i*8)));
    } printf("\n");*/
    printf("\nHeap: %d Bytes (%d integers, %d Bytes):", *(integer*)kreg.value, *(integer*)kreg.value/8, *(integer*)kreg.value%8);
    printf("\n-----------------------------------------------------------------------------------------------------------");
    printf("\n0  1  2  3  4  5  6  7      8  9  a  b  c  d  e  f      10 11 12 13 14 15 16 17     18 19 1a 1b 1c 1d 1e 1f");
    printf("\n-----------------------------------------------------------------------------------------------------------");
    for(int i=0; i < *(integer*)kreg.value; i++){
        if (i % 32 == 0) {printf("\n");} 
        else { if(i % 8 == 0){printf("    ");}}
        printf("%02x ", *(char*)(heap_block + i));
    } printf("\n");
}

/*
    STACK USAGE:
    Push the number value of x onto the stack
        int x = 0; stack_push(&x); -> stack[sreg-1] = 0
    Pop a value from the stack into a number
        int y = 0; stack_pop(&y); -> y = 255
    Print the current content of the stack
        stack_print();
*/
void *stack_block[stack_size];
void stack_print(){
    printf("Stack %d: ", *(integer*)sreg.value);
    for(int i=0; i<*(integer*)sreg.value; i++){
        integer *current = (integer *)(stack_block + i * sizeof(integer));
        printf("%08x ", *current);
    } printf("\n");
}
void stack_push(void *source) { 
    if (*(integer*)sreg.value >= stack_size) { printf("%d:\tStackoverflow Error\n", ireg.value); exit(1); }
    void *dest = stack_block + (*(integer*)sreg.value * sizeof(integer));
    memcpy(dest, source, sizeof(integer));
    (*(integer*)sreg.value)++;
}
void stack_pop(void *dest){
    if (*(integer*)sreg.value <= 0) { printf("%d:\tStackunderflow Error\n", ireg.value); exit(1); }
    (*(integer*)sreg.value)--;
    void *source = stack_block + (*(int*)sreg.value * sizeof(integer));
    memcpy(dest, source, sizeof(integer));
}
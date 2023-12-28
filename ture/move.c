// Move push and pop depend on "stack.c"
void register_push(number_t *reg){ stack_push(reg->value); }
void register_pop(number_t *reg){ stack_pop(reg->value); }

void move_immediate_integer(number_t *reg, integer value ){
    *(integer*)reg->value = value;
}

void move_immediate_float(number_t *reg, floater value){
    *(floater*)reg->value = value;
}

void move_register(number_t *dest, number_t *source){
    *(integer*)dest->value = *(integer*)source->value;
}

void move_load(number_t *reg, integer addr) {
    integer *x = (integer *)((char *)heap_block + addr);
    *(integer*)reg->value = *x;
}

void move_load_u8(number_t *reg, integer addr) {
    uint8_t *x = (uint8_t *)((char *)heap_block + addr);
    *(integer*)reg->value = *x;
}

void move_store(number_t *reg, integer addr) {
    integer *x = (integer *)((char *)heap_block + addr);
    *x = *(integer*)reg->value;
}

void move_store_u8(number_t *reg, integer addr) {
    uint8_t *x = (uint8_t *)((char *)heap_block + addr);
    *x = *(integer*)reg->value;
}


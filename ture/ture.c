ture_t *init_ture(){
    ture_t *result =    (ture_t*)malloc(sizeof(ture_t));
    result->heap =      (uint8_t*)malloc(sizeof(uint8_t)*default_heapsize);
    result->stack =     (uint64_t*)malloc(sizeof(uint64_t)*default_stacksize);
    result->ar = 0; result->br = 0; result->cr = 0; result->dr = 0;
    result->zero = false;           result->carry = false;
    result->kr = 0; result->ks = default_stacksize;
    result->ir = 0; result->sr = 0;
    return result;
}

uint64_t ture_register_get(ture_t *ture, uint64_t n_register) {
    switch(n_register){
        case a_register: return ture->ar; break;
        case b_register: return ture->br; break;
        case c_register: return ture->cr; break;
        case d_register: return ture->dr; break;
        case i_register: return ture->ir; break;
        case s_register: return ture->sr; break;
        default: error("invalid register 0x%x (%d)\n", n_register, n_register);
    }
}

void ture_register_set(ture_t *ture, uint64_t n_register, uint64_t value){
    switch(n_register){
        case a_register: ture->ar = value; break;
        case b_register: ture->br = value; break;
        case c_register: ture->cr = value; break;
        case d_register: ture->dr = value; break;
        case i_register: ture->ir = value; break;
        case s_register: ture->sr = value; break;
        default: error("invalid register 0x%x (%u)\n", n_register, n_register);
    }
}

void ture_stack_push(ture_t *ture, uint64_t value) { 
    if (ture->ks <= ture->sr) { ture->ks *=2; ture->stack = (uint64_t*)realloc(ture->stack, sizeof(uint64_t)*ture->ks); } // realloc if big enough
    ture->stack[ture->sr] = value; ture->sr++; // then push 
}

void ture_stack_pop(ture_t *ture, uint64_t n_register) {
    if (ture->ks > (ture->sr * 2)) { ture->ks /=2; ture->stack = (uint64_t*)realloc(ture->stack, sizeof(uint64_t)*ture->ks); } // dealloc if small enough
    if (ture->sr <= 0){ error("stack underflow error\n"); } // // then pop 
    ture->sr--; uint64_t value = ture->stack[ture->sr];
    ture_register_set(ture, n_register, value);
}

uint64_t ture_heap_get(ture_t *ture, uint64_t addr, uint64_t size){
    if(addr+size > ture->kr){ error("segmentation fault at 0x%x (%d)\n", addr, addr); }
    uint64_t value = 0;
    uint64_t base_address = (uint64_t)ture->heap + addr;
    switch(size){
        case 1: value = *(uint8_t*)base_address; break;
        case 2: value = *(uint16_t*)base_address; break;
        case 4: value = *(uint32_t*)base_address; break;
        case 8: value = *(uint64_t*)base_address; break;
        default: error("heap_get unable to use size %d\n", size);
    } return value;
}

void ture_heap_set(ture_t *ture, uint64_t addr, uint64_t size, uint64_t value) {
    if(addr+size > ture->kr){ error("segmentation fault at 0x%x (%d)\n", addr, addr); }
    uint64_t base_address = (uint64_t)ture->heap + addr;
    switch (size) {
        case 1: *(uint8_t*)base_address = (uint8_t)value; break;
        case 2: *(uint16_t*)base_address = (uint16_t)value; break;
        case 4: *(uint32_t*)base_address = (uint32_t)value; break;
        case 8: *(uint64_t*)base_address = value; break;
        default: error("heap_set unable to use size %d\n", size);
    }
}

void ture_print_stack(ture_t *ture){
    printf("STACK [0x%llx]:", ture->stack, ture->sr);
    for(int i=0; i < ture->sr; i++) {
        if(i%8==0) {printf("\n");}
        printf("%08x ", ture->stack[i]);
    } printf("\n");
}

void ture_print_heap(ture_t *ture) {
    printf("HEAP [0x%llx]:", ture->heap, ture->kr);
    for(uint64_t i=0; i < ture->kr; i++) {
        if(i%8==0)  {printf("  ");}
        if(i%32==0) {printf("\n");}
        char *c = (char*)(ture->heap + i);
        printf("%hhx ", *c);
    } printf("\n");
}

void ture_print_state(ture_t *ture) {
    printf("STATE: \n");
    printf("a  %016x b  %016x c  %016x d  %016x\ni  %016x s  %016x kp %016x sp %016x\n", ture->ar, ture->br, ture->cr, ture->dr, ture->ir, ture->sr, ture->kr, ture->ks);
}
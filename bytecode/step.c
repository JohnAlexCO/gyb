#define ip96 ture->ir += (96/8);
#define ip32 ture->ir += (32/8);
#define ipa2 ture->ir = instruction->arg2

void step(ture_t *ture){

    instruction_t *instruction = fetch_instruction(ture); uint64_t value;
    uint64_t opcode =   (uint64_t)*(uint8_t*)(ture->heap + ture->ir);
    uint64_t arg0  =    (uint64_t)*(uint8_t*)(ture->heap + ture->ir + 1);
    uint64_t arg1  =    (uint64_t)*(uint16_t*)(ture->heap + ture->ir + 2);
    uint64_t arg2  =    (uint64_t)*(uint64_t*)(ture->heap + ture->ir + 4);
    /*print_opname(opcode); if (opcode < 0x99) { printf(" %u %lx\n", arg0, arg2);} else { printf("\n"); }*/

    switch(instruction->opcode){
        // 96-bit Instructions
        case op_imm32:  ture_register_set(ture, arg0, arg2); ip96; break;
        case op_imm64:  ture_register_set(ture, arg0, arg2); ip96; break;
        case op_goto:   ipa2; break;
        case op_if:     if(ture->zero==true)                            { ipa2; } else { ip96; } break;
        case op_not:    if(ture->zero==false)                           { ipa2; } else { ip96; } break;
        case op_lt:     if(ture->carry==true)                           { ipa2; } else { ip96; } break;
        case op_gt:     if(ture->carry==false)                          { ipa2; } else { ip96; } break;
        case op_le:     if(ture->carry==true    || ture->zero==true)    { ipa2; } else { ip96; } break;
        case op_ge:     if(ture->carry==false   || ture->zero==true)    { ipa2; } else { ip96; } break;
        case op_load64: value = ture_heap_get(ture, arg2, 8); ture_register_set(ture, arg0, value); ip96; break;
        case op_load32: value = ture_heap_get(ture, arg2, 4); ture_register_set(ture, arg0, value); ip96; break;
        case op_load16: value = ture_heap_get(ture, arg2, 2); ture_register_set(ture, arg0, value); ip96; break;
        case op_load8: value = ture_heap_get(ture, arg2, 1); ture_register_set(ture, arg0, value); ip96; break;
        case op_store64: value = ture_register_get(ture, arg0); ture_heap_set(ture, arg2, 8, value); ip96; break;
        case op_store32: value = ture_register_get(ture, arg0); ture_heap_set(ture, arg2, 4, value); ip96; break;
        case op_store16: value = ture_register_get(ture, arg0); ture_heap_set(ture, arg2, 2, value); ip96; break;
        case op_store8: value = ture_register_get(ture, arg0); ture_heap_set(ture, arg2, 1, value); ip96; break;
        // 32-bit Instructions
        case op_imm32u: error("gyb not implementing immediate32u; use imm32 or imm64\n"); break;
        case op_imm32l: error("gyb not implementing immediate32l; use imm32 or imm64\n"); break;
        case op_add:    math_add(ture, arg0, arg1); ip32; break;
        case op_sub:    math_sub(ture, arg0, arg1); ip32; break;
        case op_mul:    math_mul(ture, arg0, arg1); ip32; break;
        case op_div:    math_div(ture, arg0, arg1); ip32; break;
        case op_left:   math_left(ture, arg0, arg1); ip32; break;
        case op_right:  math_right(ture, arg0, arg1); ip32; break;
        case op_and:    math_and(ture, arg0, arg1); ip32; break;
        case op_or:     math_or(ture, arg0, arg1); ip32; break;
        case op_xor:    math_xor(ture, arg0, arg1); ip32; break;
        case op_flip:   math_flip(ture, arg0); ip32; break;
        case op_fadd:   math_fadd(ture, arg0, arg1); ip32; break;
        case op_fsub:   math_fsub(ture, arg0, arg1); ip32; break;
        case op_fmul:   math_fmul(ture, arg0, arg1); ip32; break;
        case op_fdiv:   math_fdiv(ture, arg0, arg1); ip32; break;
        case op_interrupt: ture_syscall(ture); ip32; break;
        default: error("unknown instruction opcode 0x%x (%d) at %d\n", instruction->opcode, instruction->opcode, ture->ir);
    }
}

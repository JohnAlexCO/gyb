integer step_next(){
    integer* instructionPtr = (integer*)heap_block;
    integer instruction = littleEndian(instructionPtr[ *(integer*)ireg.value ]);
    *(integer*)ireg.value = *(integer*)ireg.value+1;
    return instruction;
}

number_t *regc(integer regn){
    switch(regn){
        case regn_a: return &areg; break;
        case regn_b: return &breg; break;
        case regn_c: return &creg; break;
        case regn_d: return &dreg; break;
        case regn_s: return &sreg; break;
        case regn_k: return &kreg; break;
        default: fprintf(stderr, "step_regc: given invalid register number %d\n", regn); exit(1);
    }
}

void main_step(){
    /* I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I
    hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate
    C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C I hate C
    */
    integer instruction = step_next();
    switch(instruction){
        // give syscall and interrupt their own dedicated sections

        case opb_jump:      branch_jmp(step_next()); break;
        case opb_if:        branch_if(step_next()); break;
        case opb_not:       branch_not(step_next()); break;
        case opb_lt:        branch_lt(step_next()); break;
        case opb_gt:        branch_gt(step_next()); break;
        case opb_le:        branch_le(step_next()); break;
        case opb_ge:        branch_ge(step_next()); break;

        case opm_imm:       move_immediate_integer(regc(step_next()), step_next()); break;
        case opm_immf:      move_immediate_float(regc(step_next()), step_next()); break;
        case opm_move:      move_register(regc(step_next()), regc(step_next())); break;
        case opm_load:      move_load(regc(step_next()), step_next()); break;
        case opm_load_u8:   move_load(regc(step_next()), step_next()); break;
        case opm_store:     move_store(regc(step_next()), step_next()); break;
        case opm_store_u8:  move_store(regc(step_next()), step_next()); break;

        case ops_push:      stack_push(&instruction); break;
        case ops_pop:       stack_pop(&instruction); break;

        case opa_cmp:       arithmetic_compare_integer(regc(step_next()), regc(step_next())); break;
        case opa_add:       arithmetic_add_integer(regc(step_next()), regc(step_next())); break;
        case opa_sub:       arithmetic_sub_integer(regc(step_next()), regc(step_next())); break;
        case opa_mul:       arithmetic_mul_integer(regc(step_next()), regc(step_next())); break;
        case opa_div:       arithmetic_div_integer(regc(step_next()), regc(step_next())); break;
        case opa_left:      arithmetic_left_integer(regc(step_next()), regc(step_next())); break;
        case opa_right:     arithmetic_right_integer(regc(step_next()), regc(step_next())); break;
        case opa_and:       arithmetic_and_integer(regc(step_next()), regc(step_next())); break;
        case opa_or:        arithmetic_or_integer(regc(step_next()), regc(step_next())); break;
        case opa_xor:       arithmetic_xor_integer(regc(step_next()), regc(step_next())); break;
        case opa_flip:      arithmetic_flip_integer(regc(step_next())); break;
        case opf_add:       arithmetic_add_float(regc(step_next()), regc(step_next())); break;
        case opf_sub:       arithmetic_sub_float(regc(step_next()), regc(step_next())); break;
        case opf_mul:       arithmetic_mul_float(regc(step_next()), regc(step_next())); break;
        case opf_div:       arithmetic_div_float(regc(step_next()), regc(step_next())); break;

        default: {
            fprintf(stderr, "step: given invalid opcode 0x%lx\n", instruction); exit(1);
        } break;
    }
}

void stepper(){
    while(true){
        main_step();
    }
}
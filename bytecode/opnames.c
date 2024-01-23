#define opname_case(name) \
    case op_##name: printf("%12s\t", #name); break;

void print_opname(uint64_t opcode){
    switch(opcode) {
        opname_case(syscall)
        opname_case(imm32)
        opname_case(imm64)
        opname_case(goto)
        opname_case(if)
        opname_case(not)
        opname_case(lt)
        opname_case(gt)
        opname_case(le)
        opname_case(ge)
        opname_case(imm32u)
        opname_case(imm32l)
        opname_case(load64)
        opname_case(load32)
        opname_case(load16)
        opname_case(load8)
        opname_case(store64)
        opname_case(store32)
        opname_case(store16)
        opname_case(store8)
        opname_case(compare)
        opname_case(add)
        opname_case(sub)
        opname_case(mul)
        opname_case(div)
        opname_case(left)
        opname_case(right)
        opname_case(and)
        opname_case(or)
        opname_case(xor)
        opname_case(flip)
        opname_case(fadd)
        opname_case(fsub)
        opname_case(fmul)
        opname_case(fdiv)
        opname_case(interrupt)
        default: printf("    %s\t", "unknown"); break;
    }
}

void print_instruction(instruction_t *instruction) {
    print_opname(instruction->opcode);
    printf("%02x    ", instruction->opcode);
    if (instruction->opcode > 0x1f ){ printf(" %02x ",  instruction->arg0); } else { printf("    "); }
    if (instruction->opcode > 0x99 ){ printf(" %04x\n", instruction->arg1); return; } 
    if (instruction->opcode < 0x99 ){ printf(" %x\n",   instruction->arg2); return; }
    printf("\n"); return;
}
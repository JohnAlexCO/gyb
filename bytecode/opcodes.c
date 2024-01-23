instruction_t *fetch_instruction(ture_t *ture) {
    uint8_t opcode  = *(uint8_t*)(ture->heap + ture->ir);
    uint64_t arg0    = (uint64_t)*(uint8_t*)(ture->heap + ture->ir + 1);
    uint64_t arg1    = (uint64_t)*(uint16_t*)(ture->heap + ture->ir + 2);
    uint64_t arg2    = (uint64_t)*(uint64_t*)(ture->heap + ture->ir + 4);
    instruction_t *result = malloc(sizeof(instruction_t));
        result->opcode  = opcode;
        result->arg0    = arg0;
        result->arg1    = arg1;
    // a0 through ff for 32-bit instructions, 00 through 99 for 96-bit
    if (opcode > 0x99) { result->arg2 = arg2; }
    return result;
}
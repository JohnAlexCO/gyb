void branch_jmp(integer addr){
    *(integer*)ireg.value = addr;
}

void branch_if(integer addr){
    if( *(integer*)zreg.value == 0 ) { *(integer*)ireg.value = addr; }
}

void branch_not(integer addr){
    if( *(integer*)zreg.value != 0 ) { *(integer*)ireg.value = addr; }
}

void branch_lt(integer addr){
    if( *(integer*)zreg.value == 0 && // not equal, is carry 
        *(integer*)oreg.value != 0
    ) { *(integer*)ireg.value = addr; }
}

void branch_gt(integer addr){
    if( *(integer*)zreg.value != 0 && // not equal, not carry
        *(integer*)oreg.value != 0
    ) { *(integer*)ireg.value = addr; }
}

void branch_le(integer addr){
    if( *(integer*)oreg.value == 0 ) { *(integer*)ireg.value = addr; }
}

void branch_ge(integer addr){
    if( *(integer*)oreg.value != 0 ) { *(integer*)ireg.value = addr; }
}
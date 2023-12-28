/*void arithmetic_add_int(number_t *dest, number_t *source){
    integer base =  *(integer*)dest->value;
    integer adder = *(integer*)source->value;
    move_immediate_integer(dest, base+adder);
}*/
#define arithmetic_new_integer(name, op) \
    void arithmetic_##name##_integer(number_t *dest, number_t *source) { \
        integer base = *(integer*)dest->value; \
        integer adder = *(integer*)source->value; \
        move_immediate_integer(dest, base op adder); \
    }

void arithmetic_compare_integer(number_t *dest, number_t *source){
    integer base = *(integer*)dest->value;
    integer adder = *(integer*)source->value;
    if (base < adder) { *(integer*)oreg.value = 1; } else { *(integer*)oreg.value = 0; }
    if (base == adder) { *(integer*)zreg.value = 1; } else { *(integer*)zreg.value = 0; }
    move_immediate_integer(dest, base - adder);
}

void arithmetic_flip_integer(number_t *dest){
    integer base = *(integer*)dest->value;
    move_immediate_integer(dest, ~base);
}

arithmetic_new_integer(add, +);
arithmetic_new_integer(sub, -);
arithmetic_new_integer(mul, *);
arithmetic_new_integer(div, /);
arithmetic_new_integer(left,  <<);
arithmetic_new_integer(right, >>);
arithmetic_new_integer(and, &);
arithmetic_new_integer(or,  |);
arithmetic_new_integer(xor, ^);

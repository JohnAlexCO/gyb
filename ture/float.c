/*void arithmetic_add_float(number_t *dest, number_t *source){
    floater base =  *(floater*)dest->value;
    floater adder = *(floater*)source->value;
    move_immediate_float(dest, base+adder);
}*/
#define arithmetic_new_float(name, op) \
    void arithmetic_##name##_float(number_t *dest, number_t *source) { \
        floater base = *(floater*)dest->value; \
        floater adder = *(floater*)source->value; \
        move_immediate_float(dest, base op adder); \
    }

arithmetic_new_float(add, +);
arithmetic_new_float(sub, -);
arithmetic_new_float(mul, *);
arithmetic_new_float(div, /);
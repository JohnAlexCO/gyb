#define math_integer(name, symbol) \
    void math_##name(ture_t *ture, uint64_t dest, uint64_t src) { \
        uint64_t base =     ture_register_get(ture, dest); \
        uint64_t adder =    ture_register_get(ture, src); \
        uint64_t value =    base symbol adder; \
        if (value > big_int/2) { ture->carry = true; } else { ture->carry = false; } \
        if (value == 0 ) { ture->zero = true; } else { ture->zero = false; } \
        ture_register_set(ture, dest, value); \
    }

#define math_float(name, symbol) \
    void math_##name(ture_t *ture, uint64_t dest, uint64_t src) { \
        double base =       (double)(uint64_t)ture_register_get(ture, dest); \
        double adder =      (double)(uint64_t)ture_register_get(ture, src); \
        double value =      base symbol adder; \
        ture_register_set(ture, dest, (uint64_t)(double)value); \
    }

void math_flip(ture_t *ture, uint64_t dest) {
    uint64_t value = ~ture_register_get(ture, dest);
    ture_register_set(ture, dest, value);
}

math_integer(add,   +)
math_integer(sub,   -)
math_integer(cmp,   -)
math_integer(mul,   *)
math_integer(div,   /)
math_integer(left,  <<)
math_integer(right, >>)
math_integer(and,   &)
math_integer(or,    |)
math_integer(xor,   ^)

math_float(fadd,    +)
math_float(fsub,    -)
math_float(fmul,    *)
math_float(fdiv,    /)
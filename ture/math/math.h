#define big_int 0xffffffffffffffff

void math_cmp   (ture_t *ture, uint64_t dest, uint64_t src);
void math_add   (ture_t *ture, uint64_t dest, uint64_t src);
void math_sub   (ture_t *ture, uint64_t dest, uint64_t src);
void math_mul   (ture_t *ture, uint64_t dest, uint64_t src);
void math_div   (ture_t *ture, uint64_t dest, uint64_t src);
void math_left  (ture_t *ture, uint64_t dest, uint64_t src);
void math_right (ture_t *ture, uint64_t dest, uint64_t src);
void math_and   (ture_t *ture, uint64_t dest, uint64_t src);
void math_or    (ture_t *ture, uint64_t dest, uint64_t src);
void math_xor   (ture_t *ture, uint64_t dest, uint64_t src);

void math_fadd  (ture_t *ture, uint64_t dest, uint64_t src);
void math_fsub  (ture_t *ture, uint64_t dest, uint64_t src);
void math_fmul  (ture_t *ture, uint64_t dest, uint64_t src);
void math_fdiv  (ture_t *ture, uint64_t dest, uint64_t src);

void math_flip  (ture_t *ture, uint64_t dest);
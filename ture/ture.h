#define default_heapsize    1024*1024 // make big enough to allocate program, will be reset down once done initializing
#define default_stacksize   1024

typedef struct {
    uint64_t ar; uint64_t br; uint64_t cr; uint64_t dr;
    uint64_t ir; uint64_t sr; uint64_t zero; uint64_t carry;
    uint64_t *stack; uint8_t *heap;
    uint64_t kr; uint64_t ks; // heap break, stack break
} ture_t;

ture_t     *init_ture();
uint64_t    ture_register_get(ture_t *ture, uint64_t n_register);
void        ture_register_set(ture_t *ture, uint64_t n_register, uint64_t value);
void        ture_stack_push(ture_t *ture, uint64_t value);
void        ture_stack_pop(ture_t *ture, uint64_t n_register);
uint64_t    ture_heap_get(ture_t *ture, uint64_t addr, uint64_t size);
void        ture_heap_set(ture_t *ture, uint64_t addr, uint64_t size, uint64_t value);

void        ture_print_stack(ture_t *ture);
void        ture_print_heap(ture_t *ture);
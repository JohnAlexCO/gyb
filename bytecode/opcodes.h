typedef struct {
    uint8_t     opcode;
    uint64_t    arg0;      // first byte
    uint64_t    arg1;      // second byte or word 
    uint64_t    arg2;  // optional 64-bit literal 
} instruction_t;

instruction_t *fetch_instruction(ture_t *ture);
void print_opname(uint64_t opcode);
void print_instruction(instruction_t *instruction);

//      Macro-only operations
#define op_syscall      0x81    //  syscall, arg1, arg2, arg3

//      96-bit operations
#define op_imm32        0x32    //  dest, dword ; 96-bit instruction
#define op_imm64        0x64    //  dest, qword ; 96-bit instruction
#define op_goto         0x10    //  addr
#define op_if           0x11
#define op_not          0x12
#define op_lt           0x13
#define op_gt           0x14
#define op_le           0x15
#define op_ge           0x16
#define op_load64       0x2f    //  dest, src
#define op_load32       0x2e
#define op_load16       0x2d
#define op_load8        0x2c
#define op_store64      0x29
#define op_store32      0x28
#define op_store16      0x27
#define op_store8       0x26

//      32-bit operations
#define op_imm32u       0xd1    //  dest, word
#define op_imm32l       0xd0    //  dest, word
#define op_compare      0xae    //  dest, src
#define op_add          0xa0    
#define op_sub          0xa1   
#define op_mul          0xa2
#define op_div          0xa3
#define op_left         0xa4
#define op_right        0xa5
#define op_and          0xa6
#define op_or           0xa7
#define op_xor          0xa8
#define op_flip         0xa9
#define op_fadd         0xaa
#define op_fsub         0xab
#define op_fmul         0xac
#define op_fdiv         0xad
#define op_interrupt    0xff    //  null, word

/*
    riscv name          gasm        bytemachine             real riscv
    ==========          ====        ===========             ==========
    lui                 imm32u      immediate upper 16-bits load upper 12-bits
    addi                imm32l      immediate lower 16-bits load lower 20-bits
    { none }            imm32       immediate 32-bit value  (compiles as a lui and addi instruction)
    { none }            imm64       immediate 64-bit value  (compiles as a combination of luis, addis, and an sll)
    ldu                 load64      load 64-bit from addr   (addr in a register, specifically)
    lwu                 load32      load 32-bit from addr   
    lhu "halfword"      load16      load 16-bit from addr
    lbu                 load8       load 8-bit from addr
    sd                  store64     store 64-bits to addr
    sw                  store32     store 32-bits to addr
    sh                  store16     store 16-bits to addr
    sb                  store8      store 8-bits to addr
    add
    sub
    mul
    div
    sll                 left
    srl                 right
    and                 
    or                  
    xor                 
    {  }                flip        no opcode exists, instead do xor with (-1)
    fadd.d              fadd
    fsub.d              fsub
    fmul.d              fmul
    fdiv.d              fdiv
    jal                 { none }    in gasm, load the address into ar and then jump using ar
    jalr                goto
    { beq }             if       
    { bne }             not         
    { bltu }            lt          
    {  }                le          ( probably done by manipulating the value before doing a different comparison )     
    {  }                gt          ( probably done by manipulating the value before doing a different comparison )
    { bgeu }            ge          
    {  }                interrupt   ( doing this like x86 does it instead )
    {  }                syscall     ( assembler converts to regular interrupt for us ) 
*/
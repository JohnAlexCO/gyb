#define oph             0x6F70677900000000
#define opb_jump        oph+1
#define opb_if          oph+2
#define opb_not         oph+3
#define opb_lt          oph+4
#define opb_gt          oph+5
#define opb_le          oph+6
#define opb_ge          oph+7

#define opm_imm         oph+10
#define opm_immf        oph+11
#define opm_move        oph+12
#define opm_load        oph+13
#define opm_load_u8     oph+14
#define opm_store       oph+15
#define opm_store_u8    oph+16
#define ops_push        oph+17
#define ops_pop         oph+18
#define opx_syscall     oph+19
#define opx_interrupt   oph+20

#define opa_cmp         oph+30
#define opa_add         oph+31
#define opa_sub         oph+32
#define opa_mul         oph+33
#define opa_div         oph+34
#define opa_left        oph+35
#define opa_right       oph+36
#define opa_and         oph+37
#define opa_or          oph+38
#define opa_xor         oph+39
#define opa_flip        oph+40

#define opf_add         oph+60
#define opf_sub         oph+61
#define opf_mul         oph+62
#define opf_div         oph+63
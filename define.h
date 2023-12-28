#include "opc.h"
#define true 1
#define false 0

#define byte uint8_t
#define floater      double
#define integer      unsigned long long

#define global_type_basemagic   0x67790000
#define variable_magic          global_type_basemagic + 0
#define int_magic               global_type_basemagic + 1
#define float_magic             global_type_basemagic + 2

#define stack_size              (1024 * 1024)*8
typedef struct { integer magic; byte value[sizeof(integer)]; } number_t;
number_t ireg  = {int_magic, 0}; // Instruction Ptr
number_t sreg  = {int_magic, 0}; // Stack Ptr
number_t kreg  = {int_magic, 0}; // Memory Break 
number_t oreg  = {int_magic, 0}; // Overflow Flag
number_t zreg  = {int_magic, 0}; // Zero Flag
number_t areg  = {int_magic, 0}; // General Purpose
number_t breg  = {int_magic, 0}; 
number_t creg  = {int_magic, 0}; 
number_t dreg  = {int_magic, 0};
#define regn_a      10
#define regn_b      11
#define regn_c      12
#define regn_d      13
#define regn_s      14
#define regn_k      15
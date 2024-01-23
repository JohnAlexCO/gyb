# gyb
A bytecode interpreter for the Garter &amp; Gasm programming languages

## Purpose

gyb is intended to function as a portable bytecode interpreter.
gyb's architecture is designed to be close-enough to a real machine
that an assembly language designed to target this bytecode can be 
translated to real machine-code somewhat trivially.

## Implementation

gyb is based on a "ture", 
a register-based turing computer
that runs just the process and has wrappers for common syscalls.
It has a very limited instruction set
and it's bytecode is intended to
resemble RISC-V and x86-64. 

gyb is also written in C, and will stay that way.
I plan to make *alternative versions* so that there's
more options for bootstrapping the Garter compiler-chain,
but I think having a version of gyb written in C
at every step in its life-cycle will be really important
to the accessibility of the language as a whole.

## Limitations and Scope 

gyb is only intended to run on 64-bit machines,
and building a version that runs on 32-bit computers 
isn't really in my plans. 
Additionally, the gyb interpreter can only handle
a small subset of system calls.
This program is intended to function
as part of the Garter cross-compilation stage,
and to act as a target for Gasm assembly.
Anything beyond those two goals is outside the scope of this project.
# gyb
A bytecode interpreter for the Garter &amp; Gasm programming languages

## Purpose

gyb is intended to function as a very small, portable
"virtual machine" or bytecode interpreter that is close-enough to low level machine code that translation is somewhat trivial, especially alongside the source code that generated it. An assembly language and assembler designed to target gyb should be pretty easy to transpile into something like `gas` or `nasm`, hand-compile, or emulate.

## Implementation

gyb is based on a "ture", a register-based 
turing machine which acts very much like a modern computer
but runs only the process and a minimal "kernel",
and which has a limited instruction set 
(designed to closely resemble 64-bit x86 Unix/Linux).

gyb is also written in C, and will stay that way.
I plan to make *alternative versions* so that there's
more options for bootstrapping the Garter compiler-chain,
but I think having a version of gyb written in C
at every step in its life-cycle will be really important
to the accessibility of the language as a whole.

## Limitations and Scope 

The bootstrapping version of this only works 
on some 64-bit systems. I plan to eventually make it work
on 32-bit systems, and to make the codebase more 
platform agnostic. I also plan to expand the number 
of system interrupts that work in gyb, and to make it so
the Garter assembler can output separate 
`syscall` and `interrupt` instructions and
gyb will translate them on the fly.
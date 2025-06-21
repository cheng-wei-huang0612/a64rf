#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>
#include "types.h"
#include "gpr.h"
#include "flags.h"
#include "vreg/read.h"
#include "vreg/print.h"

/* Print all general purpose registers (X0-X30) and the stack pointer. */
static inline void print_gprs(a64rf_state_t *state)
{
    for (size_t i = 0; i < XZR; ++i)
        printf("X%zu = 0x%016" PRIx64 "\n", i, state->gpr[i].val);
    printf("SP  = 0x%016" PRIxPTR "\n", state->sp.val);
}

/* Print general purpose registers followed by the NZCV flags. */
static inline void print_gprs_and_nzcv(a64rf_state_t *state)
{
    print_gprs(state);
    print_nzcv(state);
}

/* Print all vector registers using the d[0],d[1] view. */
static inline void print_vregs(a64rf_state_t *state)
{
    for (size_t i = 0; i < VREG_COUNT; ++i)
        print_vreg_as_2d(state, i);
}

/* Print vector registers followed by the FPSR value. */
static inline void print_vregs_and_fpsr(a64rf_state_t *state)
{
    print_vregs(state);
    print_fpsr(state);
}

/* Convenience routine printing all registers and flags. */
static inline void print_all_regs_and_flags(a64rf_state_t *state)
{
    print_gprs(state);
    print_nzcv(state);
    print_vregs(state);
    print_fpsr(state);
}

/* Dump the entire emulated stack. */
static inline void print_stack(a64rf_state_t *state)
{
    printf("SP  = 0x%016" PRIxPTR "\n", state->sp.val);
    for (size_t i = 0; i < STACK_SIZE; i += 16) {
        printf("stack[%04zu]:", i);
        for (size_t j = 0; j < 16 && i + j < STACK_SIZE; ++j)
            printf(" %02" PRIx8, state->stack[i + j]);
        putchar('\n');
    }
}

/* Dump the entire memory array. */
static inline void print_memory(a64rf_state_t *state)
{
    for (size_t i = 0; i < MEMORY_SIZE; i += 16) {
        printf("memory[%04zu]:", i);
        for (size_t j = 0; j < 16 && i + j < MEMORY_SIZE; ++j)
            printf(" %02" PRIx8, state->memory[i + j]);
        putchar('\n');
    }
}

/* Print both stack and memory regions. */
static inline void print_stack_and_memory(a64rf_state_t *state)
{
    print_stack(state);
    print_memory(state);
}

/* Print the full state including registers and memory. */
static inline void print_state(a64rf_state_t *state)
{
    print_all_regs_and_flags(state);
    print_stack_and_memory(state);
}

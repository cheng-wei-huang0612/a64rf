#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "../../types.h"



/* Return the current NZCV flags from the state structure. */
static inline nzcv_t read_nzcv(const a64rf_state_t *state) {
    return state->nzcv;
}

/* Display the NZCV flags in a human-friendly format. */
static inline void print_nzcv(const a64rf_state_t *state) {
    nzcv_t f = read_nzcv(state);
    printf("NZCV = N:%u Z:%u C:%u V:%u\n",
                   f.N, f.Z, f.C, f.V);
}


static inline void write_nzcv(a64rf_state_t *state, nzcv_t src_flag) {
    state->nzcv = src_flag;
}

static inline void write_zero_nzcv(a64rf_state_t *state) {
    nzcv_t src_flag;
    src_flag.word = (uint32_t)0;

    write_nzcv(state, src_flag);
}





static inline fpsr_t read_fpsr(const a64rf_state_t *state) {
    return state->fpsr;
}


static inline void print_fpsr(const a64rf_state_t *state) {
    fpsr_t f = read_fpsr(state);
    printf("QC = \n",f.QC );
}


static inline void write_fpsr(a64rf_state_t *state, fpsr_t src_fpsr) {
    state->fpsr = src_fpsr;
}

static inline void write_zero_fpsr(a64rf_state_t *state) {
    fpsr_t src_fpsr;
    src_fpsr.QC = 0;

    write_fpsr(state, src_fpsr);
}

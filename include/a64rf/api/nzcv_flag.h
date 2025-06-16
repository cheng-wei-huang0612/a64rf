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


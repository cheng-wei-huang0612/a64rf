#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "../../../types.h"



/*
 * Print the contents of a vector register as two 64-bit values.
 */
static inline void print_vreg_as_2d(const a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx) {
    printf("V%d: d[0] = 0x%016" PRIx64 ", d[1] = 0x%016" PRIx64 "\n",
        (int)vreg_idx,
        read_d_vreg_lo(state, vreg_idx),
        read_d_vreg_hi(state, vreg_idx));
}

/*
 * Print a vector register interpreted as four 32-bit words.
 */
static inline void print_vreg_as_4s(const a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx) {
    printf("V%d: s[0] = 0x%08" PRIx32 ", s[1] = 0x%08" PRIx32
           ", s[2] = 0x%08" PRIx32 ", s[3] = 0x%08" PRIx32 "\n",
        (int)vreg_idx,
        read_s_vreg(state, vreg_idx, 0),
        read_s_vreg(state, vreg_idx, 1),
        read_s_vreg(state, vreg_idx, 2),
        read_s_vreg(state, vreg_idx, 3));
}

/*
 * Print a vector register as eight 16-bit halfwords.
 */
static inline void print_vreg_as_8h(const a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx) {
    printf("V%d: ", (int)vreg_idx);
    for (int i = 0; i < 8; ++i) {
        printf("h[%d]=0x%04" PRIx16 "%s", i, read_h_vreg(state, vreg_idx, i), (i < 7) ? ", " : "\n");
    }
}

/*
 * Print a vector register as sixteen bytes.
 */
static inline void print_vreg_as_16b(const a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx) {
    printf("V%d: ", (int)vreg_idx);
    for (int i = 0; i < 16; ++i) {
        printf("b[%d]=0x%02" PRIx8 "%s", i, read_b_vreg(state, vreg_idx, i), (i < 15) ? ", " : "\n");
    }
}

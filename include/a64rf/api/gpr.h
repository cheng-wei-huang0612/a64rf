#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "../../types.h"

/*
 * Retrieve the 64-bit value stored in a general purpose register.
 *
 * \param state    Pointer to an a64rf_state_t structure.
 * \param gpr_idx  Register index to read (X0-X30).
 * \return         The value contained in the requested register.
 */
static inline uint64_t read_val_gpr(const a64rf_state_t* state, a64rf_gpr_idx_t gpr_idx) {
    if (gpr_idx >= GPR_COUNT) {
        fprintf(stderr, "Invalid GPR index %d\n", (int)gpr_idx);
        return 0;
    }
    return (gpr_idx == XZR) ? 0 : state->gpr[gpr_idx].val;
}

/*
 * Print the value of a general purpose register using the requested radix.
 * Supported radixes are "hex", "dec" and "bin".  Passing NULL defaults to
 * hexadecimal output.
 *
 * \param state   CPU state containing the register file.
 * \param gpr_idx Register index to print.
 * \param radix   Optional radix string.
 */
static inline void print_val_gpr(const a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx,
              const char *radix)
{
    uint64_t val = read_val_gpr(state, gpr_idx);

    /* default to hexadecimal if radix is NULL */
    if (radix == NULL || strcmp(radix, "hex") == 0 || strcmp(radix, "hexadecimal") == 0) {
        printf("X%d = 0x%016" PRIx64 "\n", (int)gpr_idx, val);
    } else if (strcmp(radix, "dec") == 0 || strcmp(radix, "decimal") == 0) {
        printf("X%d = %" PRIu64 "\n", (int)gpr_idx, val);
    } else if (strcmp(radix, "bin") == 0 || strcmp(radix, "binary") == 0) {
        /* print 64‑bit binary with 0b prefix */
        printf("X%d = 0b", (int)gpr_idx);
        for (int i = 63; i >= 0; --i) {
            putchar((val >> i) & 1 ? '1' : '0');
        }
        putchar('\n');
    } else {
        fprintf(stderr,
                "print_val_gpr: unknown radix \"%s\" (use \"hex\", \"dec\", or \"bin\")\n",
                radix);
    }
}

/*
 * Convenience wrapper to print a register value in hexadecimal.
 */
static inline void print_val_gpr_to_hex(const a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx) {
    print_val_gpr(state, gpr_idx, "hex");
}


/*
 * Convenience wrapper to print a register value in decimal.
 */
static inline void print_val_gpr_to_dec(const a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx) {
    print_val_gpr(state, gpr_idx, "dec");
}

/*
 * Write a 64-bit value to a general purpose register.
 */
static inline void write_val_gpr(a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx, uint64_t val) {
    if (gpr_idx >= GPR_COUNT) {
        fprintf(stderr, "Invalid GPR index %d\n", (int)gpr_idx);
        return;
    }

    /* Ignore writes to XZR/WZR */
    if (gpr_idx != XZR)
        state->gpr[gpr_idx].val = val;
}
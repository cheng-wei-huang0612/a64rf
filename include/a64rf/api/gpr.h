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


typedef enum {
    RADIX_HEX = 0,
    RADIX_DEC,
    RADIX_BIN
} radix_t;

static inline void print_bin64(uint64_t v)
{
    for (int i = 63; i >= 0; --i)
        putchar((v >> i) & 1 ? '1' : '0');
}

void print_val_gpr(const a64rf_state_t *state,
                   a64rf_gpr_idx_t      gpr_idx,
                   radix_t              radix,
                   bool                 is_signed)
{
    uint64_t raw = read_val_gpr(state, gpr_idx);

    /* 預設：HEX + unsigned */
    if (radix > RADIX_BIN) radix = RADIX_HEX;

    switch (radix) {
    case RADIX_DEC:
        if (is_signed)
            printf("X%d = %" PRIi64 "\n", (int)gpr_idx, (int64_t)raw);
        else
            printf("X%d = %" PRIu64 "\n", (int)gpr_idx, raw);
        break;

    case RADIX_BIN:
        printf("X%d = 0b", (int)gpr_idx);
        print_bin64(raw);
        putchar('\n');
        break;

    case RADIX_HEX:
    default:
        if (is_signed)
            printf("X%d = 0x%016" PRIx64 "  /* %" PRIi64 " */\n",
                   (int)gpr_idx, raw, (int64_t)raw);
        else
            printf("X%d = 0x%016" PRIx64 "\n", (int)gpr_idx, raw);
        break;
    }
}

/*
 * Convenience wrapper to print a register value in hexadecimal.
 */
static inline void print_val_gpr_to_unsigned_hex(const a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx) {
    print_val_gpr(state, gpr_idx, RADIX_HEX, false);
}


/*
 * Convenience wrapper to print a register value in decimal.
 */
static inline void print_val_gpr_to_unsigned_dec(const a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx) {
    print_val_gpr(state, gpr_idx, RADIX_DEC, false);
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

static inline void write_zero_gpr(a64rf_state_t *state, a64rf_gpr_idx_t gpr_idx) {
    write_val_gpr(state, gpr_idx, (uint64_t)0);
}


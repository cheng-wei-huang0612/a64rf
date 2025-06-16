#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "a64rf_types.h"

/*---------------------------------------------------------------------------
 *  Simple helpers for interacting with the a64rf_state_t structure.  These
 *  routines hide the underlying layout of the register file and make common
 *  tasks slightly easier for examples and unit tests.  All functions are
 *  defined as static inline so including this header does not require
 *  additional linkage steps.
 *---------------------------------------------------------------------------*/

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
 * Read a 64-bit element from a vector register (d register view).
 *
 * \param state     State structure containing vector registers.
 * \param vreg_idx  Vector register index to access.
 * \param lane      Lane number within the d[] view (0-1).
 * \return          Value of the specified lane or 0 on error.
 */
static inline uint64_t read_d_vreg(const a64rf_state_t* state, a64rf_vreg_idx_t vreg_idx, size_t lane) {
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return 0;
    }
    if (lane >= VREG_D_LANE_COUNT) {
        // Handle error: invalid lane index
        fprintf(stderr, "Invalid lane index %zu for vreg d[]\n", lane);
        return 0;
    }
    return state->vreg[vreg_idx].d[lane];
}

/* Read the low 64 bits of a vector register. */
static inline uint64_t read_d_vreg_lo(const a64rf_state_t* state, a64rf_vreg_idx_t vreg_idx) {
    return read_d_vreg(state, vreg_idx, 0);
}
/* Read the high 64 bits of a vector register. */
static inline uint64_t read_d_vreg_hi(const a64rf_state_t* state, a64rf_vreg_idx_t vreg_idx) {
    return read_d_vreg(state, vreg_idx, 1);
}


static inline void read_all_d_vreg(uint64_t dest[static VREG_D_LANE_COUNT],
                                   const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    memcpy(dest, state->vreg[vreg_idx].d, sizeof(state->vreg[vreg_idx].d));
}


/*
 * Read a 32-bit lane from the s[] view of a vector register.
 *
 * \param state     State structure containing vector registers.
 * \param vreg_idx  Vector register index.
 * \param lane      Lane number (0-3).
 */
static inline uint32_t read_s_vreg(const a64rf_state_t* state, a64rf_vreg_idx_t vreg_idx, size_t lane) {
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return 0;
    }
    if (lane >= VREG_S_LANE_COUNT) {
        // Handle error: invalid lane index
        fprintf(stderr, "Invalid lane index %zu for vreg s[]\n", lane);
        return 0;
    }
    return state->vreg[vreg_idx].s[lane];
}

static inline void read_all_s_vreg(uint32_t dest[static VREG_S_LANE_COUNT],
                                   const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    memcpy(dest, state->vreg[vreg_idx].s, sizeof(state->vreg[vreg_idx].s));
}




/*
 * Read a 16-bit lane from the h[] view of a vector register.
 *
 * \param state     Pointer to the state structure.
 * \param vreg_idx  Vector register index.
 * \param lane      Lane number (0-7).
 */
static inline uint16_t read_h_vreg(const a64rf_state_t* state, a64rf_vreg_idx_t vreg_idx, size_t lane) {
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return 0;
    }
    if (lane >= VREG_H_LANE_COUNT) {
        // Handle error: invalid lane index
        fprintf(stderr, "Invalid lane index %zu for vreg h[]\n", lane);
        return 0;
    }
    return state->vreg[vreg_idx].h[lane];
}
static inline void read_all_h_vreg(uint16_t dest[static VREG_H_LANE_COUNT],
                                   const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    memcpy(dest, state->vreg[vreg_idx].h, sizeof(state->vreg[vreg_idx].h));
}



/*
 * Read an 8-bit lane from the b[] view of a vector register.
 *
 * \param state     Pointer to the state structure.
 * \param vreg_idx  Vector register index.
 * \param lane      Lane number (0-15).
 */
static inline uint8_t read_b_vreg(const a64rf_state_t* state, const a64rf_vreg_idx_t vreg_idx, size_t lane) {
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return 0;
    }
    if (lane >= VREG_B_LANE_COUNT) {
        // Handle error: invalid lane index
        fprintf(stderr, "Invalid lane index %zu for vreg b[]\n", lane);
        return 0;
    }
    return state->vreg[vreg_idx].b[lane];
}

static inline void read_all_b_vreg(uint8_t dest[static VREG_B_LANE_COUNT],
                                   const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    memcpy(dest, state->vreg[vreg_idx].b, sizeof(state->vreg[vreg_idx].b));
}


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
/*
 * Write a 64-bit lane in the d[] view of a vector register.
 */
static inline void
write_d_vreg(a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx,
             size_t lane, uint64_t val)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    if (lane > 1) {
        fprintf(stderr, "Invalid lane index %zu for vreg d[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].d[lane] = val;

}

/* Helper to write the low 64 bits of a vector register. */
static inline void
write_d_vreg_lo(a64rf_state_t *s, a64rf_vreg_idx_t idx, uint64_t val)
{ write_d_vreg(s, idx, 0, val); }

/* Helper to write the high 64 bits of a vector register. */
static inline void
write_d_vreg_hi(a64rf_state_t *s, a64rf_vreg_idx_t idx, uint64_t val)
{ write_d_vreg(s, idx, 1, val); }

/* ───────────── V.s (4×32) ───────────── */
/* Write a 32-bit lane in the s[] view of a vector register. */
static inline void
write_s_vreg(a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx,
             size_t lane, uint32_t val)
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    if (lane > 3) {
        fprintf(stderr, "Invalid lane index %zu for vreg s[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].s[lane] = val;
}

/* ───────────── V.h (8×16) ───────────── */
static inline void
write_h_vreg(a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx,
             size_t lane, uint16_t val)
{ /* Write a 16-bit lane in the h[] view. */
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    if (lane > 7) {
        fprintf(stderr, "Invalid lane index %zu for vreg h[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].h[lane] = val;
}

/* ───────────── V.b (16×8) ───────────── */
static inline void
write_b_vreg(a64rf_state_t *state, a64rf_vreg_idx_t vreg_idx,
             size_t lane, uint8_t val)
{ /* Write an 8-bit lane in the b[] view. */
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    if (lane > 15) {
        fprintf(stderr, "Invalid lane index %zu for vreg b[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].b[lane] = val;
}

/* ───────────── 寫整個 V 向量 (128-bit) ─────────────
 * 若常用整塊搬移，可加下列 API；用戶自行準備來源 struct 或陣列。        */
static inline void
write_vreg_all(a64rf_state_t *state, a64rf_vreg_idx_t idx, const vreg_t *src)
{ /* Copy an entire 128-bit vector register from the provided source. */
    if (idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)idx);
        return;
    }
    state->vreg[idx] = *src;           /* 結構複製 */
}




/*───────────────────── NZCV pretty-print (N Z C V) ───────────────────*/

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


#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "../../../types.h"



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
    if (lane >= VREG_D_LANE_COUNT) {
        fprintf(stderr, "Invalid lane index %zu for vreg d[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].d[lane] = val;

}


/*
 * Write the two 64-bit lanes (d-view) of a vector register in one shot.
 *
 * \param src       Pointer to an array holding exactly VREG_D_LANE_COUNT
 *                  64-bit values (low lane first, high lane second).
 * \param state     Pointer to the CPU state structure.
 * \param vreg_idx  Index of the destination vector register.
 *
 * On parameter error the routine prints a diagnostic to stderr and returns
 * without modifying any register state.
 */
static inline void
write_all_d_vreg(a64rf_state_t      *state,
                 a64rf_vreg_idx_t    vreg_idx,
                 const uint64_t src[static VREG_D_LANE_COUNT])
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }

    /* 128-bit copy: faster than two scalar stores, keeps code short. */
    memcpy(state->vreg[vreg_idx].d,
           src,
           sizeof(state->vreg[vreg_idx].d));      /* 2 × 64-bit = 16 bytes */
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
    if (lane >= VREG_S_LANE_COUNT) {
        fprintf(stderr, "Invalid lane index %zu for vreg s[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].s[lane] = val;
}


static inline void
write_all_s_vreg(a64rf_state_t      *state,
                 a64rf_vreg_idx_t    vreg_idx,
                 const uint32_t src[static VREG_S_LANE_COUNT])
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }

    /* 128-bit copy: faster than two scalar stores, keeps code short. */
    memcpy(state->vreg[vreg_idx].s,
           src,
           sizeof(state->vreg[vreg_idx].s));      /* 2 × 64-bit = 16 bytes */
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
    if (lane >= VREG_H_LANE_COUNT) {
        fprintf(stderr, "Invalid lane index %zu for vreg h[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].h[lane] = val;
}

static inline void
write_all_h_vreg(a64rf_state_t      *state,
                 a64rf_vreg_idx_t    vreg_idx,
                 const uint16_t src[static VREG_H_LANE_COUNT])
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }

    /* 128-bit copy: faster than two scalar stores, keeps code short. */
    memcpy(state->vreg[vreg_idx].h,
           src,
           sizeof(state->vreg[vreg_idx].h));      /* 2 × 64-bit = 16 bytes */
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
    if (lane >= VREG_B_LANE_COUNT) {
        fprintf(stderr, "Invalid lane index %zu for vreg b[]\n", lane);
        return;
    }
    state->vreg[vreg_idx].b[lane] = val;
}

static inline void
write_all_b_vreg(a64rf_state_t      *state,
                 a64rf_vreg_idx_t    vreg_idx,
                 const uint8_t src[static VREG_B_LANE_COUNT])
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }

    /* 128-bit copy: faster than two scalar stores, keeps code short. */
    memcpy(state->vreg[vreg_idx].b,
           src,
           sizeof(state->vreg[vreg_idx].b));      /* 2 × 64-bit = 16 bytes */
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
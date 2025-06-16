#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>

#include "../../../types.h"




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


static inline void read_all_d_vreg(const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx,
                                   uint64_t dest[static VREG_D_LANE_COUNT])
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

static inline void read_all_s_vreg(const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx,
                                   uint32_t dest[static VREG_S_LANE_COUNT])
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

static inline void read_all_h_vreg(const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx,
                                   uint16_t dest[static VREG_H_LANE_COUNT])
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

static inline void read_all_b_vreg(const a64rf_state_t *state,
                                   a64rf_vreg_idx_t vreg_idx,
                                   uint8_t dest[static VREG_B_LANE_COUNT])
{
    if (vreg_idx >= VREG_COUNT) {
        fprintf(stderr, "Invalid vreg index %d\n", (int)vreg_idx);
        return;
    }
    memcpy(dest, state->vreg[vreg_idx].b, sizeof(state->vreg[vreg_idx].b));
}
#pragma once
#include "a64rf_types.h"
#include <stddef.h>


static inline void add_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] + b[i]);
    }

    write_all_b_vreg(s, Vd, r);
}


static inline void add_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
    {
        r[i] = (uint16_t)(a[i] + b[i]);
    }

    write_all_h_vreg(s, Vd, r);
}



static inline void add_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] + b[i]);

    write_all_s_vreg(s, Vd, r);
}

static inline void add_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] + b[i]);

    write_all_d_vreg(s, Vd, r);
}

static inline void sub_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] - b[i]);
    }

    write_all_b_vreg(s, Vd, r);
}


static inline void sub_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
        r[i] = (uint16_t)(a[i] - b[i]);

    write_all_h_vreg(s, Vd, r);
}


static inline void sub_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] - b[i]);

    write_all_s_vreg(s, Vd, r);
}


static inline void sub_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] - b[i]);

    write_all_d_vreg(s, Vd, r);
}


static inline void mul_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] * b[i]);
    }

    write_all_b_vreg(s, Vd, r);
}


static inline void mul_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
        r[i] = (uint16_t)(a[i] * b[i]);

    write_all_h_vreg(s, Vd, r);
}


static inline void mul_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] * b[i]);

    write_all_s_vreg(s, Vd, r);
}


static inline void mul_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] * b[i]);

    write_all_d_vreg(s, Vd, r);
}

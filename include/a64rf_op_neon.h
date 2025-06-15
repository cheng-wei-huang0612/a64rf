#pragma once
#include "a64rf_types.h"
#include <stddef.h>


static inline void add_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t       *dst = s->vreg[Vd].b;
    const uint8_t *a   = s->vreg[Vn].b;
    const uint8_t *b   = s->vreg[Vm].b;
    for (size_t i = 0; i < 16; ++i)
        dst[i] = (uint8_t)(a[i] + b[i]);
}


static inline void add_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t       *dst = s->vreg[Vd].h;
    const uint16_t *a   = s->vreg[Vn].h;
    const uint16_t *b   = s->vreg[Vm].h;
    for (size_t i = 0; i < 8; ++i)
        dst[i] = (uint16_t)(a[i] + b[i]);
}


static inline void add_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t       *dst = s->vreg[Vd].s;
    const uint32_t *a   = s->vreg[Vn].s;
    const uint32_t *b   = s->vreg[Vm].s;
    for (size_t i = 0; i < 4; ++i)
        dst[i] = a[i] + b[i];
}

static inline void add_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t       *dst = s->vreg[Vd].d;
    const uint64_t *a   = s->vreg[Vn].d;
    const uint64_t *b   = s->vreg[Vm].d;
    dst[0] = a[0] + b[0];
    dst[1] = a[1] + b[1];
}

static inline void sub_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t       *dst = s->vreg[Vd].b;
    const uint8_t *a   = s->vreg[Vn].b;
    const uint8_t *b   = s->vreg[Vm].b;
    for (size_t i = 0; i < 16; ++i)
        dst[i] = (uint8_t)(a[i] - b[i]);
}


static inline void sub_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t       *dst = s->vreg[Vd].h;
    const uint16_t *a   = s->vreg[Vn].h;
    const uint16_t *b   = s->vreg[Vm].h;
    for (size_t i = 0; i < 8; ++i)
        dst[i] = (uint16_t)(a[i] - b[i]);
}


static inline void sub_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t       *dst = s->vreg[Vd].s;
    const uint32_t *a   = s->vreg[Vn].s;
    const uint32_t *b   = s->vreg[Vm].s;
    for (size_t i = 0; i < 4; ++i)
        dst[i] = a[i] - b[i];
}


static inline void sub_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t       *dst = s->vreg[Vd].d;
    const uint64_t *a   = s->vreg[Vn].d;
    const uint64_t *b   = s->vreg[Vm].d;
    dst[0] = a[0] - b[0];
    dst[1] = a[1] - b[1];
}


static inline void mul_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t       *dst = s->vreg[Vd].b;
    const uint8_t *a   = s->vreg[Vn].b;
    const uint8_t *b   = s->vreg[Vm].b;
    for (size_t i = 0; i < 16; ++i)
        dst[i] = (uint8_t)(a[i] * b[i]);
}


static inline void mul_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t       *dst = s->vreg[Vd].h;
    const uint16_t *a   = s->vreg[Vn].h;
    const uint16_t *b   = s->vreg[Vm].h;
    for (size_t i = 0; i < 8; ++i)
        dst[i] = (uint16_t)(a[i] * b[i]);
}


static inline void mul_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t       *dst = s->vreg[Vd].s;
    const uint32_t *a   = s->vreg[Vn].s;
    const uint32_t *b   = s->vreg[Vm].s;
    for (size_t i = 0; i < 4; ++i)
        dst[i] = a[i] * b[i];
}


static inline void mul_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t       *dst = s->vreg[Vd].d;
    const uint64_t *a   = s->vreg[Vn].d;
    const uint64_t *b   = s->vreg[Vm].d;
    dst[0] = a[0] * b[0];
    dst[1] = a[1] * b[1];
}

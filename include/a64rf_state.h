#pragma once
#include <stdint.h>




/* single 64‑bit general-purpose register */
typedef struct {
    uint64_t val;
} gpr_t;


typedef struct {
    gpr_t     gpr[31];   /* X0–X30 */
    uint64_t  nzcv;
} a64rf_state_t;
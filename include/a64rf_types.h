#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

typedef enum a64rf_gpr_idx {
    X0  = 0,  X1,  X2,  X3,
    X4,       X5,  X6,  X7,
    X8,       X9,  X10, X11,
    X12,      X13, X14, X15,
    X16,      X17, X18, X19,
    X20,      X21, X22, X23,
    X24,      X25, X26, X27,
    X28,      X29, X30,

    GPR_IDX_MAX
} a64rf_gpr_idx_t;


#define GPR_COUNT   ((size_t)GPR_IDX_MAX)

typedef union { struct { unsigned V:1,C:1,Z:1,N:1; }; uint32_t word; } nzcv_t;

typedef struct {
    uint64_t val;
    uint32_t last_writer_pc;
    uint32_t access_cnt;
} gpr_t;

typedef enum a64rf_vreg_idx {
    V0  = 0,  V1,  V2,  V3,
    V4,       V5,  V6,  V7,
    V8,       V9,  V10, V11,
    V12,      V13, V14, V15,
    V16,      V17, V18, V19,
    V20,      V21, V22, V23,
    V24,      V25, V26, V27,
    V28,      V29, V30, V31,

    VREG_IDX_MAX
} a64rf_vreg_idx_t;


typedef struct {
    union { uint8_t b[16]; uint16_t h[8]; uint32_t s[4]; uint64_t d[2];};
    uint32_t last_writer_pc;
    uint32_t access_cnt;
} vreg_t;

#define VREG_COUNT   ((size_t)VREG_IDX_MAX)


typedef struct {
    gpr_t gpr[GPR_COUNT];
    vreg_t vreg[VREG_COUNT];
    uint64_t sp;
    nzcv_t   nzcv;
} a64rf_state_t;




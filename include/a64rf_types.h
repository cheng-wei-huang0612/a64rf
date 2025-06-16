#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

/*---------------------------------------------------------------------------
 *  Basic type definitions for the ARM64 register framework.
 *
 *  Each structure mirrors part of the CPU state so that C helpers and
 *  assembly snippets can easily exchange register snapshots.  The fields
 *  include a few book-keeping values (such as the last writer's program
 *  counter) that simplify debugging when running the unit tests.
 *---------------------------------------------------------------------------*/

/*
 * Enumeration of the 31 general purpose registers.  The values map directly
 * to the architectural X0–X30 register numbers used by AArch64 code.
 */
typedef enum a64rf_gpr_idx {
    X0  = 0,  X1,  X2,  X3,
    X4,       X5,  X6,  X7,
    X8,       X9,  X10, X11,
    X12,      X13, X14, X15,
    X16,      X17, X18, X19,
    X20,      X21, X22, X23,
    X24,      X25, X26, X27,
    X28,      X29, X30,

    XZR, SP,

    GPR_IDX_MAX               /* Marks the end of the enum and is not a reg */
} a64rf_gpr_idx_t;


/* Number of entries in the general purpose register array. */
#define GPR_COUNT   ((size_t)GPR_IDX_MAX)

/* Representation of the NZCV condition flags used by the AArch64 ISA.  The
 * structure view allows bitfield access while 'word' exposes the raw value. */
typedef union {
    struct { unsigned V:1, C:1, Z:1, N:1; };
    uint32_t word;
} nzcv_t;

/*
 * Metadata for a single general purpose register.  'val' holds the current
 * 64-bit contents while 'last_writer_pc' and 'access_cnt' provide light-weight
 * instrumentation for debugging register usage in the sample programs.
 */
typedef struct {
    uint64_t val;
    uint32_t last_writer_pc;
    uint32_t access_cnt;
} gpr_t;

/*
 * Enumeration of the thirty-two 128-bit vector registers.  The indices match
 * the architectural V0–V31 naming used in A64 assembly.
 */
typedef enum a64rf_vreg_idx {
    V0  = 0,  V1,  V2,  V3,
    V4,       V5,  V6,  V7,
    V8,       V9,  V10, V11,
    V12,      V13, V14, V15,
    V16,      V17, V18, V19,
    V20,      V21, V22, V23,
    V24,      V25, V26, V27,
    V28,      V29, V30, V31,

    VREG_IDX_MAX              /* Number of vector registers */
} a64rf_vreg_idx_t;

#define VREG_B_LANE_COUNT 16
#define VREG_H_LANE_COUNT 8
#define VREG_S_LANE_COUNT 4
#define VREG_D_LANE_COUNT 2


/*
 * Representation of a 128-bit vector register.  The anonymous union exposes
 * several common views (byte/halfword/word/doubleword).  Similar to gpr_t the
 * extra fields are used to track which instruction last modified the register
 * and how often it has been accessed.
 */
typedef struct {
    union {
        uint8_t  b[16];  /* 16 × 8-bit elements  */
        uint16_t h[8];   /* 8  × 16-bit elements */
        uint32_t s[4];   /* 4  × 32-bit elements */
        uint64_t d[2];   /* 2  × 64-bit elements */
    };
    uint32_t last_writer_pc;
    uint32_t access_cnt;
} vreg_t;

/* Total number of vector registers. */
#define VREG_COUNT   ((size_t)VREG_IDX_MAX)




/*
 * Aggregate snapshot of the CPU state.  The structure contains arrays of all
 * general purpose and vector registers along with the stack pointer and the
 * NZCV flags.  It is the primary object passed to the helper functions in
 * this project.
 */

 /*----------------------------------------------------------
 *  FPSR (Floating-point Status Register) ─ 目前只建 QC。
 *  QC = bit 27 (Armv8-A A64 實體位置)。
 *---------------------------------------------------------*/
typedef union {
    struct { unsigned _pad_0_26:27, QC:1, _pad_28_31:4; };
    uint32_t word;
} fpsr_t;



#define MEMORY_SIZE 256



typedef struct {
    gpr_t    gpr[GPR_COUNT];
    vreg_t   vreg[VREG_COUNT];
    uint64_t stack[MEMORY_SIZE];

    nzcv_t   nzcv;   /* PSTATE.NZCV               */
    fpsr_t   fpsr;   /* FPSR.QC (飽和累積旗標)     */
} a64rf_state_t;
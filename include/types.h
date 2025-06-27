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

    XZR, 

    GPR_IDX_MAX               /* Marks the end of the enum and is not a reg */
} a64rf_gpr_idx_t;


/* Number of entries in the general purpose register array. */
#define GPR_COUNT   ((size_t)GPR_IDX_MAX)



/* Representation of the NZCV condition flags used by the AArch64 ISA.  The
 * structure view allows bitfield access while 'word' exposes the raw value. */
typedef union {
    struct {
        /* 先吃掉低 28 bits，讓接下來四個旗標剛好落在 31‥28 */
        uint32_t _pad : 28;

        /* 依 ARMv8-A PSTATE bit 位置排列，最高位在最前 */
        uint32_t V    : 1;   // bit 28
        uint32_t C    : 1;   // bit 29
        uint32_t Z    : 1;   // bit 30
        uint32_t N    : 1;   // bit 31
    };
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


// typedef struct {
//     uintptr_t val;
//     uint32_t last_writer_pc;
//     uint32_t access_cnt;
// } sp_t;

typedef struct {
    void * val;
    uint32_t last_writer_pc;
    uint32_t access_cnt;
} sp_t;






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

typedef struct
{
    uint16_t val;
} pc_t;


typedef uint64_t a64rf_addr_t;




#define DEFAULT_STACK_SZ (1 * 1024)
#define DEFAULT_MEM_SZ (1 * 1024)



typedef struct {
    gpr_t    gpr[GPR_COUNT];
    vreg_t   vreg[VREG_COUNT];
    
    sp_t     sp;

    uint8_t *stack;
    size_t   stack_size;

    uint8_t *memory;
    size_t   mem_size;
    size_t   mem_cnt;

    pc_t     pc;

    nzcv_t   nzcv;
    fpsr_t   fpsr;
    uint64_t magic;
} a64rf_state_t;

/* 已有 enum，若想去掉前綴也可改成 SHIFT_LSL… */
typedef enum {
    A64_SHIFT_LSL = 0,
    A64_SHIFT_LSR = 1,
    A64_SHIFT_ASR = 2,
    A64_SHIFT_ROR = 3
} a64_shift_type_t;

typedef enum {
    EQ = 0,   // Equal
    NE,       // Not equal
    CS,       // Carry set (HS)
    CC,       // Carry clear (LO)
    MI,       // Minus, negative
    PL,       // Plus, positive or zero
    VS,       // Overflow
    VC,       // No overflow
    HI,       // Unsigned higher
    LS,       // Unsigned lower or same
    GE,       // Signed greater than or equal
    LT,       // Signed less than
    GT,       // Signed greater than
    LE,       // Signed less than or equal
    AL,       // Always (unconditional)
    NV        
} a64rf_cond_t;



typedef enum {
    OP_NULL = 0,
    OP_NOP,
    OP_RET,
    OP_LABEL,
    OP_PRINT_GPR,
    OP_BRANCH,
    OP_ADD, OP_SUB, OP_MUL,
    OP_MOV, OP_CMP, OP_CCMP,
    OP_COUNT
} a64rf_op_enum_t;

typedef enum {
    SHIFT_NONE = 0,
    SHIFT_LSL, SHIFT_LSR, SHIFT_ASR, SHIFT_ROR
} a64rf_shift_t;

typedef struct
{
    char name_of_label[32];
} a64rf_label_t;



typedef struct {
    a64rf_op_enum_t op;             // 指令種類
    a64rf_gpr_idx_t  dst;            // 目的暫存器編號
    a64rf_gpr_idx_t  src0;           // 第一來源暫存器
    a64rf_gpr_idx_t  src1;           // 第二來源暫存器（有些指令不用）
    a64rf_gpr_idx_t  src2;           // 第三來源暫存器（很少用，保留）
    uint64_t imm0;           // 立即數 0
    uint64_t imm1;           // 立即數 1
    uint64_t imm2;           // 立即數 2
    a64rf_shift_t  shift_type;     // LSL/LSR/ASR/ROR
    pc_t     target_pc;     // this is for branching insructions
    // uint8_t  nzcv_in_use;    // 1=此指令會讀 PSTATE.NZCV；0=不讀
    a64rf_label_t label;
} a64rf_instruction_t;

#define MAX_INSTRUCTION_LEN 256

typedef struct {
    a64rf_instruction_t insts[MAX_INSTRUCTION_LEN];
    pc_t    add_instruction_to_program; 
    // TODO: rename to `instruction_coordinate`

} a64rf_program_t;


static inline pc_t increment_pc(pc_t old_pc)
{
    pc_t new_pc;
    new_pc.val = (old_pc.val + 1);
    return new_pc;
}


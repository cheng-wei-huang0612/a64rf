/* a64rf_op.h */
#pragma once
#include "../../types.h"
#include "../api/mem.h"

#include <stdbool.h>
#include <string.h>

/*--------------------------------------------------------------------
 *  add_with_carry_u64()
 *  ─ 依 Arm A64《AddWithCarry》偽碼，計算 result 及 NZCV。
 *------------------------------------------------------------------*/
static inline uint64_t add_with_carry_u64(uint64_t a, uint64_t b,
                   unsigned carry_in, nzcv_t *f) {
    uint64_t res = a + b + (uint64_t)carry_in;

    /* Carry：無號加法進位 */
    f->C = carry_in ? (res <= a) : (res < a);

    /* Overflow：兩輸入同號且結果異號 */
    f->V = (~(a ^ b) & (a ^ res)) >> 63;

    /* Zero／Negative */
    f->Z = (res == 0);
    f->N = res >> 63;

    return res;
}

static inline void set_flags_logical(uint64_t res, nzcv_t *f)
{
    f->N = res >> 63;
    f->Z = (res == 0);
    f->C = 0;
    f->V = 0;         /* 依規格，ANDS/BICS/EORS 把 C/V 置 0 */
}





/* compile to: mul Xd, Xn, Xm */
static inline void mul_xform(a64rf_state_t *s,
                             const a64rf_gpr_idx_t Xd, 
                             const a64rf_gpr_idx_t Xn, 
                             const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n * src_m;

    write_val_gpr(s, Xd, result);
}


void mul_xd_xn_xm(a64rf_program_t *program, a64rf_gpr_idx_t dst, a64rf_gpr_idx_t src0, a64rf_gpr_idx_t src1) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_MUL;
    instruction.dst = dst;
    instruction.src0 = src0;
    instruction.src1 = src1;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc = increment_pc(program->add_instruction_to_program);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}


static inline bool validate_add_imm_shift(uint32_t imm, unsigned shift,
                       const char *func_name)
{
    if (imm > 0xFFFu) {
        fprintf(stderr, "%s: imm 0x%X 超出 12-bit 範圍\n",
                func_name, imm);
        return false;
    }
    if (shift != 0 && shift != 12) {
        fprintf(stderr, "%s: shift 必須是 0 或 12，收到 %u\n",
                func_name, shift);
        return false;
    }
    return true;
}

/*--------------------------------------------------------------------
 *  validate_sp_alignment()
 *  ─ 回傳 true  ⇢  SP 已 16-byte 對齊
 *    回傳 false ⇢  SP 未對齊，並印出警告
 *------------------------------------------------------------------*/
// static inline bool
// validate_sp_alignment(const a64rf_state_t *s, const char *func_name)
// {
//     // TODO: API for sp
//     uint64_t sp_val = s->sp.val;
//     if (sp_val & 0xF) {
//         fprintf(stderr,
//                 "%s: SP (0x%016" PRIx64 ") not 16-byte aligned\n",
//                 func_name, sp_val);
//         return false;
//     }
//     return true;
// }


// static inlien bool validate_sp_align(SP);


static inline void add_xform_imm_shift(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 const uint32_t imm,
                                 const uint32_t shift)
{
    if (!validate_add_imm_shift(imm, shift, __func__))
        return;

    uint64_t operand1 = read_val_gpr(s, Xn);
    uint64_t operand2 = ((uint64_t)imm << shift);

    nzcv_t dummy_flag;
    uint64_t result = add_with_carry_u64(operand1, operand2, 0, &dummy_flag);

    write_val_gpr(s, Xd, result);
}

static inline void add_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 const uint32_t imm)
{
    add_xform_imm_shift(s, Xd, Xn, imm, 0u);
}




// static inline void add_sp_imm_shift(a64rf_state_t *s,
//                                  const uint32_t imm,
//                                  const uint32_t shift)
// {
//     if (!validate_add_imm_shift(imm, shift, __func__))
//         return;
//     uint64_t operand1 = s->sp.val;
//     uint64_t operand2 = ((uint64_t)imm << shift);

//     nzcv_t dummy_flag;
//     uint64_t result = add_with_carry_u64(operand1, operand2, 0, &dummy_flag);



//     validate_sp_alignment(s, __func__);
// }

// static inline void add_sp_imm(a64rf_state_t *s,
//                                  const uint32_t imm)
// {
//     add_xform_imm_shift(s, SP, SP, imm, 0u);
//     validate_sp_alignment(s, __func__);

// }

// static inline void add_reg_from_sp_imm_shift(a64rf_state_t *s,
//                                              a64rf_gpr_idx_t Xd,
//                                              uint32_t imm,
//                                              uint32_t shift)
// {
//     add_xform_imm_shift(s, Xd, SP, imm, shift);
// }

// static inline void add_reg_from_sp_imm(a64rf_state_t *s,
//                                              a64rf_gpr_idx_t Xd,
//                                              uint32_t imm)
// {
//     add_xform_imm_shift(s, Xd, SP, imm, 0u);
// }

// static inline void add_sp_from_reg_imm_shift(a64rf_state_t *s,
//                                              a64rf_gpr_idx_t Xn,
//                                              uint32_t imm,
//                                              uint32_t shift)
// {
//     add_xform_imm_shift(s, SP, Xn, imm, shift);
//     validate_sp_alignment(s, __func__);

// }


// static inline void add_sp_from_reg_imm(a64rf_state_t *s,
//                                              a64rf_gpr_idx_t Xn,
//                                              uint32_t imm)
// {
//     add_xform_imm_shift(s, SP, Xn, imm, 0u);
//     validate_sp_alignment(s, __func__);

// }








/* 
compile to: add Xd, Xn, Xm 
ref: arm profile-a TODO
*/
static inline void add_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n + src_m;

    write_val_gpr(s, Xd, result);
}


void add_xd_xn_xm(a64rf_program_t *program, a64rf_gpr_idx_t dst, a64rf_gpr_idx_t src0, a64rf_gpr_idx_t src1) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_ADD;
    instruction.dst = dst;
    instruction.src0 = src0;
    instruction.src1 = src1;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc = increment_pc(program->add_instruction_to_program);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}


static inline bool validate_shift_reg(unsigned amount,
                                      a64_shift_type_t type,
                                      const char *fn)
{
    if (amount > 63) {
        fprintf(stderr, "%s: shift amount %u out of range (0-63)\n", fn, amount);
        return false;
    }
    if (type > A64_SHIFT_ROR) {
        fprintf(stderr, "%s: illegal shift type %u\n", fn, type);
        return false;
    }
    return true;
}


// static inline void add_xform_shift_reg(a64rf_state_t *s,
//                                        a64rf_gpr_idx_t Xd,
//                                        a64rf_gpr_idx_t Xn,
//                                        a64rf_gpr_idx_t Xm,
//                                        a64_shift_type_t shift_type,
//                                        unsigned amount)
// {
//     if (!validate_shift_reg(amount, shift_type, __func__))
//         return;

//     if (Xn == SP || Xn == SP || Xm == SP) {
//         fprintf(stderr, "%s: SP cannot be used as Rn/Rm here\n", __func__);
//         return;
//     }

//     uint64_t op1 = read_val_gpr(s, Xn);
//     uint64_t op2 = read_val_gpr(s, Xm);

//     switch (shift_type) {
//         case A64_SHIFT_LSL: op2 <<= amount; break;
//         case A64_SHIFT_LSR: op2 >>= amount; break;
//         case A64_SHIFT_ASR: op2 = (uint64_t)((int64_t)op2 >> amount); break;
//         case A64_SHIFT_ROR:
//             op2 = (op2 >> amount) | (op2 << ((64 - amount) & 63));
//             break;
//     }

//     uint64_t result = op1 + op2;
//     write_val_gpr(s, Xd, result);

//     /* 若 Rd==SP，檢 16-byte alignment */
//     if (Xd == SP) validate_sp_alignment(s, __func__);
// }





/*
compile to: adds Xd, Xn, Xm 
ref: arm profile-a C6-1608
*/
static inline void adds_xd_xn_xm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    nzcv_t   flags = {0};
    uint64_t result = add_with_carry_u64(src_n, src_m, /*carry_in=*/0, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

// legacy name
#define adds_xform adds_xd_xn_xm


/*
compile to: adds Xd, Xn, #imm, #shift
ref: arm profile-a C6-1606
*/
static inline void adds_xd_xn_imm_shift(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const uint32_t imm12,
                              const uint32_t shift)
{
    if (imm12 > 0xFFFu) {
        fprintf(stderr, "adds_xd_xn_xm: imm12 0x%X out of 12-bit range\n", imm12);
        return;
    }
    if (shift != 0 && shift != 12) {
        fprintf(stderr, "adds_xd_xn_xm: shift must be either 0 or 12, got %u\n", shift);
        return;
    }

    uint64_t imm = imm12 << shift;

    uint64_t operand1 = read_val_gpr(s, Xn);
    uint64_t operand2 = imm;

    nzcv_t   flags = {0};
    uint64_t result = add_with_carry_u64(operand1, operand2, /*carry_in=*/0, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

/*
compile to: adds Xd, Xn, #imm
ref: arm profile-a C6-1606
*/
static inline void adds_xd_xn_imm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const uint32_t imm12)
{
    adds_xd_xn_imm_shift(s, Xd, Xn, imm12, 0);
}



/*
compile to: adcs Xd, Xn, Xm 
ref: arm profile-a C6-1593
*/
static inline void adcs_xd_xn_xm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    nzcv_t   flags = {0};
    
    uint64_t result = add_with_carry_u64(src_n, src_m, s->nzcv.C, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

/*
compile to: adc Xd, Xn, Xm 
ref: arm profile-a C6-1592
*/
static inline void adc_xd_xn_xm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    nzcv_t   dummy_flags = {0};
    
    uint64_t result = add_with_carry_u64(src_n, src_m, s->nzcv.C, &dummy_flags);

    write_val_gpr(s, Xd, result);
}




static inline void sub_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = ~read_val_gpr(s, Xm);

    nzcv_t   dummy_flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, 1, &dummy_flags);


    write_val_gpr(s, Xd, result);
}


void sub_xd_xn_xm(a64rf_program_t *program, a64rf_gpr_idx_t dst, a64rf_gpr_idx_t src0, a64rf_gpr_idx_t src1) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_SUB;
    instruction.dst = dst;
    instruction.src0 = src0;
    instruction.src1 = src1;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc = increment_pc(program->add_instruction_to_program);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}



static inline void subs_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = ~read_val_gpr(s, Xm);

    nzcv_t   flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, 1, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

static inline void cmp_xform(a64rf_state_t *s,
                             const a64rf_gpr_idx_t Xn,
                             const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = ~read_val_gpr(s, Xm);

    nzcv_t flags;
    (void)add_with_carry_u64(src_n, src_m, 1, &flags);

    s->nzcv = flags;
}

static inline void cmn_xform(a64rf_state_t *s,
                             const a64rf_gpr_idx_t Xn,
                             const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    nzcv_t flags;
    (void)add_with_carry_u64(src_n, src_m, 0, &flags);

    s->nzcv = flags;
}


static inline void adcs_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n   = read_val_gpr(s, Xn);
    uint64_t src_m   = read_val_gpr(s, Xm);
    unsigned carry_in = s->nzcv.C;

    nzcv_t   flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, carry_in, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

static inline void sbcs_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n   = read_val_gpr(s, Xn);
    uint64_t src_m   = ~read_val_gpr(s, Xm);
    unsigned carry_in = s->nzcv.C;

    nzcv_t   flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, carry_in, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}

static inline void negs_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = 0;
    uint64_t src_m = ~read_val_gpr(s, Xm);

    nzcv_t   flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, 1, &flags);

    s->nzcv = flags;
    write_val_gpr(s, Xd, result);
}


static inline void ands_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n & src_m;

    set_flags_logical(result, &s->nzcv);
    write_val_gpr(s, Xd, result);
}


/*--------------------------------------------------------------------
 *  Logical/Arithmetic shifts and Rotate Right by register (64‑bit)
 *------------------------------------------------------------------*/
static inline void lsl_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t amount = read_val_gpr(s, Xm) & 63;   /* use low‑order 6 bits */

    uint64_t result = src_n << amount;

    write_val_gpr(s, Xd, result);
}

static inline void lsl_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 unsigned imm6)
{
    if (imm6 > 63) {
        fprintf(stderr, "lsl_xform_imm: shift amount %u out of range\n", imm6);
        return;
    }

    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t result = src_n << imm6;

    write_val_gpr(s, Xd, result);
}

static inline void lsr_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t amount = read_val_gpr(s, Xm) & 63;

    uint64_t result = src_n >> amount;

    write_val_gpr(s, Xd, result);
}

static inline void lsr_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 unsigned imm6)
{
    if (imm6 > 63) {
        fprintf(stderr, "lsr_xform_imm: shift amount %u out of range\n", imm6);
        return;
    }

    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t result = src_n >> imm6;

    write_val_gpr(s, Xd, result);
}

static inline void asr_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    int64_t  src_n  = (int64_t)read_val_gpr(s, Xn);
    uint64_t amount = read_val_gpr(s, Xm) & 63;

    uint64_t result = (uint64_t)(src_n >> amount);

    write_val_gpr(s, Xd, result);
}

static inline void asr_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 unsigned imm6)
{
    if (imm6 > 63) {
        fprintf(stderr, "asr_xform_imm: shift amount %u out of range\n", imm6);
        return;
    }

    int64_t  src_n  = (int64_t)read_val_gpr(s, Xn);
    uint64_t result = (uint64_t)(src_n >> imm6);

    write_val_gpr(s, Xd, result);
}

static inline void ror_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t amount = read_val_gpr(s, Xm) & 63;

    uint64_t result = (src_n >> amount) | (src_n << ((64 - amount) & 63));

    write_val_gpr(s, Xd, result);
}

static inline void ror_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 unsigned imm6)
{
    if (imm6 > 63) {
        fprintf(stderr, "ror_xform_imm: rotate amount %u out of range\n", imm6);
        return;
    }

    uint64_t src_n  = read_val_gpr(s, Xn);
    uint64_t amount    = imm6 & 63;
    uint64_t result = (src_n >> amount) | (src_n << ((64 - amount) & 63));

    write_val_gpr(s, Xd, result);
}



static inline void bic_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n & ~src_m;

    write_val_gpr(s, Xd, result);
}

static inline void bics_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n & ~src_m;

    set_flags_logical(result, &s->nzcv);
    write_val_gpr(s, Xd, result);
}

/* 
compile to: orr xd, xn, xm 
ref: a-profile: C6-2141
*/
static inline void orr_xd_xn_xm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n | src_m;

    write_val_gpr(s, Xd, result);
}

// legacy
#define orr_xform orr_xd_xn_xm


/* 
compile to: orr xd, xn, #imm
ref: a-profile: C6-2139
*/
static inline void orr_xd_xn_imm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const uint64_t imm)
{
    uint64_t operand1 = read_val_gpr(s, Xn);
    uint64_t operand2 = imm;

    uint64_t result = operand1 | operand2;

    write_val_gpr(s, Xd, result);
}

/* 
compile to: mov xd, #imm
ref: a-profile: C6-2105
TODO: review this
*/
static inline void mov_xd_imm(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const uint32_t imm)
{
    orr_xd_xn_imm(s, Xd, XZR, imm);
}


/* 
compile to: movz xd, #imm
ref: a-profile: C6-2113
*/
static inline void movz_xd_imm_lsl_shift(a64rf_state_t *s,
                                         const a64rf_gpr_idx_t Xd,
                                         const uint32_t imm16,
                                         const uint32_t shift)
{
    if (imm16 > 0xFFFFu) {
        fprintf(stderr, "movz_xd_imm_lsl_shift: imm16 0x%X out of 16-bit range\n", imm16);
        return;
    }
    if (shift % 16 != 0) {
        fprintf(stderr, "movz_xd_imm_lsl_shift: shift %u is not a multiple of 16\n", shift);
        return;
    }
    uint64_t value = ((uint64_t)imm16) << shift;
    write_val_gpr(s, Xd, value);
}


static inline bool condition_holds(const a64rf_state_t *s, const a64rf_cond_t cond)
{

    bool result = false;
    switch ((cond >> 1) & 0x7) {
        case 0: // '000' EQ/NE
            result = (s->nzcv.Z == 1);
            break;
        case 1: // '001' CS/CC
            result = (s->nzcv.C == 1);
            break;
        case 2: // '010' MI/PL
            result = (s->nzcv.N == 1);
            break;
        case 3: // '011' VS/VC
            result = (s->nzcv.V == 1);
            break;
        case 4: // '100' HI/LS
            result = (s->nzcv.C == 1 && s->nzcv.Z == 0);
            break;
        case 5: // '101' GE/LT
            result = (s->nzcv.N == s->nzcv.V);
            break;
        case 6: // '110' GT/LE
            result = (s->nzcv.N == s->nzcv.V && s->nzcv.Z == 0);
            break;
        case 7: // '111' AL
            result = true;
            break;
    }
    if (cond & 1 && cond != 15)
        result = !result;
    return result;
}

/* 
compile to: csel xd, xn, xm, cond
ref: a-profile: C6-1888
*/
static inline void csel_xd_xn_xm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 const a64rf_gpr_idx_t Xm,
                                 const a64rf_cond_t cond)
{
    uint64_t result = {0};
    if (condition_holds(s, cond)) {
        result = read_val_gpr(s, Xn);
    } else {
        result = read_val_gpr(s, Xm);
    }

    write_val_gpr(s, Xd, result);
}





/* 
compile to: ldr xt, [xn] 
ref: a-profile: C6-2006
*/
static inline void ldr_xt_xn(a64rf_state_t *s,
                             a64rf_gpr_idx_t Xd,
                             a64rf_gpr_idx_t Xn)
{

    uint64_t base   = read_val_gpr(s, Xn);

    uint64_t gaddr  = base;
    uint64_t data   = 0;
    if (base & 7) {
        fprintf(stderr, "unaligned LDR @ 0x%llx\n", (unsigned long long)base);
        abort();
    }
    if (read_mem_64(s, gaddr, &data) != 0) {     /* Data Abort */
        fprintf(stderr, "LDR abort @ 0x%llx\n", (unsigned long long)gaddr);
        abort();
    }
    write_val_gpr(s, Xd, data);
}

// legacy name
#define ldr_xform ldr_xt_xn

/*---------------------------------------------------------------
 *  compile to:     ldp Xt1, Xt2, [Xn]
 *  ref:  Arm ARM A-profile (C6-1999), “LDP (Load Pair, 64-bit)”
 *----------------------------------------------------------------
 *  - Xt1, Xt2  ←  [Xn]        // little-endian: Xt1 ← [base],
 *                              //                Xt2 ← [base+8]
 *----------------------------------------------------------------*/
static inline void
ldp_xt1_xt2_xn(a64rf_state_t        *s,
               const a64rf_gpr_idx_t       Xt1,
               const a64rf_gpr_idx_t       Xt2,
               const a64rf_gpr_idx_t       Xn)
{
    /*------------------------------------------------------------*
     *  1. 取出 base address                                       *
     *------------------------------------------------------------*/
    uint64_t base = read_val_gpr(s, Xn);

    /*------------------------------------------------------------*
     *  2. Alignment check (8-byte)                               *
     *     – Arm 容許非對齊存取，但許多系統對 LDP 要求 8-byte 對齊 *
     *------------------------------------------------------------*/
    if (base & 7) {
        fprintf(stderr,
                "unaligned LDP @ 0x%llx\n",
                (unsigned long long)base);
        abort();
    }

    /*------------------------------------------------------------*
     *  3. 讀取 2×64-bit                                           *
     *------------------------------------------------------------*/
    uint64_t lo = 0, hi = 0;
    if (read_mem_64(s, base,      &lo) != 0 ||   /* data abort? */
        read_mem_64(s, base + 8,  &hi) != 0) {
        fprintf(stderr,
                "LDP abort @ 0x%llx\n",
                (unsigned long long)base);
        abort();
    }

    /*------------------------------------------------------------*
     *  4. 寫回目標暫存器                                          *
     *------------------------------------------------------------*/
    write_val_gpr(s, Xt1, lo);
    write_val_gpr(s, Xt2, hi);
}


/*---------------------------------------------------------------
 *  compile to:     ldp Xt1, Xt2, [Xn, #imm]
 *  ref:  Arm ARM A-profile (C6-2006), “LDP (Load Pair, 64-bit, offset)”
 *----------------------------------------------------------------
 *  - Xt1 ← [base + imm]          (little-endian: low address → Xt1)
 *  - Xt2 ← [base + imm + 8]
 *
 *  *imm 必須為 8 的倍數，範圍通常在 ±504 之內
 *----------------------------------------------------------------*/
static inline void
ldp_xt1_xt2_xn_imm(a64rf_state_t        *s,
                   a64rf_gpr_idx_t       Xt1,
                   a64rf_gpr_idx_t       Xt2,
                   a64rf_gpr_idx_t       Xn,
                   int32_t               imm)   /* byte offset */
{
    /*------------------------------------------------------------*
     *  1. 檢查立即值                                             *
     *------------------------------------------------------------*/
    if (imm & 7) {
        fprintf(stderr,
                "LDP imm (%d) not multiple of 8\n", imm);
        abort();
    }

    /*------------------------------------------------------------*
     *  2. 計算實際位址                                           *
     *------------------------------------------------------------*/
    uint64_t base = read_val_gpr(s, Xn);
    uint64_t addr = base + (int64_t)imm;   /* sign-extended add */

    /*------------------------------------------------------------*
     *  3. Alignment check (8-byte)                               *
     *------------------------------------------------------------*/
    if (addr & 7) {
        fprintf(stderr,
                "unaligned LDP @ 0x%llx\n",
                (unsigned long long)addr);
        abort();
    }

    /*------------------------------------------------------------*
     *  4. 讀取 2×64-bit                                          *
     *------------------------------------------------------------*/
    uint64_t lo = 0, hi = 0;
    if (read_mem_64(s, addr,       &lo) != 0 ||   /* Data abort? */
        read_mem_64(s, addr + 8,   &hi) != 0) {
        fprintf(stderr,
                "LDP abort @ 0x%llx\n",
                (unsigned long long)addr);
        abort();
    }

    /*------------------------------------------------------------*
     *  5. 寫回目的暫存器                                         *
     *------------------------------------------------------------*/
    write_val_gpr(s, Xt1, lo);
    write_val_gpr(s, Xt2, hi);
}




// TODO: change to str_xt_xn
static inline void str_xform(a64rf_state_t *s,
                             a64rf_gpr_idx_t Xd,   /* 要寫出的資料來源暫存器 */
                             a64rf_gpr_idx_t Xn)   /* 基底位址暫存器       */
{
    /* 如果你還沒全面鋪 CHECK_INIT，這裡先不加；要加也只需一行 */
    /* CHECK_INIT(s); */

    uint64_t base  = read_val_gpr(s, Xn);          /* 目標 guest address */
    uint64_t data  = read_val_gpr(s, Xd);          /* 欲寫入的 64-bit 數值 */

    /* 8-byte alignment 檢查（符合 A64 規格；要寬鬆可刪） */
    if (base & 7) {
        fprintf(stderr, "unaligned STR @ 0x%llx\n",
                (unsigned long long)base);
        abort();
    }

    /* 寫入；若超出 guest memory 範圍則視為 data abort */
    if (write_mem_64(s, base, data) != 0) {
        fprintf(stderr, "STR abort @ 0x%llx\n",
                (unsigned long long)base);
        abort();
    }
}

/*---------------------------------------------------------------
 *  compile to:     stp Xt1, Xt2, [Xn, #imm]
 *  ref:  Arm ARM A-profile (C6-2332), STP
 *----------------------------------------------------------------
 *  - [base + imm]     ← Xt1   (little-endian: low address ← Xt1)
 *  - [base + imm + 8] ← Xt2
 *
 *  *imm 必須為 8 的倍數，且範圍通常在 ±504 之內
 *----------------------------------------------------------------*/
static inline void
stp_xt1_xt2_xn_imm(a64rf_state_t        *s,
                   a64rf_gpr_idx_t       Xt1,
                   a64rf_gpr_idx_t       Xt2,
                   a64rf_gpr_idx_t       Xn,
                   int32_t               imm)   /* byte offset */
{
    /*------------------------------------------------------------*
     *  1. 立即值檢查                                             *
     *------------------------------------------------------------*/
    if (imm & 7) {
        fprintf(stderr,
                "STP imm (%d) not multiple of 8\n", imm);
        abort();
    }

    /*------------------------------------------------------------*
     *  2. 計算實際位址                                           *
     *------------------------------------------------------------*/
    uint64_t base = read_val_gpr(s, Xn);
    uint64_t addr = base + (int64_t)imm;   /* sign-extended add */

    /*------------------------------------------------------------*
     *  3. Alignment check (8-byte)                               *
     *------------------------------------------------------------*/
    if (addr & 7) {
        fprintf(stderr,
                "unaligned STP @ 0x%llx\n",
                (unsigned long long)addr);
        abort();
    }

    /*------------------------------------------------------------*
     *  4. 取得待寫入資料                                         *
     *------------------------------------------------------------*/
    uint64_t lo = read_val_gpr(s, Xt1);
    uint64_t hi = read_val_gpr(s, Xt2);

    /*------------------------------------------------------------*
     *  5. 寫入 2×64-bit                                          *
     *------------------------------------------------------------*/
    if (write_mem_64(s, addr,     lo) != 0 ||   /* Data abort? */
        write_mem_64(s, addr + 8, hi) != 0) {
        fprintf(stderr,
                "STP abort @ 0x%llx\n",
                (unsigned long long)addr);
        abort();
    }
}



void branch(a64rf_program_t *program, a64rf_label_t label)
{
    a64rf_instruction_t instruction;
    instruction.op = OP_BRANCH;
    instruction.dst = XZR;
    instruction.src0 = XZR;
    instruction.src1 = XZR;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    strcpy(instruction.label.name_of_label, label.name_of_label);

    instruction.target_pc.val = (uint16_t)(-1);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}

void ret(a64rf_program_t *program) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_RET;
    instruction.dst = XZR;
    instruction.src0 = XZR;
    instruction.src1 = XZR;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc.val = (uint16_t)(-1);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}




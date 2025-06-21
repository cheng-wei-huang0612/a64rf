/* a64rf_op.h */
#pragma once
#include "../../types.h"

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






static inline void adds_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    nzcv_t   flags;
    uint64_t result = add_with_carry_u64(src_n, src_m, /*carry_in=*/0, &flags);

    s->nzcv = flags;
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

static inline void orr_xform(a64rf_state_t *s,
                              const a64rf_gpr_idx_t Xd,
                              const a64rf_gpr_idx_t Xn,
                              const a64rf_gpr_idx_t Xm)
{
    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t src_m = read_val_gpr(s, Xm);

    uint64_t result = src_n | src_m;

    write_val_gpr(s, Xd, result);
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




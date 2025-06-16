/* a64rf_op.h */
#pragma once
#include "../../types.h"


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

/*--------------------------------------------------------------------
 *  add_xform_imm()
 *  ─ Xd = Xn + imm (imm is 12‑bit unsigned, no shift)
 *------------------------------------------------------------------*/
static inline void add_xform_imm(a64rf_state_t *s,
                                 const a64rf_gpr_idx_t Xd,
                                 const a64rf_gpr_idx_t Xn,
                                 uint32_t imm)
{
    /* A64 ADD (immediate) encodes a 12‑bit literal (0‑4095). */
    if (imm > 0xFFFu) {
        fprintf(stderr,
                "add_xform_imm: imm value 0x%X exceeds 12‑bit range (0‑0xFFF)\n",
                imm);
        return;
    }

    uint64_t src_n = read_val_gpr(s, Xn);
    uint64_t result = src_n + (uint64_t)imm;

    write_val_gpr(s, Xd, result);
}

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
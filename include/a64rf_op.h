/* a64rf_op.h */
#pragma once
#include "a64rf_state.h"
#include "a64rf_regs.h"

/* dst = a * b   (MUL 不影響 NZCV，但我們仍把 flags 帶進再帶出) */
static inline void mul_xform(a64rf_state_t *s,
                             a64rf_reg d, a64rf_reg a, a64rf_reg b)
{
    uint64_t lhs = s->gpr[a].val;
    uint64_t rhs = s->gpr[b].val;
    uint64_t in_flags  = s->nzcv;
    uint64_t out_flags;
    uint64_t res;

    __asm__ volatile (
        "msr nzcv, %[in_f]\n\t"          /* 把 struct 裡的旗標寫進系統暫存器 */
        "mul %[r], %[x], %[y]\n\t"       /* 執行乘法 (不改 NZCV) */
        "mrs %[out_f], nzcv"             /* 取回 (保留原值)           */
        : [r] "=&r"(res), [out_f] "=&r"(out_flags)
        : [x] "r"(lhs), [y] "r"(rhs), [in_f] "r"(in_flags)
        : "cc"                           /* 告訴編譯器此 asm 讀寫 flags */
    );

    s->gpr[d].val = res;
    s->nzcv       = out_flags;
}

/* dst = a + b   (使用 ADD 產生並更新 NZCV) */
static inline void add_xform(a64rf_state_t *s,
                             a64rf_reg d, a64rf_reg a, a64rf_reg b)
{
    uint64_t lhs = s->gpr[a].val;
    uint64_t rhs = s->gpr[b].val;
    uint64_t in_flags  = s->nzcv;
    uint64_t out_flags;
    uint64_t res;

    __asm__ volatile (
        "msr nzcv, %[in_f]\n\t"          /* 將原 flags 填入 */
        "add %[r], %[x], %[y]\n\t"
        "mrs  %[out_f], nzcv"            /* 讀出新的 NZCV */
        : [r] "=&r"(res), [out_f] "=&r"(out_flags)
        : [x] "r"(lhs), [y] "r"(rhs), [in_f] "r"(in_flags)
        : "cc"
    );

    s->gpr[d].val = res;
    s->nzcv       = out_flags;
}

static inline void adds_xform(a64rf_state_t *s,
                             a64rf_reg d, a64rf_reg a, a64rf_reg b)
{
    uint64_t lhs = s->gpr[a].val;
    uint64_t rhs = s->gpr[b].val;
    uint64_t in_flags  = s->nzcv;
    uint64_t out_flags;
    uint64_t res;

    __asm__ volatile (
        "msr nzcv, %[in_f]\n\t"          /* 將原 flags 填入 */
        "adds %[r], %[x], %[y]\n\t"
        "mrs  %[out_f], nzcv"            /* 讀出新的 NZCV */
        : [r] "=&r"(res), [out_f] "=&r"(out_flags)
        : [x] "r"(lhs), [y] "r"(rhs), [in_f] "r"(in_flags)
        : "cc"
    );

    s->gpr[d].val = res;
    s->nzcv       = out_flags;
}
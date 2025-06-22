#include "a64rf_size.h"
/*===================================================================
 *  (以下沿用上一版本的巨集，已抽出 SNAP_FRAME_BEGIN / END 等…)
 *===================================================================*/
#ifndef __SNAP_MACRO_SAFE_INC__
#define __SNAP_MACRO_SAFE_INC__

#ifdef A64RF_TRACE


/* ────────────────────────────────────────────────
 * 共用框架：prologue / epilogue
 * extra = 需向下分配的 spill bytes
 * ────────────────────────────────────────────────*/
        .macro  SNAP_FRAME_BEGIN extra:req
            stp     x29, x30, [sp, -16]!
            mov     x29, sp

            stp     x19, x20, [sp, -16]!

            mrs     x20, nzcv

            stp     x0, x1, [sp, #-32]!
            stp     x2, x3, [sp, #16]

            sub     sp, sp, \extra
            mov     x9, sp
        .endm

        .macro  SNAP_FRAME_END   extra:req
            add     sp, sp, \extra

            ldp     x2, x3, [sp, #16]
            ldp     x0, x1, [sp], #32

            ldp     x19, x20, [sp], 16
            ldp     x29, x30, [sp], 16
        .endm

/* ────────────────────────────────────────────────
 *  SNAP_GPRS  ─ 快照 X0–X30 + NZCV
 *  呼叫範例：  SNAP_GPRS  7, 1       ; idx=7, side=Asm
 * ────────────────────────────────────────────────*/
        .macro  SNAP_GPRS idx:req, side:req
            SNAP_FRAME_BEGIN    SNAP_GPR_SZ

            /* spill X0–X30 */
            .irp r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                         16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
                str     x\r, [x9, #(\r*8)]
            .endr
            /* NZCV */
            str     w20, [x9, #248]

            /* call C printer */
            mov     x0, x9              /* arg0 = spill ptr */
            mov     w1, \side           /* arg1 = side      */
            mov     w2, #\idx           /* arg2 = idx       */
            bl      _a64rf_dump_gprs_idx

            msr     nzcv, x20
            SNAP_FRAME_END    SNAP_GPR_SZ
        .endm

/* ────────────────────────────────────────────────
 *  向後相容別名：SNAP_REGS == SNAP_GPRS
 * ────────────────────────────────────────────────*/
        .macro  SNAP_REGS idx:req, side:req
            SNAP_GPRS \idx, \side
        .endm

/* ────────────────────────────────────────────────
 *  SNAP_VREGS idx, side, esz
 *      ① 512B   V0–V31
 *      ②  4B    FPSR (僅 QC bit會用到；靠額外寄存器傳給 C)
 *  (其餘與先前相同)
 * ────────────────────────────────────────────────*/
        .macro  SNAP_VREGS idx:req, side:req, esz=8
            SNAP_FRAME_BEGIN   SNAP_VREG_SZ

            /* spill V registers */
            .irp v, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                     16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                str     q\v, [x9, #(\v*16)]
            .endr

            /* 取 FPSR；QC 在 bit 27 */
            mrs     x19, fpsr
            and     w4, w19, #0x08000000      /* QC → w4 (0/1) */

            /* x0=buf, w1=side, w2=idx, w3=esz, w4=QC */
            mov     x0, x9
            mov     w1, \side
            mov     w2, #\idx
            mov     w3, #\esz
            bl      _a64rf_dump_vregs_idx

            SNAP_FRAME_END  SNAP_VREG_SZ
        .endm
/* ────────────────────────────────────────────────
 *  SNAP_ALL idx, side, esz
 *      spill 832 B = 304(GPR) + 512(V) + 16(FPSR pad)
 * ────────────────────────────────────────────────*/
        .macro  SNAP_ALL idx:req, side:req, esz=8
            SNAP_FRAME_BEGIN   SNAP_ALL_SZ

            /* -------- GPR 0-30 + NZCV -------- */
            .irp r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                         16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
                str     x\r, [x9, #(\r*8)]
            .endr
            str     w20, [x9, #248]

            /* -------- V0-V31 -------- */
            .irp v, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                     16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                str     q\v, [x9, #(SNAP_GPR_SZ + \v*16)]
            .endr

            /* -------- FPSR word (QC) -------- */
            mrs     x19, fpsr
            str     w19, [x9, #(SNAP_GPR_SZ + SNAP_VREG_SZ)]   /* offset 816 */

            /* x0=buf, w1=side, w2=idx, w3=esz */
            mov     x0, x9
            mov     w1, \side
            mov     w2, #\idx
            mov     w3, #\esz
            bl      _a64rf_dump_state_idx

            SNAP_FRAME_END  SNAP_ALL_SZ
        .endm
/* ────────────────────────────────────────────────
 *  SNAP_STATE idx, side, esz
 *      完整 CPU 快照 → 848 B
 *      GPR(304) + VREG(512) + FPSR(16) + PC/SP(16)
 *      esz = 8/16/32/64 (列印用 lane 大小，預設 8)
 * ────────────────────────────────────────────────*/
        .macro  SNAP_STATE idx:req, side:req, esz=8
            SNAP_FRAME_BEGIN   SNAP_STATE_SZ

            /* ---- GPRs ---- */
            .irp r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                         16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
                str x\r, [x9, #(\r*8)]
            .endr
            str w20, [x9, #248]                      /* NZCV */

            /* ---- VREGs ---- */
            .irp v, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                     16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                str q\v, [x9, #(SNAP_GPR_SZ + \v*16)]
            .endr

            /* ---- SYS ---- */
            mrs x19, fpsr
            str w19, [x9, #(SNAP_GPR_SZ + SNAP_VREG_SZ)]      /* FPSR */

            mov x19, lr                                       /* PC ≈ LR */
            str x19, [x9, #(SNAP_GPR_SZ + SNAP_VREG_SZ + 8)]

            mov x19, sp                                       /* SP */
            str x19, [x9, #(SNAP_GPR_SZ + SNAP_VREG_SZ + 16)]

            /* C shim: snapshot_dump(buf, side, idx, esz) */
            mov x0, x9
            mov w1, \side
            mov w2, #\idx
            mov w3, #\esz
            bl  _a64rf_snapshot_dump

            SNAP_FRAME_END  SNAP_STATE_SZ
        .endm
#else   /* !A64RF_TRACE ── 追蹤關閉時皆為空巨集 */

        .macro  SNAP_FRAME_BEGIN extra:req
        .endm
        .macro  SNAP_FRAME_END   extra:req
        .endm
        .macro  SNAP_GPRS idx:req, side:req
        .endm
        .macro  SNAP_REGS idx:req, side:req
        .endm
        .macro  SNAP_VREGS idx:req, side:req
        .endm
        .macro  SNAP_ALL idx:req, side:req
        .endm
        .macro  SNAP_STATE idx:req, side:req
        .endm

#endif  /* A64RF_TRACE */
#endif  /* __SNAP_MACRO_SAFE_INC__ */
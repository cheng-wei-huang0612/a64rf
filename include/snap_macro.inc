/*  safer SNAP_REGS  ────────────────────────────────────────────────
 *  idx  : 0‥4095  (手動序號)
 *  side : 0 = Ref, 1 = Asm
 *  堆疊總用量：16(FP/LR) + 16(x19,x20) + 32(x0-x3) + 304(spill) = 368 B
 *  ※ 仍保持 16-byte 對齊
 */
#ifndef __SNAP_MACRO_SAFE_INC__
#define __SNAP_MACRO_SAFE_INC__

#ifdef A64RF_TRACE
        .equ    SNAP_SAVE_SZ, 304

        .macro  SNAP_REGS idx:req, side:req
        /* ── 建立暫時 frame，保存 FP/LR ───────────────────────── */
        stp     x29, x30, [sp, -16]!
        mov     x29, sp

        /* ── 保存我們即將動用的 callee-saved x19, x20 ───────── */
        stp     x19, x20, [sp, -16]!

        /* ── 抓取並保存原始 NZCV 到 x20 (x20 現在屬臨時) ─────── */
        mrs     x20, nzcv

        /* ── 保存 caller-saved 參數暫存器 x0-x3 ─────────────── */
        stp     x0, x1, [sp, #-32]!       /* sp-=32, 存 x0,x1          */
        stp     x2, x3, [sp, #16]         /* 存 x2,x3                  */

        /* ── 分配 304B spill 區，對齊 16 ───────────────────── */
        sub     sp, sp, #SNAP_SAVE_SZ
        mov     x9, sp                    /* x9 = spill base (caller-saved) */

        /* ── Spill X0-X30 (31 個通用暫存器) ─────────────────── */
        .irp r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                     16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
            str     x\r, [x9, #(\r*8)]
        .endr

        /* ── 存入 NZCV snapshot ─────────────────────────────── */
        str     w20, [x9, #248]           /* 248 = 0xF8 */

        /* ── 呼叫列印函式 (僅破壞 caller-saved) ─────────────── */
        mov     x0, x9                    /* arg0 = spill ptr          */
        mov     w1, \side                 /* arg1 = side               */
        mov     w2, #\idx                 /* arg2 = idx                */
        bl      _a64rf_dump_regs_idx

        /* ── 還原原始 NZCV，保持呼叫者旗標不變 ─────────────── */
        msr     nzcv, x20

        /* ── 釋放 spill 區並還原暫存器 ─────────────────────── */
        add     sp, sp, #SNAP_SAVE_SZ

        ldp     x2, x3, [sp, #16]
        ldp     x0, x1, [sp], #32

        ldp     x19, x20, [sp], 16        /* 復原 x19, x20 */
        ldp     x29, x30, [sp], 16        /* 恢復 FP/LR，回到原 stack */

        .endm
#else
        .macro  SNAP_REGS idx:req, side:req
        .endm
#endif  /* A64RF_TRACE */
#endif  /* __SNAP_MACRO_SAFE_INC__ */
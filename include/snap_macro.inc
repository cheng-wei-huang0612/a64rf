/*  SNAP_REGS idx, side   ───────────────────────────────────────────
 *     idx  : 0‥4095    (手動指定序號)
 *     side : 0 = Ref,  1 = Asm
 *
 *  佔用 stack：32 (+4 保存暫存器) + 256 (GPR spill) + 8 (NZCV) = 296
 *  取整 16 → 我們用 304  (0x130) Bytes
 */
#ifndef __SNAP_MACRO_SAFE_INC__
#define __SNAP_MACRO_SAFE_INC__

#ifdef A64RF_TRACE
        .macro  SNAP_REGS idx:req, side:req

        stp     x29, x30, [sp, -16]!
        mov     x29, sp



        /* -------------------------------------------------------- *
         * 1) 先保存 caller-saved 參數暫存器 x0‥x3                  *
         * -------------------------------------------------------- */
        stp     x0, x1, [sp, #-32]!      /* 把 sp 往下開 32B 並存 x0,x1 */
        stp     x2, x3, [sp, #16]        /* 存 x2,x3 */

        /* -------------------------------------------------------- *
         * 2) 再為暫存區開 256+8 = 264 Bytes (對齊到 304)           *
         * -------------------------------------------------------- */
        sub     sp, sp, #304
        mov     x19, sp                  /* x19 = spill base */

        /* Spill X0‥X30 (31 個) ；用 x20 當暫存寄存器            */
        .irp r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,\
                     16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
            str     x\r, [x19, #(\r*8)]
        .endr

        /* NZCV 放在 offset 0xF8 (= 248)                         */
        mrs     x20, nzcv
        str     w20, [x19, #248]

        /* x0 = spill-ptr, w1 = side, w2 = idx                    */
        mov     x0, x19
        mov     w1, \side
        mov     w2, #\idx
        bl      _a64rf_dump_regs_idx

        /* -------------------------------------------------------- *
         * 3) 還原堆疊 & 暫存器                                   *
         * -------------------------------------------------------- */
        add     sp, sp, #304
        ldp     x2, x3, [sp, #16]
        ldp     x0, x1, [sp], #32

        ldp     x29, x30, [sp], 16
        .endm
#else
        .macro  SNAP_REGS idx:req, side:req
        .endm
#endif  /* A64RF_TRACE */
#endif  /* __SNAP_MACRO_SAFE_INC__ */
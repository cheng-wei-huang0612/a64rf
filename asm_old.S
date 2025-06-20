/**********************************************************************
 *  foo_asm.S  —  demo               (build with -DA64RF_TRACE)
 *
 *  void foo(uint64_t *dst, const uint64_t *src);
 *      dst[0] = src[0] * src[1]
 *      dst[1] = src[0] + src[1]
 *********************************************************************/

        #include "snap_macro.inc"     /* 提供 SNAP_REGS idx,side */

        .text
        .globl  _foo                 /* macOS 需前導底線；ELF 可寫 foo */
        .p2align 2
_foo:   

        stp     x29, x30, [sp, -16]!
        mov     x29, sp
        /* ── snapshot #0 入口狀態 ── */
#ifdef A64RF_TRACE
        SNAP_REGS 0, 1               /* idx=0, side=1 (Asm) */

#endif

        /* X0 = dst,  X1 = src */
        ldr     x2, [x1]             /* src[0] */
        ldr     x3, [x1, #8]         /* src[1] */

        mul     x4, x2, x3
        str     x4, [x0]             /* dst[0] */

        adds    x5, x2, x3
        str     x5, [x0, #8]         /* dst[1] */

        /* ── snapshot #1 出口狀態 ── */
#ifdef A64RF_TRACE

        SNAP_REGS 1, 1               /* idx=1, side=1 (Asm) */
#endif

        ldp     x29, x30, [sp], 16
        ret
#ifndef __A64RF_MACROS_INC__
#define __A64RF_MACROS_INC__

#include "a64rf_offsets.h"

#ifdef A64RF_TRACE
    /* side = 0 (ref) 或 1 (asm) */
    .macro SNAP_C side:req
        /* 備份暫存器 */
        sub     sp, sp, #16
        stp     x9, x10, [sp]

        mov     x9, x0             /* base 指標 (state*) */

        /* ---- GPR ---- */
        .irp    r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
            str x\r, [x9, #OFF_GPR(\r)]
        .endr

        // /* ---- SIMD ---- */
        // .irp    i, 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30
        //     stp q\i, q\i+1, [x9, #OFF_SIMD(\i)]
        // .endr

        /* ---- NZCV ---- */
        mrs     x10, nzcv
        str     w10, [x9, #OFF_NZCV]

        /* 呼叫 shim (x0=state*, x1=side) */
        mov     x1, #\side
        bl      _a64rf_snap_shim

        /* 還原 */
        ldp     x9, x10, [sp], #16
    .endm
#else
    .macro SNAP_C side:req    /* release: 空宏 */
    .endm
#endif /* A64RF_TRACE */

#endif /* __A64RF_MACROS_INC__ */

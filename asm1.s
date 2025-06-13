# 1 "asm.s"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 464 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "asm.s" 2
# 1 "include/macros.inc" 1




# 1 "include/a64rf_offsets.h" 1









   






# 5 "include/macros.inc" 2


    
    .macro SNAP_C side:req
        
        sub     sp, sp, #16
        stp     x9, x10, [sp]

        mov     x9, x0             

        
        .irp    r, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
            str x\r, [x9, #( (\r) * 8 )]
        .endr

        
        .irp    i, 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30
            stp q\i, q\i+1, [x9, #( 8*31 + (\i) * 16 )]
        .endr

        
        mrs     x10, nzcv
        str     w10, [x9, #( 8*31 + 16*32 )]

        
        mov     x1, #\side
        bl      a64rf_snap_shim

        
        ldp     x9, x10, [sp], #16
    .endm






# 2 "asm.s" 2
    .text
    .global foo_asm
foo_asm:
    stp x29, x30, [sp, -16]!
    mov x29, sp

    SNAP_C 1          // snapshot #0 (asm)

    ldr x2, [x0, #( (0) * 8 )]   // X0
    ldr x3, [x0, #( (1) * 8 )]   // X1
    mul x4, x2, x3
    str x4, [x0, #( (2) * 8 )]   // X2
    SNAP_C 1          // snapshot #1

    adds x5, x4, x3
    str  x5, [x0, #( (3) * 8 )]  // X3
    SNAP_C 1          // snapshot #2

    mrs  x6, nzcv
    str  w6, [x0, #( 8*31 + 16*32 )]

    ldp x29, x30, [sp], 16
    ret

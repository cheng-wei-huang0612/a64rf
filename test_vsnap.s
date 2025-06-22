    .globl test_vsnap
test_vsnap:
    movi    v0.16b,  #0x11      /* 填充測試資料 */
    movi    v31.16b, #0xFF
    SNAP_VREGS  42, 1
    ret

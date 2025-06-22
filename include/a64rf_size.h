#ifndef A64RF_SIZES_H
#define A64RF_SIZES_H
#define SNAP_GPR_SZ    304     /* X0-X30 + NZCV */
#define SNAP_VREG_SZ   512     /* V0-V31       */
#define SNAP_FPSR_SZ    16     /* 4B FPSR +12 pad (仍占 16) */
#define SNAP_PCSP_SZ    16     /* 8B PC + 8B SP */
#define SNAP_STATE_SZ  (SNAP_GPR_SZ + SNAP_VREG_SZ + \
                        SNAP_FPSR_SZ + SNAP_PCSP_SZ)   /* 848 */
#endif
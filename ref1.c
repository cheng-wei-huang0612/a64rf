/* ref1.c －－ minimal playground --------------------------------------- */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "a64rf_types.h"
#include "a64rf_api.h"
#include "a64rf_op.h"


#define DUMP_GPR(s, r)  print_val_gpr_to_hex(&(s), r)
#define DUMP_NZCV(s)    printf("NZCV = N:%u Z:%u C:%u V:%u\n", \
                               (s).nzcv.N, (s).nzcv.Z, \
                               (s).nzcv.C, (s).nzcv.V)

int main(void)
{
    a64rf_state_t s;
    memset(&s, 0, sizeof s);

    /* ─────────────────────── Stage-0：初值 ─────────────────────── */
    write_val_gpr(&s, X0,  0xfffffffffffffff0ULL); /*   2^64 − 16  */
    write_val_gpr(&s, X1,  0x20ULL);               /*  +32         */
    write_val_gpr(&s, X2,  0ULL);                  /* 清空目標暫存器 */
    puts("=== Initial ===");
    DUMP_GPR(s, X0);  DUMP_GPR(s, X1);  DUMP_NZCV(s);

    /* ─────────────────────── Stage-1：ADDS 溢位邊界 ─────────────── */
    puts("\n=== ADDS X2, X0, X1  (expect C=1, V=0) ===");
    adds_xform(&s, X2, X0, X1);        /* (2^64−16) + 32 → 0x20 − 0x10 = 16 進位 */
    DUMP_GPR(s, X2);  DUMP_NZCV(s);    /* N=0 Z=0 C=1 V=0 */

    /* ─────────────────────── Stage-2：ADCS 串接 Carry ───────────── */
    puts("\n=== ADCS X3, X2, X2  (use previous C=1) ===");
    adcs_xform(&s, X3, X2, X2);        /* 16+16+1 → 33；C 應該清回 0 */
    DUMP_GPR(s, X3);  DUMP_NZCV(s);    /* N=0 Z=0 C=0 V=0 */

    /* ─────────────────────── Stage-3：SUBS 產生負數 & Borrow ───── */
    puts("\n=== SUBS X4, X2, X3  (16 − 33 = −17) ===");
    subs_xform(&s, X4, X2, X3);
    DUMP_GPR(s, X4);  DUMP_NZCV(s);    /* N=1 Z=0 C=0 V=0 */

    /* ─────────────────────── Stage-4：SBCS 吃 Borrow 再減────────── */
    puts("\n=== SBCS X5, X4, X0  (−17 − (¬C) − ... ) ===");
    sbcs_xform(&s, X5, X4, X0);        /* C=0 → borrow=1 */
    DUMP_GPR(s, X5);  DUMP_NZCV(s);

    /* ─────────────────────── Stage-5：CMP & CMN 對照 ───────────── */
    puts("\n=== CMP X3, X3  (should set Z=1) ===");
    cmp_xform(&s, X3, X3);             /* 33−33 → 0 */
    DUMP_NZCV(s);                      /* N=0 Z=1 C=1 V=0 */

    puts("\n=== CMN X3, X0  (33 + (2^64−16) , expect C=1) ===");
    cmn_xform(&s, X3, X0);
    DUMP_NZCV(s);

    /* ─────────────────────── Stage-6：ANDS / EORS S-variant ─────── */
    puts("\n=== ANDS X6, X3, X2  (flags N/Z only, C=V=0) ===");
    ands_xform(&s, X6, X3, X2);
    DUMP_GPR(s, X6);  DUMP_NZCV(s);

    puts("\n=== EORS X7, X3, X3  (結果0, Z=1, C=V=0) ===");
    eors_xform(&s, X7, X3, X3);
    DUMP_GPR(s, X7);  DUMP_NZCV(s);

    return 0;
}
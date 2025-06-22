/* example009.c – showcase of a64rf printing helpers  */
#include <stdio.h>
#include <string.h>
#include "a64rf.h"

int main(void)
{
    /* -------------------------------------------------------- *
     * 建立乾淨狀態，並準備幾組可視化資料                         *
     * -------------------------------------------------------- */
    a64rf_state_t s = {0};              /* 全零起始 */
    initialize_a64rf_state(&s);         /* 若你啟用了預設 PC/SP 初值 */

    /* 通用暫存器 */
    write_val_gpr(&s, X0, 0xF23456789ABCDEF0ULL);
    write_val_gpr(&s, X1, 0xFFEDCBA987654321ULL);
    /* 向量暫存器 V0 = {lo = 0xAA55AA55…, hi = 0x55AA55AA…} */
    write_d_vreg_lo(&s, V0, 0xAA55AA55AA55AA55ULL);
    write_d_vreg_hi(&s, V0, 0x55AA55AA55AA55AAULL);

    puts("=== GPR value (hex / dec / oct) ===");
    print_val_gpr_to_unsigned_hex(&s, X0);
    print_val_gpr(&s, X0, RADIX_DEC, true);
    print_val_gpr(&s, X0, RADIX_OCT, false);

    puts("\n=== Vector register interpret as {2D,4S,8H,16B} ===");
    print_vreg_as_2d(&s, V0);
    print_vreg_as_4s(&s, V0);
    print_vreg_as_8h(&s, V0);
    print_vreg_as_16b(&s, V0);

    /* 做些簡單運算以改變 NZCV ------------------------------------------------ */
    puts("\n=== ADDS & flag demo ===");
    print_val_gpr_to_unsigned_hex(&s, X0);
    print_val_gpr_to_unsigned_hex(&s, X1);
    print_nzcv(&s);

    puts("\n=== PERFORM ADDS X2, X0, X1 ===");
    adds_xform(&s, X2, X0, X1);     /* 64 bit 加法，更新旗標 */
    print_val_gpr_to_unsigned_hex(&s, X2);
    print_nzcv(&s);

    /* 再來個零結果觀察 Z flag --------------------------------------------- */
    puts("\n=== PERFORM SUBS XZR, X2, X2 ===");
    subs_xform(&s, XZR /*丟棄*/, X2, X2);  /* SUBS … → 0 */
    print_nzcv(&s);


}

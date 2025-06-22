/* example004.c - BICS instruction example */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "a64rf.h"

int main(void)
{
    a64rf_state_t s;
    memset(&s, 0, sizeof s);

    /* Scenario 1 */
    write_val_gpr(&s, X1, 0xff00ff00ff00ff00ULL);
    write_val_gpr(&s, X2, 0x00ff00ff00ff00ffULL);

    puts("=== BICS X3, X1, X2 ===");
    bics_xform(&s, X3, X1, X2);

    print_val_gpr_to_unsigned_hex(&s, X3);
    print_nzcv(&s);

    /* Scenario 2: zero result */
    puts("\n=== BICS X4, X1, X1 ===");
    bics_xform(&s, X4, X1, X1);

    print_val_gpr_to_hex(&s, X4);
    print_nzcv(&s);

    /* Scenario 3: different operands */
    write_val_gpr(&s, X5, 0xf0f0f0f0f0f0f0f0ULL);
    write_val_gpr(&s, X6, 0x0f0f0f0f0f0f0f0fULL);

    puts("\n=== BICS X7, X5, X6 ===");
    bics_xform(&s, X7, X5, X6);

    print_val_gpr_to_unsigned_hex(&s, X7);
    print_nzcv(&s);

    return 0;
}

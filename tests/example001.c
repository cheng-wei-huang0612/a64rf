/* example001.c - ADDS boundary example */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "a64rf.h"



int main(void)
{
    a64rf_state_t s;
    memset(&s, 0, sizeof s);

    /* Stage 0: initial values */
    write_val_gpr(&s, X0, 0xfffffffffffffff0ULL);
    write_val_gpr(&s, X1, 0x20ULL);
    write_val_gpr(&s, X2, 0ULL);
    puts("=== Initial ===");

    print_val_gpr_to_hex(&s, X0);
    print_val_gpr_to_hex(&s, X1);
    print_nzcv(&s);


    /* Stage 1: ADDS overflow boundary */
    puts("\n=== ADDS X2, X0, X1 ===");
    adds_xform(&s, X2, X0, X1);

    print_val_gpr_to_hex(&s, X2);
    print_nzcv(&s);


    return 0;
}

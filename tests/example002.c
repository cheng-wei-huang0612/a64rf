/* example002.c - ADCS and SUBS examples */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "a64rf_types.h"
#include "a64rf_api.h"
#include "a64rf_op.h"



int main(void)
{
    a64rf_state_t s;
    memset(&s, 0, sizeof s);

    /* Prepare some values via ADDS */
    write_val_gpr(&s, X0, 0x10ULL);
    write_val_gpr(&s, X1, 0x10ULL);
    adds_xform(&s, X2, X0, X1); /* result 0x20, C cleared */

    /* Stage 2: ADCS chaining carry */
    puts("=== ADCS X3, X2, X2 ===");
    adcs_xform(&s, X3, X2, X2);

    print_val_gpr_to_hex(&s, X3);
    print_nzcv(&s);


    /* Stage 3: SUBS negative result */
    puts("\n=== SUBS X4, X2, X3 ===");
    subs_xform(&s, X4, X2, X3);

    print_val_gpr_to_hex(&s, X4);
    print_nzcv(&s);


    return 0;
}

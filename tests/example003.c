/* example003.c - SBCS, CMP/CMN and logical flag updates */
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "a64rf.h"


int main(void)
{
    a64rf_state_t s;
    memset(&s, 0, sizeof s);

    write_val_gpr(&s, X2, 0x10ULL);
    write_val_gpr(&s, X3, 0x21ULL);

    /* Stage 4: SBCS with borrow */
    puts("=== SBCS X5, X3, X2 ===");
    sbcs_xform(&s, X5, X3, X2);

    print_val_gpr_to_hex(&s, X5);
    print_nzcv(&s);

    /* Stage 5: CMP and CMN */
    puts("\n=== CMP X3, X3 ===");
    cmp_xform(&s, X3, X3);

    print_nzcv(&s);

    puts("\n=== CMN X3, X2 ===");
    cmn_xform(&s, X3, X2);
    print_nzcv(&s);


    /* Stage 6: ANDS and EORS */
    puts("\n=== ANDS X6, X3, X2 ===");
    ands_xform(&s, X6, X3, X2);

    print_val_gpr_to_hex(&s, X6);
    print_nzcv(&s);




    return 0;
}

/* example003.c - SBCS, CMP/CMN and logical flag updates */
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

    write_val_gpr(&s, X2, 0x10ULL);
    write_val_gpr(&s, X3, 0x21ULL);

    /* Stage 4: SBCS with borrow */
    puts("=== SBCS X5, X3, X2 ===");
    sbcs_xform(&s, X5, X3, X2);
    DUMP_GPR(s, X5);  DUMP_NZCV(s);

    /* Stage 5: CMP and CMN */
    puts("\n=== CMP X3, X3 ===");
    cmp_xform(&s, X3, X3);
    DUMP_NZCV(s);

    puts("\n=== CMN X3, X2 ===");
    cmn_xform(&s, X3, X2);
    DUMP_NZCV(s);

    /* Stage 6: ANDS and EORS */
    puts("\n=== ANDS X6, X3, X2 ===");
    ands_xform(&s, X6, X3, X2);
    DUMP_GPR(s, X6);  DUMP_NZCV(s);

    puts("\n=== EORS X7, X3, X3 ===");
    eors_xform(&s, X7, X3, X3);
    DUMP_GPR(s, X7);  DUMP_NZCV(s);

    return 0;
}

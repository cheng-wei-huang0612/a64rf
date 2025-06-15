/* example001.c - ADDS boundary example */
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

    /* Stage 0: initial values */
    write_val_gpr(&s, X0, 0xfffffffffffffff0ULL);
    write_val_gpr(&s, X1, 0x20ULL);
    write_val_gpr(&s, X2, 0ULL);
    puts("=== Initial ===");
    DUMP_GPR(s, X0);  DUMP_GPR(s, X1);  DUMP_NZCV(s);

    /* Stage 1: ADDS overflow boundary */
    puts("\n=== ADDS X2, X0, X1 ===");
    adds_xform(&s, X2, X0, X1);
    DUMP_GPR(s, X2);  DUMP_NZCV(s);

    return 0;
}

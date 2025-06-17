

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "a64rf.h"





int main(void)
{
    a64rf_state_t s = initialize_a64rf_state();

    write_val_gpr(&s, X0, (uint64_t)1);
    write_val_gpr(&s, X1, (uint64_t)1);

    write_d_vreg_hi(&s, V0, (uint64_t)2);
    write_d_vreg_lo(&s, V0, (uint64_t)2);
    write_d_vreg_hi(&s, V1, (uint64_t)2);
    write_d_vreg_lo(&s, V1, (uint64_t)2);


    add_xform(&s, X2, X0, X1);
    print_val_gpr(&s, X2, NULL);

    add_dform(&s, V2, V0, V1);
    print_vreg_as_2d(&s, V2);


    return 0;
}

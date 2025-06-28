#include "a64rf.h"

#include <assert.h>

int main(void)
{

uint8_t a[VREG_B_LANE_COUNT] = {
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0,
    1, 0, 0, 0
};

uint8_t b[VREG_B_LANE_COUNT] = {
    -1, 0, 0, 0,
    -1, 0, 0, 0,
    -3, 0, 0, 0,
    -2, 0, 0, 0
};

a64rf_state_t st;
a64rf_state_init(&st, 0, 0);          /* 4 KB stack、64 KB heap */

write_all_b_vreg(&st, V0, a);
write_all_b_vreg(&st, V1, b);

smull_vd8h_vn8b_vm8b(&st, V2, V0, V1);
smull2_vd8h_vn16b_vm16b(&st, V2, V0, V1);

print_vreg_as_8h(&st, V2);





}

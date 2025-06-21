#include <stdio.h>
#include "a64rf.h"
#include "a64rf/api/state.h"


static inline void push_u64(a64rf_state_t *s, uint64_t value)
{
    s->sp.val -= 8;                          // stack grows downward
    *((uint64_t *)s->sp.val) = value;        // store value
}

static inline uint64_t pop_u64(a64rf_state_t *s)
{
    uint64_t value = *((uint64_t *)s->sp.val); // load
    s->sp.val += 8;                            // free space
    return value;
}


int main(void)
{
    a64rf_state_t st = {0};
    initialize_a64rf_state(&st);


    /* Fill a few registers with sample values */
    write_val_gpr(&st, X0, 2);
    write_val_gpr(&st, X1, 3);
    write_val_gpr(&st, X2, 5);

    /* Demonstrate add_xform and mul_xform */
    add_xform(&st, X3, X0, X1); /* X3 = X0 + X1 = 5 */
    mul_xform(&st, X4, X3, X2); /* X4 = X3 * X2 = 25 */

    /* Example vector contents using the API */
    write_d_vreg_lo(&st, V0, 0x0123456789abcdefULL);
    write_d_vreg_hi(&st, V0, 0xfedcba9876543210ULL);
    write_d_vreg_lo(&st, V1, 0x1111111111111111ULL);
    write_d_vreg_hi(&st, V1, 0x2222222222222222ULL);

    /* Vector addition via helper */
    add_dform(&st, V2, V0, V1);

    
    push_u64(&st, 0x0123456789ABCDEF);

    puts("\n--- Stack Dump ---");
    print_stack(&st);


    return 0;
}

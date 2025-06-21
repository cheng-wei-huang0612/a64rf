#include <stdio.h>
#include "a64rf.h"
#include "a64rf/api/state.h"

int main(void)
{
    a64rf_state_t st = initialize_a64rf_state();

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

    /* Store some bytes on the stack and in memory */
    for (size_t i = 0; i < 16; ++i) {
        st.stack[i]  = (uint8_t)i;
        st.memory[i] = (uint8_t)(0xff - i);
    }

    puts("--- General Purpose Registers and Flags ---");
    print_gprs_and_nzcv(&st);

    puts("\n--- Vector Registers and FPSR ---");
    print_vregs_and_fpsr(&st);

    puts("\n--- Stack Dump ---");
    print_stack(&st);

    puts("\n--- Memory Dump ---");
    print_memory(&st);

    puts("\n--- Complete State ---");
    print_state(&st);

    return 0;
}

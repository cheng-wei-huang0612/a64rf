#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "a64rf.h"

int main(void)
{
    int64_t a, b, c;
    a = 1;
    b = 10;
    c = 5;




    a64rf_state_t state = initialize_a64rf_state();
    a64rf_program_t program = initialize_a64rf_program_t();
    write_val_gpr(&state, X0, (uint64_t)a);
    write_val_gpr(&state, X1, (uint64_t)b);
    write_val_gpr(&state, X2, (uint64_t)c);
    write_val_gpr(&state, X3, (uint64_t)2);






    mul_xd_xn_xm(&program, X1, X1, X2);
    add_xd_xn_xm(&program, X0, X0, X1);
    mul_xd_xn_xm(&program, X1, X1, X3);
    sub_xd_xn_xm(&program, X1, X0, X1);


    ret(&program);
    // program.insts[10].op = OP_RET;
    // program.insts[10].target_pc.val = (uint16_t)-1;



    printf("%d\n\n",program.insts[1].op);
    





    print_val_gpr(&state, X0, RADIX_DEC, true);
    print_val_gpr(&state, X1, RADIX_DEC, true);
    print_val_gpr(&state, X2, RADIX_DEC, true);

    run_program_on_state(&program, &state);


    print_val_gpr(&state, X0, RADIX_DEC, true);
    print_val_gpr(&state, X1, RADIX_DEC, true);
    print_val_gpr(&state, X2, RADIX_DEC, true);



    return 0;
}

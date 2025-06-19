#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "a64rf.h"

int main(void)
{
    a64rf_state_t state = initialize_a64rf_state();
    a64rf_program_t program = initialize_a64rf_program_t();


    printf("%d\n\n",program.insts[1].op);


    add_xd_xn_xm(&program, X0, X1, X2);


    ret(&program);
    // program.insts[10].op = OP_RET;
    // program.insts[10].target_pc.val = (uint16_t)-1;



    printf("%d\n\n",program.insts[1].op);
    


    write_val_gpr(&state, X0, (uint64_t)0);
    write_val_gpr(&state, X1, (uint64_t)1);
    write_val_gpr(&state, X2, (uint64_t)2);


    print_val_gpr(&state, X0, NULL);
    print_val_gpr(&state, X1, NULL);
    print_val_gpr(&state, X2, NULL);

    run_program_on_state(&program, &state);


    print_val_gpr(&state, X0, NULL);
    print_val_gpr(&state, X1, NULL);
    print_val_gpr(&state, X2, NULL);



    return 0;
}

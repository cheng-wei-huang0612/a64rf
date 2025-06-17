#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "a64rf.h"

int main(void)
{
    a64rf_state_t state = initialize_a64rf_state();
    a64rf_program_t program = initialize_a64rf_program_t();


    printf("%d\n\n",program.insts[1].op);


    program.insts[3].op = OP_RET;
    program.insts[3].target_pc.val = (uint16_t)-1;


    printf("%d\n\n",program.insts[1].op);
    
    run_program_on_state(&program, &state);



    return 0;
}

#include <stdbool.h>
#include <string.h> 
#include "../types.h"
#include "api/gpr.h"
#include "api/flags.h"
#include "api/vreg/read.h"
#include "api/vreg/print.h"
#include "api/vreg/write.h"

void wipe(void *p, size_t n) {
    memset(p, 0, n);   /* 原型與 memset 完全相同 */
}



// a64rf_state_t initialize_a64rf_state(a64rf_state_t * state)
// {
//     a64rf_state_t state = {0};

//     for (size_t i = 0; i < GPR_COUNT; i++)
//     {
//         write_zero_gpr((&state), i);
//     }

//     for (size_t i = 0; i < VREG_COUNT; i++)
//     {
//         write_zero_vreg((&state), i);
//     }

//     //state.sp.val =(void *)&state.stack[STACK_SIZE-1];
//     state.sp.val = &state.stack[STACK_SIZE-1];

//     wipe(state.stack, sizeof(state.stack));

//     wipe(state.memory, sizeof(state.memory));
    
//     state.pc.val = 0;


//     write_zero_nzcv(&state);

//     write_zero_fpsr(&state);
    
//     return state;
// }

void initialize_a64rf_state(a64rf_state_t *state)
{  
    for (size_t i = 0; i < GPR_COUNT; i++)
    {
        write_zero_gpr(state, i);
    }

    for (size_t i = 0; i < VREG_COUNT; i++)
    {
        write_zero_vreg(state, i);
    }

    state->sp.val = &state->stack[STACK_SIZE];

    wipe(state->stack, sizeof(state->stack));

    wipe(state->memory, sizeof(state->memory));
    
    state->pc.val = 0;

    write_zero_nzcv(state);

    write_zero_fpsr(state);
    


}




a64rf_state_t eor_a64rf_state(a64rf_state_t *state1, a64rf_state_t *state2)
{
    // generate delta = state1 ^ state2

    a64rf_state_t delta_state = {0};

    for (size_t i = 0; i < GPR_COUNT; i++)
    {
        uint64_t val1 = read_val_gpr(state1, i);
        uint64_t val2 = read_val_gpr(state2, i);
        uint64_t val = val1 ^ val2;
        write_val_gpr(&delta_state, i, val);
    }
       
    for (size_t i = 0; i < VREG_COUNT; i++)
    {
        uint64_t val1 = read_val_gpr(state1, i);
        uint64_t val2 = read_val_gpr(state2, i);
        uint64_t val = val1 ^ val2;
        write_val_gpr(&delta_state, i, val);
    }
       
}

bool a64rf_state_eor_zero(a64rf_state_t *state)
{
    // return true if state = zero state

}


bool equal_a64rf_state(a64rf_state_t *state1, a64rf_state_t *state2)
{
    // delta_state = state1 ^ state2
    // return true if delta_state = 0

}




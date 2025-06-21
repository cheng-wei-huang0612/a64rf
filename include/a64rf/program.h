#include <stdbool.h>
#include <string.h> 
#include "../types.h"
#include "api/gpr.h"
#include "api/flags.h"
#include "api/vreg/read.h"
#include "api/vreg/print.h"
#include "api/vreg/write.h"
#include "run_program.h"


static inline a64rf_program_t initialize_a64rf_program_t(void)
{
    a64rf_program_t program;
    for (size_t i = 0; i < MAX_INSTRUCTION_LEN; i++)
    {
        program.insts[i].op = OP_NULL;
    }

    program.add_instruction_to_program.val = 0;

    return program;
}

// static inline pc_t increment_pc(pc_t old_pc)
// {
//     pc_t new_pc;
//     new_pc.val = (old_pc.val + 1);
//     return new_pc;
// }




void run_program_on_state(a64rf_program_t *program, a64rf_state_t *state) 
{
    if (state->pc.val != 0) {
        fprintf(stderr, "Alert: state->pc.val is not zero (value: %llu)\n", (unsigned long long)state->pc.val);
    }

    // we should get the respective pc for each label first.
    // 1. collect all branching insructions 
    // 2. collect all labels
    // 3. replace all target_pc of branching instructions with correct porgram coordinates
    // 4. check if there is any branching instructions are invalid (i.e., no corresponding label)


    while (state->pc.val != UINT16_MAX)
    {
        const a64rf_instruction_t current_instruction = program->insts[state->pc.val];


        // run the instruction on state
        // this function will do pc+=1 (or branching) on the state
        run_instruction_on_state(&current_instruction, state);

    }
    

    return;
    
}



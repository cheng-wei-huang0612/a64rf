#include <stdbool.h>
#include <string.h> 
#include "../types.h"
#include "api/gpr.h"
#include "api/flags.h"
#include "api/vreg/read.h"
#include "api/vreg/print.h"
#include "api/vreg/write.h"


static inline a64rf_program_t initialize_a64rf_program_t(void)
{
    a64rf_program_t program;
    for (size_t i = 0; i < MAX_INSTRUCTION_LEN; i++)
    {
        program.insts[i].op = OP_NULL;
    }

    return program;
}

pc_t increment_pc(pc_t old_pc)
{
    pc_t new_pc;
    new_pc.val = (old_pc.val + 1);
    return new_pc;
}

void run_instruction_on_state(a64rf_instruction_t *instruction, a64rf_state_t *state)
{
    if (instruction->op == OP_NULL) {
        state->pc.val += 1;
    }

    if (instruction->op == OP_RET) 
    {
        state->pc = instruction->target_pc;
    }
    
}


void run_program_on_state(a64rf_program_t *program, a64rf_state_t *state) 
{
    if (state->pc.val != 0) {
        fprintf(stderr, "Alert: state->pc.val is not zero (value: %llu)\n", (unsigned long long)state->pc.val);
    }

    // we should get the respective pc for each label first.


    a64rf_instruction_t current_instruction;
    for (size_t i = 0; i < MAX_INSTRUCTION_LEN; i++)
    {
        current_instruction = program->insts[state->pc.val];


        printf("current pc is %d", state->pc.val);
        if (current_instruction.op == OP_NULL) {
            printf("current instruction is NULL\n\n");
        }
        else if (current_instruction.op == OP_RET) {
            printf("current instruction is RET\n\n");
        }
        else {
            printf("current instruction opcode is %d\n\n", current_instruction.op);
        }

        // run the instruction on state
        // this function will do pc+=1 (or branching) on the state
        run_instruction_on_state(&current_instruction, state);

        if (state->pc.val == (uint16_t)-1)
        {
            // end of program
            return;
        }


        
    }
    
}


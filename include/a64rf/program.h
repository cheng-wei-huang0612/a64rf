#include <stdbool.h>
#include <string.h> 
#include "../types.h"
#include "api/gpr.h"
#include "api/flags.h"
#include "api/vreg/read.h"
#include "api/vreg/print.h"
#include "api/vreg/write.h"
#include "op/a64rf_op_gpr.h"
#include "op/a64rf_op_neon.h"

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

pc_t increment_pc(pc_t old_pc)
{
    pc_t new_pc;
    new_pc.val = (old_pc.val + 1);
    return new_pc;
}

void run_instruction_on_state(const a64rf_instruction_t *instruction, a64rf_state_t *state)
{
    if (instruction->op == OP_NULL) {
        state->pc.val += 1;
    }

    if (instruction->op == OP_RET) 
    {
        state->pc = instruction->target_pc;
    }

    if (instruction->op == OP_ADD)
    {
        state->pc.val += 1;
        printf("perform add %d, %d, %d\n\n", instruction->dst, instruction->src0, instruction->src1);
        add_xform(state, instruction->dst, instruction->src0, instruction->src1);
        
    }
    
    
}


void run_program_on_state(a64rf_program_t *program, a64rf_state_t *state) 
{
    if (state->pc.val != 0) {
        fprintf(stderr, "Alert: state->pc.val is not zero (value: %llu)\n", (unsigned long long)state->pc.val);
    }

    // we should get the respective pc for each label first.


    while (state->pc.val != UINT16_MAX)
    {
        const a64rf_instruction_t current_instruction = program->insts[state->pc.val];

        printf("current pc is %d. ", state->pc.val);
        if (current_instruction.op == OP_NULL) {
            printf("current instruction is NULL\n\n");
        }
        else if (current_instruction.op == OP_NOP) {
            printf("current instruction is RET\n\n");
        }
        else if (current_instruction.op == OP_RET) {
            printf("current instruction is RET\n\n");
        }
        else if (current_instruction.op == OP_ADD) {
            printf("current instruction is ADD\n\n");
        }
        else {
            printf("current instruction opcode is %d\n\n", current_instruction.op);
        }

        // run the instruction on state
        // this function will do pc+=1 (or branching) on the state
        run_instruction_on_state(&current_instruction, state);

    }
    

    return;
    
}

void add_xd_xn_xm(a64rf_program_t *program, a64rf_gpr_idx_t dst, a64rf_gpr_idx_t src0, a64rf_gpr_idx_t src1) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_ADD;
    instruction.dst = dst;
    instruction.src0 = src0;
    instruction.src1 = src1;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc = increment_pc(program->add_instruction_to_program);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}


void ret(a64rf_program_t *program) 
{
    a64rf_instruction_t instruction;
    instruction.op = OP_RET;
    instruction.dst = XZR;
    instruction.src0 = XZR;
    instruction.src1 = XZR;
    instruction.src2 = XZR;
    instruction.imm0 = 0;
    instruction.imm1 = 0;
    instruction.imm2 = 0;
    instruction.shift_type = SHIFT_NONE;
    instruction.target_pc.val = (uint16_t)(-1);
    
    program->insts[program->add_instruction_to_program.val] = instruction;
    program->add_instruction_to_program = increment_pc(program->add_instruction_to_program);
}
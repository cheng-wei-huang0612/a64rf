#include <stdbool.h>
#include <string.h> 
#include "../types.h"

#include "op/a64rf_op_gpr.h"
#include "op/a64rf_op_neon.h"



void run_instruction_on_state(const a64rf_instruction_t *instruction,
                              a64rf_state_t *state)
{
    state->pc.val += 1;

    switch (instruction->op) {

    case OP_NULL:
        state->pc.val += 1;
        break;

    case OP_RET:
        state->pc = instruction->target_pc;
        break;

    case OP_ADD:
        printf("perform add %d, %d, %d\n\n",
               instruction->dst, instruction->src0, instruction->src1);
        add_xform(state, instruction->dst, instruction->src0, instruction->src1);
        break;

    case OP_SUB:
        printf("perform add %d, %d, %d\n\n",
               instruction->dst, instruction->src0, instruction->src1);
        sub_xform(state, instruction->dst, instruction->src0, instruction->src1);
        break;

    case OP_MUL:
        printf("perform mul %d, %d, %d\n\n",
               instruction->dst, instruction->src0, instruction->src1);
        mul_xform(state, instruction->dst, instruction->src0, instruction->src1);
        break;
    
    /* 之後可以在這裡加入更多 opcode */
    default:
        fprintf(stderr, "Unsupported opcode: %d\n", instruction->op);
        /* 視需求決定要不要終止或忽略 */
        break;
    }
}

#include <stdbool.h>
#include <string.h> 
#include <stdlib.h>
#include "../types.h"
#include "api/gpr.h"
#include "api/flags.h"
#include "api/vreg/read.h"
#include "api/vreg/print.h"
#include "api/vreg/write.h"

void wipe(void *p, size_t n) {
    memset(p, 0, n);   /* 原型與 memset 完全相同 */
}

#define A64RF_MAGIC 27183

int a64rf_state_init(a64rf_state_t *s, size_t stack_sz, size_t mem_sz) {
    if (!s) return -1; 

    memset(s, 0, sizeof *s);

    stack_sz = stack_sz ? stack_sz : DEFAULT_STACK_SZ;
    mem_sz   = mem_sz   ? mem_sz   : DEFAULT_MEM_SZ;


    s->stack  = (uint8_t *)malloc(stack_sz);
    s->memory = (uint8_t *)malloc(mem_sz);
    if (!s->stack || !s->memory) {
        free(s->stack);
        free(s->memory);
        return -2;
    }


    s->stack_size = stack_sz;
    s->mem_size   = mem_sz;
    s->mem_cnt    = 0;

    memset(s->stack , 0, stack_sz);
    memset(s->memory, 0, mem_sz);

    for (size_t i = 0; i < GPR_COUNT; i++)
        write_zero_gpr(s, i);
    for (size_t i = 0; i < VREG_COUNT; i++)
        write_zero_vreg(s, i);

    write_zero_nzcv(s);
    write_zero_fpsr(s);

    s->pc.val = 0;
    
    s->magic = A64RF_MAGIC;

    
    return 0;
}


void a64rf_clean(a64rf_state_t *s)
{
    if (!s) return;
    /* 若 magic 不符，代表從未 init；直接略過 */
    if (s->magic != A64RF_MAGIC) return;

    free(s->stack);
    free(s->memory);

    /* 清零避免 UAF；magic 歸零可偵測重複 destroy */
    memset(s, 0, sizeof *s);
}

// a64rf_state_t eor_a64rf_state(a64rf_state_t *state1, a64rf_state_t *state2)
// {
//     // generate delta = state1 ^ state2

//     a64rf_state_t delta_state = {0};

//     for (size_t i = 0; i < GPR_COUNT; i++)
//     {
//         uint64_t val1 = read_val_gpr(state1, i);
//         uint64_t val2 = read_val_gpr(state2, i);
//         uint64_t val = val1 ^ val2;
//         write_val_gpr(&delta_state, i, val);
//     }
       
//     for (size_t i = 0; i < VREG_COUNT; i++)
//     {
//         uint64_t val1 = read_val_gpr(state1, i);
//         uint64_t val2 = read_val_gpr(state2, i);
//         uint64_t val = val1 ^ val2;
//         write_val_gpr(&delta_state, i, val);
//     }
       
// }

// bool a64rf_state_eor_zero(a64rf_state_t *state)
// {
//     // return true if state = zero state

// }


// bool equal_a64rf_state(a64rf_state_t *state1, a64rf_state_t *state2)
// {
//     // delta_state = state1 ^ state2
//     // return true if delta_state = 0

// }




#pragma once
#include <stdio.h>
#include <inttypes.h>
#include "types.h"


static inline print_gprs(a64rf_state_t *state);
// include sp


static inline print_gprs_and_nzcv(a64rf_state_t *state);


static inline print_vregs(a64rf_state_t *state);

static inline print_vregs_and_fpsr(a64rf_state_t *state);


static inline print_all_regs_and_flags(a64rf_state_t *state);



static inline print_stack(a64rf_state_t *state);

static inline print_memory(a64rf_state_t *state);


static inline print_stack_and_memory(a64rf_state_t *state);

static inline print_state(a64rf_state_t *state);

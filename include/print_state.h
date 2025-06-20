#ifndef PRINT_STATE_H
#define PRINT_STATE_H
#include <stdio.h>
#include <inttypes.h>
#include "types.h"


static inline void print_state(const char *tag, const a64rf_state_t *st)
{
    if (tag && *tag) printf("-- %s --\n", tag);
    for (int i=0; i<31; i++)
        printf("X%-2d = 0x%016" PRIx64 "\n", i, st->gpr[i].val);
    uint32_t f = st->nzcv.word >> 28;
    printf("NZCV  N=%d Z=%d C=%d V=%d (raw=0x%X)\n", !!(f&8), !!(f&4), !!(f&2), !!(f&1), f);
}


#endif /* PRINT_STATE_H */
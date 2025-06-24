#pragma once

#include "../../types.h"
#include <stdbool.h>

#define A64RF_MEM_BASE 0x1000ULL

static inline size_t guest2off(const a64rf_state_t *s, a64rf_addr_t gaddr)
{
    if (gaddr < A64RF_MEM_BASE)           return SIZE_MAX;
    size_t off = (size_t)(gaddr - A64RF_MEM_BASE);
    if (off >= s->mem_size)               return SIZE_MAX;
    return off;
}

enum mem_width { W8=1, W16=2, W32=4, W64=8 };

static inline int mem_rw(a64rf_state_t *s,
                         a64rf_addr_t    gaddr,
                         enum mem_width  w,
                         bool            is_write,
                         uint64_t       *val)        /* R:輸出 W:輸入 */
{

    size_t off = guest2off(s, gaddr);
    if (off == SIZE_MAX || off + w > s->mem_size)
        return -1;                         /* data abort */

    if (is_write)  memcpy(&s->memory[off], val, w);
    else           memcpy(val, &s->memory[off], w);
    return 0;
}

#define DECL_MEM_API(bits, width_enum)                                      \
int read_mem_##bits (a64rf_state_t *s, a64rf_addr_t a, uint##bits##_t *dst) \
{ uint64_t t=0; int r=mem_rw(s,a,width_enum,false,&t); *dst=(uint##bits##_t)t; return r; }\
int write_mem_##bits(a64rf_state_t *s, a64rf_addr_t a, uint##bits##_t src)  \
{ uint64_t t=src; return mem_rw(s,a,width_enum,true,&t); }

DECL_MEM_API(8 , W8 )
DECL_MEM_API(16, W16)
DECL_MEM_API(32, W32)
DECL_MEM_API(64, W64)


a64rf_addr_t alloc_mem(a64rf_state_t *s, size_t sz, size_t align)
{

    size_t p = (s->mem_cnt + (align - 1)) & ~(align - 1);
    if (p + sz > s->mem_size) return 0;    /* out of guest heap */
    s->mem_cnt = p + sz;
    return A64RF_MEM_BASE + p;             /* guest address */
}
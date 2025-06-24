#include "a64rf.h"
#include "a64rf/api/mem.h"
#include <assert.h>

int main(void)
{

uint64_t a[1] = {6};
uint64_t b[1] = {6};
uint64_t dest[2] = {0};



a64rf_state_t st;
a64rf_init(&st, 4<<10, 64<<10);          /* 4 KB stack、64 KB heap */

a64rf_addr_t a_ptr = alloc_mem(&st, 8, 8);
write_mem_64(&st, a_ptr, *a);
a64rf_addr_t b_ptr = alloc_mem(&st, 8, 8);
write_mem_64(&st, b_ptr, *b);
a64rf_addr_t dest_ptr = alloc_mem(&st, 8, 8);

write_val_gpr(&st, X0, dest_ptr);
write_val_gpr(&st, X1, a_ptr);
write_val_gpr(&st, X2, b_ptr);

ldr_xform(&st, X1, X1);
ldr_xform(&st, X2, X2);

mul_xform(&st, X1, X1, X2);

str_xform(&st, X1, X0);

read_mem_64(&st, dest_ptr, dest);
printf("dest = %llu", dest[0], dest[1]);



}

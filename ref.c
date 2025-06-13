/* driver.c --------------------------------------------------------- */
#include <stdio.h>
#include <stdint.h>
//#include "snap_macro.inc"            /* for SNAP_REGS 0 */
#include "a64rf_dump.h"              /* _a64rf_dump_regs decl */
#include "a64rf_state.h"             /* 只是示範；若不需要可省 */
#include "a64rf_op.h"

extern void foo(uint64_t *dst, const uint64_t *src);      /* asm.S */
extern void foo_ref(uint64_t *dst, const uint64_t *src);  /* ref.c */



/* ─── 主程式 ─────────────────────────────────────────────── */
int main(void)
{
    uint64_t src[2]     = { -11, 10 };
    uint64_t dst_ref[2] = { 0 };
    uint64_t dst_asm[2] = { 0 };

    foo(dst_asm, src);

    printf("dst_asm: [%lu, %lu]\n", dst_asm[0], dst_asm[1]);


}
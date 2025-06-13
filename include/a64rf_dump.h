#ifndef A64RF_DUMP_H
#define A64RF_DUMP_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/* side = 0 (Ref), 1 (Asm) */
void a64rf_dump_regs(const uint64_t *gpr_nzcv, int side);
#ifdef __cplusplus
}
#endif

#endif
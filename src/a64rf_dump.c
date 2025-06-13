#include <stdio.h>
#include <inttypes.h>
#include "a64rf_dump.h"

/* -------------------------------------------------------------
 *  公用列印工具：
 *      a64rf_dump_regs()       – 無序號版本（維持舊介面）
 *      a64rf_dump_regs_idx()   – 帶 snapshot 序號
 *
 *  旗標解析採用位移方式，正確對應 NZCV 的 [31:28] 四個 bit。
 * -----------------------------------------------------------*/

/* 解析 NZCV 四旗標 */
static inline void dump_nzcv(uint32_t nzcv)
{
    unsigned N = (nzcv >> 31) & 1;
    unsigned Z = (nzcv >> 30) & 1;
    unsigned C = (nzcv >> 29) & 1;
    unsigned V = (nzcv >> 28) & 1;

    printf("NZCV N=%u Z=%u C=%u V=%u (raw=0x%08X)\n", N, Z, C, V, nzcv);
}

/* 無序號版本（向後相容） */
void a64rf_dump_regs(const uint64_t *buf, int side)
{
    const char tag = side ? 'A' : 'R';
    printf("\n[S %c]\n", tag);

    for (int i = 0; i < 31; i++)
        printf("X%-2d = 0x%016" PRIx64 "\n", i, buf[i]);

    dump_nzcv((uint32_t)buf[31]);
}

/* 帶 snapshot 序號版本 */
void a64rf_dump_regs_idx(const uint64_t *buf, int side, unsigned idx)
{
    const char tag = side ? 'A' : 'R';
    printf("\n[S%u %c]\n", idx, tag);

    for (int i = 0; i < 31; i++)
        printf("X%-2d = 0x%016" PRIx64 "\n", i, buf[i]);

    dump_nzcv((uint32_t)buf[31]);
}
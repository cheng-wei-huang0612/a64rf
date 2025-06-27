#include <stdio.h>
#include <inttypes.h>
#include "a64rf_dump.h"
#include "a64rf/api/state.h"


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


/* 帶 snapshot 序號版本 */
void a64rf_dump_gprs_idx(const uint64_t *buf, int side, unsigned idx)
{
    const char tag = side ? 'A' : 'R';
    printf("\n[S%u %c]\n", idx, tag);
    for (int i = 0; i < 31; ++i)
        printf("X%-2d = 0x%016" PRIx64 "\n", i, buf[i]);
    dump_nzcv((uint32_t)buf[31]);
}

void a64rf_dump_regs_idx(const uint64_t *b,int s,unsigned i)
{ a64rf_dump_gprs_idx(b,s,i); }

/* lane_bits = 8 / 16 / 32 / 64 */
static void dump_lane(const uint8_t *p, int lane_bits)
{
    switch (lane_bits) {
    case 64: printf("0x%016" PRIx64, *(const uint64_t*)p); break;
    case 32: printf("0x%08"  PRIx32, *(const uint32_t*)p); break;
    case 16: printf("0x%04"  PRIx16, *(const uint16_t*)p); break;
    default: printf("%02"    PRIx8 ,  *p);                 break;
    }
}

/* 參數表：buf, side, idx, lane_bits */
void a64rf_dump_vregs_idx(const void *buf, int side,
                          unsigned idx, int lane_bits, int qc)
{
    const char tag = side ? 'A' : 'R';
    const uint8_t *base = buf;
    int step = lane_bits / 8;
    int lanes = 16 / step;

    printf("\n[V%u %c]  (%d-bit lanes, QC=%d)\n",
           idx, tag, lane_bits, qc);

    for (int v = 0; v < 32; ++v) {
        printf("V%-2d:", v);
        const uint8_t *vp = base + v*16;
        for (int l = 0; l < lanes; ++l) {
            putchar(' ');
            switch (lane_bits) {
            case 64: printf("0x%016" PRIx64, *(const uint64_t*)(vp+l*step)); break;
            case 32: printf("0x%08"  PRIx32, *(const uint32_t*)(vp+l*step)); break;
            case 16: printf("0x%04"  PRIx16, *(const uint16_t*)(vp+l*step)); break;
            default: printf("%02"    PRIx8 ,  *(const uint8_t *)(vp+l*step)); break;
            }
        }
        putchar('\n');
    }
}

#define SNAP_GPR_SZ   304
#define SNAP_VREG_SZ   512
void a64rf_dump_state_idx(const void *buf, int side,
                          unsigned idx, int lane_bits)
{
    const uint8_t *p = buf;
    a64rf_dump_gprs_idx( (const uint64_t*)p, side, idx );      /* GPR+NZCV */

    p += SNAP_GPR_SZ;
    /* QC 位於最後 4B—we先抓下來 */
    uint32_t fpsr = *(const uint32_t*)(p + SNAP_VREG_SZ);
    int qc = (fpsr >> 27) & 1;

    a64rf_dump_vregs_idx( p, side, idx, lane_bits, qc );       /* V + QC */

    printf("[FPSR] QC=%d  raw=0x%08" PRIx32 "\n\n", qc, fpsr);
}

/* 把 848B raw buffer 轉成 a64rf_state_t */
static void buf_to_state(const uint8_t *b, a64rf_state_t *s)
{
    /* (1) GPR  */
    const uint64_t *q = (const uint64_t*)b;
    for (int i = 0; i < 31; ++i)     s->gpr[i].val = q[i];
    s->nzcv.word = (uint32_t)q[31];

    

    /* (2) VREG */
    memcpy(s->vreg, b + SNAP_GPR_SZ, SNAP_VREG_SZ);

    /* (3) SYS */
    const uint8_t *sys = b + SNAP_GPR_SZ + SNAP_VREG_SZ;
    s->fpsr.word = *(const uint32_t*)sys;

    const uint64_t *ps = (const uint64_t*)(sys + 8);
    s->pc.val = (uint16_t)(ps[0] & 0xFFFF);   /* 若 pc.val 只有 16 bit */
    s->sp.val = (void*)ps[1];
}

/* ASM 呼叫用：x0=buf, w1=side, w2=idx, w3=lane_bits */
void a64rf_snapshot_dump(const void *buf,
                         int side, unsigned idx, int lane_bits)
{
    printf("print whole state\n\n");
    a64rf_state_t snap = {0};
    buf_to_state(buf, &snap);




    /* 你自己的列印函式：可依 lane_bits 決定 VREG 8/16/32/64  */
    print_all_regs_and_flags(&snap);
}
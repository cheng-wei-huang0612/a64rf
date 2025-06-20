#include <stdio.h>
#include <stdint.h>
#include <stdalign.h>   /* 新增：讓 alignas 可用 */
#include "ntt8_twiddle.h"

/* 彙編函式：x0 = in[64]、x1 = tw_pack[56] */
extern void three_layer_ntt(int16_t *in, const int16_t *tw_pack);

/* 把表格裡「單一 lane」的常數，打包成連續 7×8 = 56 個 int16_t */
static void pack_twiddle(int lane, int16_t out[56])
{
    const ntt8_constants_t *t = &ntt8_tbl[lane];
    int ofs = 0;

    #define COPY(arr)                           \
        for (int i = 0; i < 8; ++i)             \
            out[ofs++] = (arr)[i]

    COPY(t->root0);      COPY(t->root0_tw);
    COPY(t->root1);      COPY(t->root1_tw);
    COPY(t->root2);      COPY(t->root2_tw);
    for (int i = 0; i < 8; ++i)                 /* modulus 整條向量 */
        out[ofs++] = t->p;
    #undef COPY
}

int main(void)
{
    /* ---- 1. 準備輸入 ---- */
    alignas(16) int16_t in[64];   /* 修：把分號移到變數後面 */
    for (int i = 0; i < 64; ++i)
        in[i] = (i + 1) & 0x7FFF;   /* demo 數據 */

    /* ---- 2. 打包 lane-0 (p = 3329) 的常數 ---- */
    alignas(16) int16_t tw[56];  /* 同上修正 */
    pack_twiddle(0, tw);

    /* ---- 3. 呼叫三層 8-點 NTT ---- */
    three_layer_ntt(in, tw);

    /* ---- 4. 輸出結果 ---- */
    for (int lane = 0; lane < 8; ++lane) {
        printf("lane %d : ", lane);
        for (int j = 0; j < 8; ++j)
            printf("%5d ", in[lane * 8 + j]);
        putchar('\n');
    }
    return 0;
}
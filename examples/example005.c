#include "a64rf.h"   /* 你的 register-file & op 定義 */

void demo_128bit_add(void)
{
    a64rf_state_t s = {0};          /* 清空所有 GPR 與 NZCV */

    /* A  = 0x12345678_9ABCDEF0'01234567_89ABCDEF */
    s.gpr[X0].val = (1ULL<<63);   /* A_lo */
    s.gpr[X1].val = (1ULL<<63);   /* A_hi */

    /* B  = 0x0FEDCBA9_87654321'0FEDCBA9_87654321 */
    s.gpr[X2].val = (1ULL<<63);   /* B_lo */
    s.gpr[X3].val = (1ULL<<63);   /* B_hi (示意相同) */    
    /* --- 低字：X4 = A_lo + B_lo，並設定 NZCV --------------- */
    adds_xform(&s, X4, X0, X2);     /* ADDS X4, X0, X2 */

    /* --- 高字：X5 = A_hi + B_hi + C ------------------------- */
    adcs_xform(&s, X5, X1, X3);     /* ADCS X5, X1, X3 */

    /* optional：觀察 flags（此時的 C=最終進位） -------------- */
    printf("NZCV after 128-bit add: N=%u Z=%u C=%u V=%u\n",
           s.nzcv.N, s.nzcv.Z, s.nzcv.C, s.nzcv.V);

    /* --- 把低 64 bit 結果循環右轉 13 位 -------------------- */
    ror_xform_imm(&s, X6, X4, 13);  /* ROR X6, X4, #13 */

    /* --- 用 ANDS 檢查旋轉結果是否為零 ---------------------- */
    ands_xform(&s, XZR /*丟棄*/, X6, X6);    /* TST X6, X6 */
    if (s.nzcv.Z) puts("Rotate result is zero!");

    /* 結果：X5:X4 = A+B,  X6 = ROR13(X4) -------------------- */
}


int main(int argc, char const *argv[])
{
    demo_128bit_add();
    return 0;
}

/* demo.c ─ a64rf_op.h 測試程式 */
#include <stdio.h>
#include <inttypes.h>
#include "a64rf_state.h"
#include "a64rf_regs.h"
#include "a64rf_op.h"

/* 小工具：把 NZCV 四個 bit 印出來 */
static void print_nzcv(uint64_t nzcv)
{
    printf("N=%d Z=%d C=%d V=%d (raw=%#010" PRIx64 ")\n",
           (int)((nzcv >> 31) & 1),
           (int)((nzcv >> 30) & 1),
           (int)((nzcv >> 29) & 1),
           (int)((nzcv >> 28) & 1),
           nzcv & 0xF0000000u);
}

int main(void)
{
    a64rf_state_t st = {0};

    /* 1. 初始化暫存器與 flags ----------------------------------------- */
    st.gpr[X0].val = 5;          // lhs
    st.gpr[X1].val = 10;         // rhs
    st.nzcv        = 0;          // 清空旗標

    puts("=== MUL 範例：flags 維持不變 ===");
    print_nzcv(st.nzcv);

    mul_xform(&st, X2, X0, X1);  // X2 = 5 * 10
    printf("X2 = %" PRIu64 "\n", st.gpr[X2].val);
    print_nzcv(st.nzcv);         // 仍為 0

    /* 2. ADD：不更新 NZCV（使用 add 指令）---------------------------- */
    puts("\n=== ADD 範例：手動先設旗標 → ADD 不改 NZCV ===");
    /* 先故意把 C 旗標設 1（bit 29） */
    st.nzcv = 1u << 29;
    print_nzcv(st.nzcv);

    add_xform(&st, X3, X2, X1);  // X3 = 50 + 10 = 60
    printf("X3 = %" PRIu64 "\n", st.gpr[X3].val);
    print_nzcv(st.nzcv);         // 可看到 C 仍為 1、不會被 ADD 改動

    /* 3. ADDS：會更新 NZCV ------------------------------------------- */
    puts("\n=== ADDS 範例：同樣輸入 → 旗標自動更新 ===");
    /* 把旗標再清 0 看得更明顯 */
    st.nzcv = 0;
    print_nzcv(st.nzcv);
    st.gpr[X1].val = (uint64_t)1<<63;
    st.gpr[X2].val = ((uint64_t)1<<63) + 1;
    adds_xform(&st, X4, X2, X1); 
    printf("X4 = %" PRIu64 "\n", st.gpr[X4].val);
    print_nzcv(st.nzcv);         // Z 仍為 0，但 C 依結果決定，V 也會按溢位更新

    return 0;
}
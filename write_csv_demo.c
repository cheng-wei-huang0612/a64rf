/*
 * trace_p25519_color.c
 *
 * 產生 bignum_add_p25519.xlsx：
 *  ─ 橫軸：X0–X11
 *  ─ 縱軸：指令序列
 *  ─ 淺藍：只讀   (input)
 *  ─ 淺黃：只寫   (output)
 *  ─ 淺綠：讀＋寫 (in-place)
 *
 * 編譯：
 *   gcc trace_p25519_color.c -o trace \
 *       -lxlsxwriter -lz -lm
 *
 * 執行：
 *   ./trace      # 產生 bignum_add_p25519.xlsx
 */

#include <stdio.h>
#include <string.h>
#include <xlsxwriter.h>

/*───── 一行指令的描述─────*/
typedef struct {
    const char *asm_str;
    const char *in[6];   /* 最多 6 個輸入暫存器 */
    int         in_cnt;
    const char *out[4];  /* 最多 4 個輸出暫存器 */
    int         out_cnt;
} trace_t;

/*───── 指令序列 (X0–X11 即足夠) ─────*/
static const trace_t trace[] = {
 {"ldp x3, x4, [x1]"            , {"X1"},                1, {"X3","X4"},          2},
 {"ldp x5, x6, [x1,#16]"        , {"X1"},                1, {"X5","X6"},          2},
 {"ldp x7, x8, [x2]"            , {"X2"},                1, {"X7","X8"},          2},
 {"ldp x9, x10,[x2,#16]"        , {"X2"},                1, {"X9","X10"},         2},
 {"adds x3, x3, x7"             , {"X3","X7"},           2, {"X3"},               1},
 {"adcs x4, x4, x8"             , {"X4","X8"},           2, {"X4"},               1},
 {"adcs x5, x5, x9"             , {"X5","X9"},           2, {"X5"},               1},
 {"adc  x6, x6, x10"            , {"X6","X10"},          2, {"X6"},               1},
 {"mov  x11, #0"                , {NULL},                0, {"X11"},              1},
 {"movk x11,#0x8000, lsl #48"   , {"X11"},               1, {"X11"},              1},
 {"adds x7, x3, #19"            , {"X3"},                1, {"X7"},               1},
 {"adcs x8, x4, xzr"            , {"X4","XZR"},          2, {"X8"},               1},
 {"adcs x9, x5, xzr"            , {"X5","XZR"},          2, {"X9"},               1},
 {"adcs x10,x6, x11"            , {"X6","X11"},          2, {"X10"},              1},
 {"csel x3, x3, x7, cc"         , {"X3","X7"},           2, {"X3"},               1},
 {"csel x4, x4, x8, cc"         , {"X4","X8"},           2, {"X4"},               1},
 {"csel x5, x5, x9, cc"         , {"X5","X9"},           2, {"X5"},               1},
 {"csel x6, x6, x10, cc"        , {"X6","X10"},          2, {"X6"},               1},
 {"stp  x3, x4, [x0]"           , {"X0","X3","X4"},      3, {NULL},               0},
 {"stp  x5, x6, [x0,#16]"       , {"X0","X5","X6"},      3, {NULL},               0},
};
static const size_t TRACE_N = sizeof(trace)/sizeof(trace[0]);

/*───── 暫存器清單 (橫軸) ─────*/
static const char *regs[] = {
    "X0","X1","X2","X3","X4","X5","X6",
    "X7","X8","X9","X10","X11"
};
static const int REG_N = sizeof(regs)/sizeof(regs[0]);

/*───── 工具函式：判斷 in / out ─────*/
static int is_in_reg (const trace_t *t, const char *reg){
    for (int i=0;i<t->in_cnt;i++)
        if (t->in[i] && strcmp(t->in[i],reg)==0) return 1;
    return 0;
}
static int is_out_reg(const trace_t *t, const char *reg){
    for (int i=0;i<t->out_cnt;i++)
        if (t->out[i] && strcmp(t->out[i],reg)==0) return 1;
    return 0;
}

int main(void)
{
    /* 建立活頁簿與工作表 */
    lxw_workbook  *wb = workbook_new("bignum_add_p25519.xlsx");
    lxw_worksheet *ws = workbook_add_worksheet(wb, NULL);

    /* 定義三種顏色格式 */
    lxw_format *fmt_in      = workbook_add_format(wb);  /* 淺藍 */
    lxw_format *fmt_out     = workbook_add_format(wb);  /* 淺黃 */
    lxw_format *fmt_inplace = workbook_add_format(wb);  /* 淺綠 */
    format_set_bg_color(fmt_in,      0xCCE5FF);
    format_set_bg_color(fmt_out,     0xFFFF99);
    format_set_bg_color(fmt_inplace, 0xC6EFCE);

    /* ── 表頭 ── */
    worksheet_write_string(ws, 0, 0, "Instruction", NULL);
    for (int c = 0; c < REG_N; ++c)
        worksheet_write_string(ws, 0, c+1, regs[c], NULL);

    /* ── 逐列寫入指令 ── */
    int row = 1;
    for (size_t i = 0; i < TRACE_N; ++i, ++row) {
        const trace_t *t = &trace[i];
        worksheet_write_string(ws, row, 0, t->asm_str, NULL);

        for (int c = 0; c < REG_N; ++c) {
            const char *reg = regs[c];
            int col = c + 1;

            int in  = is_in_reg (t, reg);
            int out = is_out_reg(t, reg);

            if (in && out)
                worksheet_write_blank(ws, row, col, fmt_inplace);  /* 淺綠 */
            else if (out)
                worksheet_write_blank(ws, row, col, fmt_out);      /* 淺黃 */
            else if (in)
                worksheet_write_blank(ws, row, col, fmt_in);       /* 淺藍 */
            /* 其他保持空白 */
        }
    }

    /* 產生檔案 */
    int rc = workbook_close(wb);
    if (rc != LXW_NO_ERROR) {
        fprintf(stderr, "xlsxwriter error: %s\n", lxw_strerror(rc));
        return 1;
    }
    puts("✓ bignum_add_p25519.xlsx generated");
    return 0;
}

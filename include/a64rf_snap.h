#include <string.h>
#include <stdio.h>
#include "a64rf_state.h"
#include "print_state.h"

#define MAX_SNAP 512

/* 這裡產生全域資料 & 函式定義 */
static a64rf_state_t snap_ref[MAX_SNAP];
static unsigned      snap_idx = 0;

void a64rf_snap_shim(a64rf_state_t *st, int side)
{
    if (side == 0) {
        memcpy(&snap_ref[snap_idx], st, sizeof(*st));
        printf("\n[snap %u] ref stored\n", snap_idx);
    } else {
        printf("[snap %u] asm compare\n", snap_idx);
        if (memcmp(&snap_ref[snap_idx], st, sizeof(*st)) == 0) {
            puts("✓ match\n");
        } else {
            puts("❌ mismatch\n");
            print_state("ref", &snap_ref[snap_idx]);
            print_state("asm", st);
        }
        snap_idx++;
    }
}
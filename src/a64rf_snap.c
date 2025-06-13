#include <string.h>
#include <stdio.h>
#include "a64rf_state.h"
#include "print_state.h"

#define MAX_SNAP 512
static a64rf_state_t snap_ref[MAX_SNAP];
static unsigned idx = 0;

/*  side=0 → ref  /  side=1 → asm  */
void a64rf_snap_shim(a64rf_state_t *st, int side)
{
    if (side == 0) {
        if (idx >= MAX_SNAP) return;      /* cap */
        memcpy(&snap_ref[idx], st, sizeof(*st));
        printf("\n[snap %u] ref stored\n", idx);
    } else {
        printf("[snap %u] asm compare\n", idx);
        if (memcmp(&snap_ref[idx], st, sizeof(*st)) == 0) {
            puts("✓ match\n");
        } else {
            puts("❌ mismatch – detail below\n");
            print_state("ref", &snap_ref[idx]);
            print_state("asm", st);
        }
        idx++;
    }
}
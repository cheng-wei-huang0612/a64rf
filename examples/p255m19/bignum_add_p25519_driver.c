//#include "a64rf.h"
#include <stdint.h>
#include "stdio.h"
extern void bignum_add_p25519(uint64_t z[static 4], const uint64_t x[static 4], const uint64_t y[static 4]);
extern uint64_t x[4];
extern uint64_t y[4];

int main(void)
{
    uint64_t z[4];

    bignum_add_p25519(z, x, y);

    // for (int i = 0; i < 4; i++) {
    //     printf("z[%d] = %llu\n", i, (unsigned long long)z[i]);
    // }




    return 0;
}

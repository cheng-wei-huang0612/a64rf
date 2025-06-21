
#include "stdint.h"

extern void bignum_inv_p25519(uint64_t z[static 4],const uint64_t x[static 4]);


int main(int argc, char const *argv[])
{
    uint64_t x[4] = {0, 0, 0, 1};
    uint64_t z[4];

    bignum_inv_p25519(z, x);

    return 0;
}

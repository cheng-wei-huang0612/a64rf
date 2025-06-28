// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0 OR ISC OR MIT-0

// ----------------------------------------------------------------------------
// Add modulo p_25519, z := (x + y) mod p_25519, assuming x and y reduced
// Inputs x[4], y[4]; output z[4]
//
//    extern void bignum_add_p25519(uint64_t z[static 4], const uint64_t x[static 4],
//                                  const uint64_t y[static 4]);
//
// Standard ARM ABI: X0 = z, X1 = x, X2 = y
// ----------------------------------------------------------------------------
#include "_internal_s2n_bignum.h"

#include "snap_macro.inc"

        S2N_BN_SYM_VISIBILITY_DIRECTIVE(bignum_add_p25519)
        S2N_BN_SYM_PRIVACY_DIRECTIVE(bignum_add_p25519)

        .text
        .balign 4

#define z x0
#define x x1
#define y x2
#define d0 x3
#define d1 x4
#define d2 x5
#define d3 x6
#define c0 x7
#define c1 x8
#define c2 x9
#define c3 x10

S2N_BN_SYMBOL(bignum_add_p25519):

// Add as [d3; d2; d1; d0] = x + y; since we assume x, y < 2^255 - 19
// this sum fits in 256 bits

        ldp     d0, d1, [x]
        ldp     c0, c1, [y]
        adds    d0, d0, c0
        adcs    d1, d1, c1
        ldp     d2, d3, [x, #16]
        ldp     c0, c1, [y, #16]
        adcs    d2, d2, c0
        adc     d3, d3, c1



// Now x + y >= 2^255 - 19 <=> x + y + (2^255 + 19) >= 2^256
// Form [c3; c2; c1; c0] = (x + y) + (2^255 + 19), with CF for the comparison

        mov     c3, #0x8000000000000000
adds X7, X3, #19
adcs X8, X4, X31
adcs X9, X5, X31
adcs X10, X6, X10

// If the comparison holds, select [c3; c2; c1; c0]. There's no need to mask
// it since in this case it is ((x + y) + (2^255 + 19)) - 2^256 because the
// top carry is lost, which is the desired (x + y) - (2^255 - 19).

csel X3, X3, X7, cc
csel X4, X4, X8, cc
csel X5, X5, X9, cc
csel X6, X6, X10, cc
#ifdef A64RF_TRACE
        SNAP_STATE 0, 1               /* idx=0, side=1 (Asm) */
#endif

// Store the result

        stp     d0, d1, [z]
        stp     d2, d3, [z, #16]

        ret

#if defined(__linux__) && defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
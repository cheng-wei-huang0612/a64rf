.text
.global bignum_add_p25519
.global _bignum_add_p25519
bignum_add_p25519:
_bignum_add_p25519:
ldp X3, X4, [X1]
ldp X7, X8, [X2]
adds X3, X3, X7
adcs X4, X4, X8
ldp X5, X6, [X1, #16]
ldp X7, X8, [X2, #16]
adcs X5, X5, X7
adc X6, X6, X8
movz X10, #32768
adds X7, X3, #19
adcs X8, X4, X31
adcs X9, X5, X31
adcs X10, X6, X10
csel x3, x3, x7, cc
csel x4, x4, x8, cc
csel x5, x5, x9, cc
csel x6, x6, x10, cc
stp X3, X4, [X0]
stp X5, X6, [X0, #16]
ret

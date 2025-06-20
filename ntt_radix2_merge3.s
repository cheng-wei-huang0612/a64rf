///
/// Copyright (c) 2022 Arm Limited
/// Copyright (c) 2022 Hanno Becker
/// Copyright (c) 2023 Amin Abdulrahman, Matthias Kannwischer
/// SPDX-License-Identifier: MIT
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///

in      .req x0

data0   .req v16
data1   .req v17
data2   .req v18
data3   .req v19
data4   .req v20
data5   .req v21
data6   .req v22
data7   .req v23

tmp     .req v24

root0          .req v0
root0_twisted  .req v1
root1          .req v2
root1_twisted  .req v3
root2          .req v4
root2_twisted  .req v5

modulus        .req v6

.macro mulmod dst, src, const, const_twisted, idx
        mul        \dst\().8h, \src\().8h, \const\().h[\idx]
        sqrdmulh   \src\().8h, \src\().8h, \const_twisted\().h[\idx]
        mla        \dst\().8h, \src\().8h, modulus\().8h
.endm

.macro ct_butterfly a, b, root, root_twisted, idx
        mulmod tmp, \b, \root, \root_twisted, \idx
        sub    \b\().8h,    \a\().8h, tmp\().8h
        add    \a\().8h,    \a\().8h, tmp\().8h
.endm


.global _three_layer_ntt
.global three_layer_ntt

_three_layer_ntt:
three_layer_ntt:
        ld1 {data0.8h},  [in], #16
        ld1 {data1.8h},  [in], #16
        ld1 {data2.8h},  [in], #16
        ld1 {data3.8h},  [in], #16
        ld1 {data4.8h},  [in], #16
        ld1 {data5.8h},  [in], #16
        ld1 {data6.8h},  [in], #16
        ld1 {data7.8h},  [in], #16


        ct_butterfly data0,  data4,  root0, root0_twisted, 0
        ct_butterfly data1,  data5,  root0, root0_twisted, 0
        ct_butterfly data2,  data6,  root0, root0_twisted, 0
        ct_butterfly data3,  data7,  root0, root0_twisted, 0

        ct_butterfly data0,  data2,  root1, root1_twisted, 0
        ct_butterfly data1,  data3,  root1, root1_twisted, 0
        ct_butterfly data4,  data6,  root1, root1_twisted, 1
        ct_butterfly data5,  data7,  root1, root1_twisted, 1

        ct_butterfly data0,  data1,  root2, root2_twisted, 0
        ct_butterfly data2,  data3,  root2, root2_twisted, 1
        ct_butterfly data4,  data5,  root2, root2_twisted, 2
        ct_butterfly data6,  data7,  root2, root2_twisted, 3


        sub in, in, #128
        st1 {data0.8h},  [in], #16
        st1 {data1.8h},  [in], #16
        st1 {data2.8h},  [in], #16
        st1 {data3.8h},  [in], #16
        st1 {data4.8h},  [in], #16
        st1 {data5.8h},  [in], #16
        st1 {data6.8h},  [in], #16
        st1 {data7.8h},  [in], #16
ret 

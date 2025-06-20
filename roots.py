#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Make 8-point NTT twiddle-factor table (8 primes × 8-lane NEON layout)
"""

P = [3329, 7681, 12289, 15361, 18433, 10009, 10169, 10177]

# ---------- helpers ----------
def powmod(a, e, p):
    r = 1
    while e:
        if e & 1:
            r = (r * a) % p
        a = (a * a) % p
        e >>= 1
    return r

def prim_root_order(p, order=8):
    k = (p - 1) // order
    for g in range(2, p):
        ω = powmod(g, k, p)
        if all(powmod(ω, d, p) != 1 for d in range(1, order)):
            return ω
    raise ValueError("no primitive root")

def tw(c, p):                 # round(c · 2¹⁵ / p)
    return (c * (1 << 15) + (p // 2)) // p

def make_entry(p):
    ω = prim_root_order(p, 8)
    w1, w2, w3 = ω % p, powmod(ω, 2, p), powmod(ω, 3, p)

    root0      = [1] * 8
    root0_tw   = [tw(1, p)] * 8

    root1      = [1, w2] * 4
    root1_tw   = [tw(1, p), tw(w2, p)] * 4

    root2      = [1, w1, w2, w3] * 2
    root2_tw   = [tw(1, p), tw(w1, p), tw(w2, p), tw(w3, p)] * 2

    return dict(p=p,
                root0=root0,      root0_tw=root0_tw,
                root1=root1,      root1_tw=root1_tw,
                root2=root2,      root2_tw=root2_tw)

# ---------- emit ----------
entries = [make_entry(p) for p in P]

with open("ntt8_twiddle.h", "w") as f:
    f.write("// Auto-generated: 8-point NTT twiddle factors (8 primes)\n")
    f.write("#pragma once\n#include <stdint.h>\n\n")
    f.write("typedef struct {\n"
            "    uint16_t p;\n"
            "    int16_t  root0[8];\n"
            "    int16_t  root0_tw[8];\n"
            "    int16_t  root1[8];\n"
            "    int16_t  root1_tw[8];\n"
            "    int16_t  root2[8];\n"
            "    int16_t  root2_tw[8];\n"
            "} ntt8_constants_t;\n\n")

    f.write("static const ntt8_constants_t ntt8_tbl[8] = {\n")
    for e in entries:
        def fmt(arr): return "{" + ", ".join(f"{v}" for v in arr) + "}"
        f.write("  {\n")
        f.write(f"    {e['p']},\n")
        f.write(f"    {fmt(e['root0'])},\n")
        f.write(f"    {fmt(e['root0_tw'])},\n")
        f.write(f"    {fmt(e['root1'])},\n")
        f.write(f"    {fmt(e['root1_tw'])},\n")
        f.write(f"    {fmt(e['root2'])},\n")
        f.write(f"    {fmt(e['root2_tw'])}\n")
        f.write("  },\n")
    f.write("};\n")

print("✓  ntt8_twiddle.h  已生成")
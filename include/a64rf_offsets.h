#ifndef A64RF_OFFSETS_H
#define A64RF_OFFSETS_H

/* 結構對齊假設：
 *   struct a64rf_state_t {
 *       gpr_t gpr[31];             // 31 × 8 Bytes
 *       uint8x16_t v[32];          // 32 × 16 Bytes (SIMD Q registers)
 *       uint32_t   nzcv;           // 4 Bytes (aligned)
 *   };
 */

#define OFF_GPR(i)   (  (i) * 8 )                      /* gpr[i].val */
#define OFF_SIMD(i)  ( 8*31 + (i) * 16 )               /* q[i]       */
#define OFF_NZCV     ( 8*31 + 16*32 )                  /* flags      */

#endif /* A64RF_OFFSETS_H */
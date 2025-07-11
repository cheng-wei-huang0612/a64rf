#pragma once
#include "../../types.h"
#include <stddef.h>


static inline void add_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] + b[i]);
    }

    write_all_b_vreg(s, Vd, r);

}


static inline void add_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
    {
        r[i] = (uint16_t)(a[i] + b[i]);
    }

    write_all_h_vreg(s, Vd, r);
}



static inline void add_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] + b[i]);

    write_all_s_vreg(s, Vd, r);
}

static inline void add_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] + b[i]);

    write_all_d_vreg(s, Vd, r);
}

static inline void sub_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] - b[i]);
    }

    write_all_b_vreg(s, Vd, r);
}


static inline void sub_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
        r[i] = (uint16_t)(a[i] - b[i]);

    write_all_h_vreg(s, Vd, r);
}


static inline void sub_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] - b[i]);

    write_all_s_vreg(s, Vd, r);
}


static inline void sub_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] - b[i]);

    write_all_d_vreg(s, Vd, r);
}


static inline void mul_bform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);
    
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i)
    {
        r[i] = (uint8_t)(a[i] * b[i]);
    }

    write_all_b_vreg(s, Vd, r);
}


static inline void mul_hform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i)
        r[i] = (uint16_t)(a[i] * b[i]);

    write_all_h_vreg(s, Vd, r);
}


static inline void mul_sform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i)
        r[i] = (uint32_t)(a[i] * b[i]);

    write_all_s_vreg(s, Vd, r);
}


static inline void mul_dform(a64rf_state_t *s,
                             const a64rf_vreg_idx_t Vd,
                             const a64rf_vreg_idx_t Vn,
                             const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i)
        r[i] = (uint64_t)(a[i] * b[i]);

    write_all_d_vreg(s, Vd, r);
}

/*
compile to: smull Vd.8h, Vn.8b, Vm.8b
action: sign extend the first 8 b elements of Vn and Vm to h size, and
then multiply them
ref: a-profile: C7-3105
*/
static inline void smull_vd8h_vn8b_vm8b(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 8;
    //uint8_t operand1[64 / elements];
    uint8_t operand1[VREG_B_LANE_COUNT];
    uint8_t operand2[VREG_B_LANE_COUNT];
    uint16_t results[VREG_H_LANE_COUNT];


    read_all_b_vreg(s, Vn, operand1);
    read_all_b_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int8_t)operand1[e];
        int64_t element2 = (int64_t)(int8_t)operand2[e];
        int64_t result = element1 * element2;
        results[e] = (uint16_t)(int16_t) result;
    }

    write_all_h_vreg(s, Vd, results);    
}

// not assembler acceptable but intuitively acceptable
#define smull_vd8h_vn16b_vm16b smull_vd8h_vn8b_vm8b

/*
compile to: smull2 Vd.8h, Vn.16b, Vm.16b
action: sign extend the first 8 b elements of Vn and Vm to h size, and
then signed multiply them
ref: a-profile: C7-3105
*/
static inline void smull2_vd8h_vn16b_vm16b(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 8;
    //uint8_t operand1[64 / elements];
    uint8_t operand1[VREG_B_LANE_COUNT];
    uint8_t operand2[VREG_B_LANE_COUNT];
    uint16_t results[VREG_H_LANE_COUNT];


    read_all_b_vreg(s, Vn, operand1);
    read_all_b_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int8_t)operand1[e + 8];
        int64_t element2 = (int64_t)(int8_t)operand2[e + 8];
        int64_t result = element1 * element2;
        results[e] = (uint16_t)(int16_t) result;
    }

    write_all_h_vreg(s, Vd, results);    
}

/*
compile to: smull Vd.4s, Vn.4h, Vm.4h
action: sign extend the first 4 h elements of Vn and Vm to s size, and
then signed multiply them
ref: a-profile: C7-3105
*/
static inline void smull_vd4s_vn4h_vm4h(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 4;
    //uint8_t operand1[64 / elements];
    uint16_t operand1[VREG_H_LANE_COUNT];
    uint16_t operand2[VREG_H_LANE_COUNT];
    uint32_t results[VREG_S_LANE_COUNT];


    read_all_h_vreg(s, Vn, operand1);
    read_all_h_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int16_t)operand1[e];
        int64_t element2 = (int64_t)(int16_t)operand2[e];
        int64_t result = element1 * element2;
        results[e] = (uint32_t)(int32_t) result;
    }

    write_all_s_vreg(s, Vd, results);    
}

// not assembler acceptable but intuitively acceptable
#define smull_vd4s_vn8h_vm8h smull_vd4s_vn4h_vm4h

/*
compile to: smull2 Vd.4s, Vn.8h, Vm.8h
action: sign extend the first 4 h elements of Vn and Vm to s size, and
then signed multiply them
ref: a-profile: C7-3105
*/
static inline void smull2_vd4s_vn8h_vm8h(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 4;
    //uint8_t operand1[64 / elements];
    uint16_t operand1[VREG_H_LANE_COUNT];
    uint16_t operand2[VREG_H_LANE_COUNT];
    uint32_t results[VREG_S_LANE_COUNT];


    read_all_h_vreg(s, Vn, operand1);
    read_all_h_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int16_t)operand1[e + elements];
        int64_t element2 = (int64_t)(int16_t)operand2[e + elements];
        int64_t result = element1 * element2;
        results[e] = (uint32_t)(int32_t) result;
    }

    write_all_s_vreg(s, Vd, results);    
}

/*
compile to: smull Vd.2d, Vn.2s, Vm.2s
action: sign extend the first 2 s elements of Vn and Vm to d size, and
then signed multiply them
ref: a-profile: C7-3105
*/
static inline void smull_vd2d_vn2s_vm2s(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 2;
    //uint8_t operand1[64 / elements];
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];


    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e];
        int64_t element2 = (int64_t)(int32_t)operand2[e];
        int64_t result = element1 * element2;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);    
}

// not assembler acceptable but intuitively acceptable
#define smull_vd2d_vn4s_vm4s smull_vd2d_vn2s_vm2s

/*
compile to: smull2 Vd.4s, Vn.8h, Vm.8h
action: sign extend the first 4 h elements of Vn and Vm to s size, and
then signed multiply them
ref: a-profile: C7-3105
*/
static inline void smull2_vd2d_vn4s_vm4s(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm)
{
    uint8_t elements = 2;
    //uint8_t operand1[64 / elements];
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];


    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e + elements];
        int64_t element2 = (int64_t)(int32_t)operand2[e + elements];
        int64_t result = element1 * element2;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);
}

/*
compile to: smull Vd.2d, Vn.2s, Vm.s[index]
action: sign extend the first 2 s elements of Vn and Vm to d size, and
then signed multiply them
ref: a-profile: C7-3103
*/
static inline void smull_vd2d_vn2s_vms_lane(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm,
                                        const int lane)
{
    // check if lane is applicable


    uint8_t elements = 2;
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];
    
    
    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);

    int64_t element2 = (int64_t)(int32_t)operand2[lane];
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e];
        int64_t result = element1 * element2;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);    
}

/*
compile to: smull2 Vd.2d, Vn.4s, Vm.s[index]
action: sign extend the upper 2 s elements of Vn and Vm to d size, and
then signed multiply them
ref: a-profile: C7-3103
*/
static inline void smull2_vd2d_vn4s_vms_lane(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm,
                                        const int lane)
{
    // check if lane is applicable


    uint8_t elements = 2;
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];
    
    
    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);

    int64_t element2 = (int64_t)(int32_t)operand2[lane];
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e + elements];
        int64_t result = element1 * element2;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);    
}


/*
compile to: smlal Vd.2d, Vn.2s, Vm.s[index]
action: sign extend the first 2 s elements of Vn and Vm to d size, and
then signed multiply them accumulate to the 2 d elements of Vd
ref: a-profile: C7-3089
*/
static inline void smlal_vd2d_vn2s_vms_lane(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm,
                                        const int lane)
{
    // check if lane is applicable


    uint8_t elements = 2;
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t operand3[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];
    
    
    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);
    read_all_d_vreg(s, Vd, operand3);

    int64_t element2 = (int64_t)(int32_t)operand2[lane];
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e];
        int64_t element3 = (int64_t)(int64_t)operand3[e];
        int64_t product = element1 * element2;
        int64_t result = element3 + product;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);    
}

/*
compile to: smlal2 Vd.2d, Vn.4s, Vm.s[index]
action: sign extend the last 2 s elements of Vn and Vm to d size, and
then signed multiply them accumulate to the 2 d elements of Vd
ref: a-profile: C7-3089
*/
static inline void smlal2_vd2d_vn4s_vms_lane(a64rf_state_t *s,
                                        const a64rf_vreg_idx_t Vd,
                                        const a64rf_vreg_idx_t Vn,
                                        const a64rf_vreg_idx_t Vm,
                                        const int lane)
{
    // check if lane is applicable


    uint8_t elements = 2;
    uint32_t operand1[VREG_S_LANE_COUNT];
    uint32_t operand2[VREG_S_LANE_COUNT];
    uint64_t operand3[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];
    
    
    read_all_s_vreg(s, Vn, operand1);
    read_all_s_vreg(s, Vm, operand2);
    read_all_d_vreg(s, Vd, operand3);

    int64_t element2 = (int64_t)(int32_t)operand2[lane];
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)(int32_t)operand1[e + elements];
        int64_t element3 = (int64_t)(int64_t)operand3[e];
        int64_t product = element1 * element2;
        int64_t result = element3 + product;
        results[e] = (uint64_t)(int64_t) result;
    }

    write_all_d_vreg(s, Vd, results);    
}



/*
compile to: sshr Vd.2d, Vn.2d, #imm
action: 
ref: a-profile: C7-
*/
static inline void sshr_vd2d_vn2d_imm(a64rf_state_t *s,
                                      const a64rf_vreg_idx_t Vd,
                                      const a64rf_vreg_idx_t Vn,
                                      const uint32_t imm)
{
    // check if imm is applicable

    uint8_t elements = 2;
    uint64_t operand1[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, operand1);
    
    for (size_t e = 0; e < elements; e++)
    {
        int64_t element1 = (int64_t)operand1[e];
        element1 = element1 >> imm;
        results[e] = (uint64_t)element1;
    }
    write_all_d_vreg(s, Vd, results);    
}


static inline void and_vd16b_vn16b_vm16b(a64rf_state_t *s,
                                      const a64rf_vreg_idx_t Vd,
                                      const a64rf_vreg_idx_t Vn,
                                      const a64rf_vreg_idx_t Vm)
{
    uint64_t operand1[VREG_D_LANE_COUNT];
    uint64_t operand2[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, operand1);
    read_all_d_vreg(s, Vm, operand2);

    for (size_t e = 0; e < VREG_D_LANE_COUNT; e++)
    {
        uint64_t element1 = operand1[e];
        uint64_t element2 = operand2[e];
        uint64_t result = element1 & element2;
        results[e] = result;
    }
    write_all_d_vreg(s, Vd, results);    
}

// we should, somehow, notice the user that, such syntax is not acceptable
// for certain assembler.
#define and_vd8h_vn8h_vm8h and_vd16b_vn16b_vm16b
#define and_vd4s_vn4s_vm4s and_vd16b_vn16b_vm16b
#define and_vd2d_vn2d_vm2d and_vd16b_vn16b_vm16b

static inline void orr_vd16b_vn16b_vm16b(a64rf_state_t *s,
                                      const a64rf_vreg_idx_t Vd,
                                      const a64rf_vreg_idx_t Vn,
                                      const a64rf_vreg_idx_t Vm)
{
    uint64_t operand1[VREG_D_LANE_COUNT];
    uint64_t operand2[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, operand1);
    read_all_d_vreg(s, Vm, operand2);

    for (size_t e = 0; e < VREG_D_LANE_COUNT; e++)
    {
        uint64_t element1 = operand1[e];
        uint64_t element2 = operand2[e];
        uint64_t result = element1 | element2;
        results[e] = result;
    }
    write_all_d_vreg(s, Vd, results);    
}

// we should, somehow, notice the user that, such syntax is not acceptable
// for certain assembler.
#define orr_vd8h_vn8h_vm8h orr_vd16b_vn16b_vm16b
#define orr_vd4s_vn4s_vm4s orr_vd16b_vn16b_vm16b
#define orr_vd2d_vn2d_vm2d orr_vd16b_vn16b_vm16b



static inline void shl_vd2d_vd2n_imm(a64rf_state_t *s,
                                      const a64rf_vreg_idx_t Vd,
                                      const a64rf_vreg_idx_t Vn,
                                      const uint32_t imm)
{
    // check if imm is applicable

    uint8_t elements = 2;
    uint64_t operand1[VREG_D_LANE_COUNT];
    uint64_t results[VREG_D_LANE_COUNT];

    read_all_d_vreg(s, Vn, operand1);
    
    for (size_t e = 0; e < elements; e++)
    {
        uint64_t element1 = (uint64_t)operand1[e];
        element1 = element1 << imm;
        results[e] = (uint64_t)element1;
    }
    write_all_d_vreg(s, Vd, results);       
}                                      


/**********************************************************************
 * Scalar Saturation Helpers (grouped by OPERATION → width)
 *--------------------------------------------------------------------
 * For each arithmetic category we list all supported widths together,
 * making it easy to locate “all signed‑add helpers” in one chunk, etc.
 * Every helper sets `*sat = 1` if the result saturated, so the caller
 * can later update FPSR.QC.  No other side‑effects occur.
 *********************************************************************/

/*======================  Signed ADD  (SQADD)  ======================*/
static inline int8_t  sat_add_s8 (int8_t  a, int8_t  b, int *sat)
{
    int16_t tmp = (int16_t)a + (int16_t)b;
    if (tmp > INT8_MAX)  { *sat = 1; return  INT8_MAX; }
    if (tmp < INT8_MIN)  { *sat = 1; return  INT8_MIN; }
    return (int8_t)tmp;
}

static inline int16_t sat_add_s16(int16_t a, int16_t b, int *sat)
{
    int32_t tmp = (int32_t)a + (int32_t)b;
    if (tmp > INT16_MAX) { *sat = 1; return INT16_MAX; }
    if (tmp < INT16_MIN) { *sat = 1; return INT16_MIN; }
    return (int16_t)tmp;
}

static inline int32_t sat_add_s32(int32_t a, int32_t b, int *sat)
{
    int64_t tmp = (int64_t)a + (int64_t)b;
    if (tmp > INT32_MAX) { *sat = 1; return INT32_MAX; }
    if (tmp < INT32_MIN) { *sat = 1; return INT32_MIN; }
    return (int32_t)tmp;
}

static inline int64_t sat_add_s64(int64_t a, int64_t b, int *sat)
{
    if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) {
        *sat = 1;
        return (b > 0) ? INT64_MAX : INT64_MIN;
    }
    return a + b;
}

/*=====================  Unsigned ADD  (UQADD)  =====================*/
static inline uint8_t  sat_add_u8 (uint8_t  a, uint8_t  b, int *sat)
{
    uint16_t tmp = (uint16_t)a + (uint16_t)b;
    if (tmp > UINT8_MAX)  { *sat = 1; return UINT8_MAX; }
    return (uint8_t)tmp;
}

static inline uint16_t sat_add_u16(uint16_t a, uint16_t b, int *sat)
{
    uint32_t tmp = (uint32_t)a + (uint32_t)b;
    if (tmp > UINT16_MAX) { *sat = 1; return UINT16_MAX; }
    return (uint16_t)tmp;
}

static inline uint32_t sat_add_u32(uint32_t a, uint32_t b, int *sat)
{
    uint64_t tmp = (uint64_t)a + (uint64_t)b;
    if (tmp > UINT32_MAX) { *sat = 1; return UINT32_MAX; }
    return (uint32_t)tmp;
}

static inline uint64_t sat_add_u64(uint64_t a, uint64_t b, int *sat)
{
    uint64_t res = a + b;
    if (res < a) { *sat = 1; return UINT64_MAX; }
    return res;
}

/*==========  Signed + Unsigned ADD  (SUQADD)  =====================*/
static inline int8_t  suq_add_s8 (int8_t  a, uint8_t  b, int *sat)
{
    int16_t tmp = (int16_t)a + (int16_t)b;
    if (tmp > INT8_MAX)  { *sat = 1; return  INT8_MAX; }
    if (tmp < INT8_MIN)  { *sat = 1; return  INT8_MIN; }
    return (int8_t)tmp;
}

static inline int16_t suq_add_s16(int16_t a, uint16_t b, int *sat)
{
    int32_t tmp = (int32_t)a + (int32_t)b;
    if (tmp > INT16_MAX) { *sat = 1; return INT16_MAX; }
    if (tmp < INT16_MIN) { *sat = 1; return INT16_MIN; }
    return (int16_t)tmp;
}

static inline int32_t suq_add_s32(int32_t a, uint32_t b, int *sat)
{
    int64_t tmp = (int64_t)a + (int64_t)b;
    if (tmp > INT32_MAX) { *sat = 1; return INT32_MAX; }
    if (tmp < INT32_MIN) { *sat = 1; return INT32_MIN; }
    return (int32_t)tmp;
}

static inline int64_t suq_add_s64(int64_t a, uint64_t b, int *sat)
{
    if (b && a > INT64_MAX - (int64_t)b) { *sat = 1; return INT64_MAX; }
    return a + (int64_t)b;
}

/*======================  Signed SUB  (SQSUB)  =====================*/
static inline int8_t  sat_sub_s8 (int8_t  a, int8_t  b, int *sat)
{ return sat_add_s8 (a, (int8_t)(-b), sat); }

static inline int16_t sat_sub_s16(int16_t a, int16_t b, int *sat)
{ return sat_add_s16(a, (int16_t)(-b), sat); }

static inline int32_t sat_sub_s32(int32_t a, int32_t b, int *sat)
{ return sat_add_s32(a, (int32_t)(-b), sat); }

static inline int64_t sat_sub_s64(int64_t a, int64_t b, int *sat)
{ return sat_add_s64(a, -b, sat); }

/*=====================  Unsigned SUB  (UQSUB)  ====================*/
static inline uint8_t  sat_sub_u8 (uint8_t  a, uint8_t  b, int *sat)
{
    if (a < b) { *sat = 1; return 0; }
    return (uint8_t)(a - b);
}

static inline uint16_t sat_sub_u16(uint16_t a, uint16_t b, int *sat)
{
    if (a < b) { *sat = 1; return 0; }
    return (uint16_t)(a - b);
}

static inline uint32_t sat_sub_u32(uint32_t a, uint32_t b, int *sat)
{
    if (a < b) { *sat = 1; return 0; }
    return (uint32_t)(a - b);
}


static inline uint64_t sat_sub_u64(uint64_t a, uint64_t b, int *sat)
{
    if (a < b) { *sat = 1; return 0; }
    return a - b;
}


/*====================  Signed QSHL  (SQSHL)  =====================*/
static inline int8_t  sat_shl_s8 (int8_t a, int8_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 7) { *sat = 1; return (a < 0) ? INT8_MIN : INT8_MAX; }
        int16_t tmp = (int16_t)a << sh;
        if (tmp > INT8_MAX) { *sat = 1; return INT8_MAX; }
        if (tmp < INT8_MIN) { *sat = 1; return INT8_MIN; }
        return (int8_t)tmp;
    }
    return (int8_t)(a >> (-sh));
}

static inline int16_t sat_shl_s16(int16_t a, int16_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 15) { *sat = 1; return (a < 0) ? INT16_MIN : INT16_MAX; }
        int32_t tmp = (int32_t)a << sh;
        if (tmp > INT16_MAX) { *sat = 1; return INT16_MAX; }
        if (tmp < INT16_MIN) { *sat = 1; return INT16_MIN; }
        return (int16_t)tmp;
    }
    return (int16_t)(a >> (-sh));
}

static inline int32_t sat_shl_s32(int32_t a, int32_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 31) { *sat = 1; return (a < 0) ? INT32_MIN : INT32_MAX; }
        int64_t tmp = (int64_t)a << sh;
        if (tmp > INT32_MAX) { *sat = 1; return INT32_MAX; }
        if (tmp < INT32_MIN) { *sat = 1; return INT32_MIN; }
        return (int32_t)tmp;
    }
    return a >> (-sh);
}

static inline int64_t sat_shl_s64(int64_t a, int64_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 63) { *sat = 1; return (a < 0) ? INT64_MIN : INT64_MAX; }
        if ((sh > 0) && ((a >  (INT64_MAX >> sh)) || (a < (INT64_MIN >> sh)))) {
            *sat = 1;
            return (a < 0) ? INT64_MIN : INT64_MAX;
        }
        return a << sh;
    }
    return a >> (-sh);
}

/*===================  Unsigned QSHL  (UQSHL)  ====================*/
static inline uint8_t  sat_shl_u8 (uint8_t a, int8_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 8) { *sat = 1; return UINT8_MAX; }
        uint16_t tmp = (uint16_t)a << sh;
        if (tmp > UINT8_MAX) { *sat = 1; return UINT8_MAX; }
        return (uint8_t)tmp;
    }
    return a >> (-sh);
}

static inline uint16_t sat_shl_u16(uint16_t a, int16_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 16) { *sat = 1; return UINT16_MAX; }
        uint32_t tmp = (uint32_t)a << sh;
        if (tmp > UINT16_MAX) { *sat = 1; return UINT16_MAX; }
        return (uint16_t)tmp;
    }
    return a >> (-sh);
}

static inline uint32_t sat_shl_u32(uint32_t a, int32_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 32) { *sat = 1; return UINT32_MAX; }
        uint64_t tmp = (uint64_t)a << sh;
        if (tmp > UINT32_MAX) { *sat = 1; return UINT32_MAX; }
        return (uint32_t)tmp;
    }
    return a >> (-sh);
}

static inline uint64_t sat_shl_u64(uint64_t a, int64_t sh, int *sat) {
    if (sh >= 0) {
        if (sh >= 64) { *sat = 1; return UINT64_MAX; }
        if ((sh > 0) && (a > (UINT64_MAX >> sh))) { *sat = 1; return UINT64_MAX; }
        return a << sh;
    }
    return a >> (-sh);
}


/*--------------------------------------------------------------------
 *  Vector Saturating Arithmetic
 *  ─  SQADD · UQADD · SUQADD · SQSUB · UQSUB
 *  Each helper below:
 *      1. Loads lane‑wise operands from Vn/Vm
 *      2. Performs saturating arithmetic via the scalar helpers
 *      3. Writes the result to Vd
 *      4. If *any* lane saturated → sets FPSR.QC (state‑local `s->qc`)
 *  Coding style mirrors the earlier add/sub/mul helpers.
 *------------------------------------------------------------------*/

/*===========================  SQADD  ============================*/
static inline void sqadd_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];
    int     qc = 0;

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint8_t)sat_add_s8((int8_t)a[i], (int8_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_b_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqadd_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];
    int      qc = 0;

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint16_t)sat_add_s16((int16_t)a[i], (int16_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_h_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqadd_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];
    int      qc = 0;

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint32_t)sat_add_s32((int32_t)a[i], (int32_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_s_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqadd_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];
    int      qc = 0;

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint64_t)sat_add_s64((int64_t)a[i], (int64_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_d_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

/*===========================  UQADD  ============================*/
static inline void uqadd_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];
    int     qc = 0;

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_add_u8(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_b_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqadd_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];
    int      qc = 0;

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_add_u16(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_h_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqadd_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];
    int      qc = 0;

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_add_u32(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_s_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqadd_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];
    int      qc = 0;

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_add_u64(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_d_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

/*==========================  SUQADD  ===========================*/
static inline void suqadd_bform(a64rf_state_t *s,
                                const a64rf_vreg_idx_t Vd,
                                const a64rf_vreg_idx_t Vn,
                                const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];
    int     qc = 0;

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint8_t)suq_add_s8((int8_t)a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_b_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void suqadd_hform(a64rf_state_t *s,
                                const a64rf_vreg_idx_t Vd,
                                const a64rf_vreg_idx_t Vn,
                                const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];
    int      qc = 0;

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint16_t)suq_add_s16((int16_t)a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_h_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void suqadd_sform(a64rf_state_t *s,
                                const a64rf_vreg_idx_t Vd,
                                const a64rf_vreg_idx_t Vn,
                                const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];
    int      qc = 0;

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint32_t)suq_add_s32((int32_t)a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_s_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void suqadd_dform(a64rf_state_t *s,
                                const a64rf_vreg_idx_t Vd,
                                const a64rf_vreg_idx_t Vn,
                                const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];
    int      qc = 0;

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint64_t)suq_add_s64((int64_t)a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_d_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

/*===========================  SQSUB  ============================*/
static inline void sqsub_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];
    int     qc = 0;

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint8_t)sat_sub_s8((int8_t)a[i], (int8_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_b_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqsub_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];
    int      qc = 0;

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint16_t)sat_sub_s16((int16_t)a[i], (int16_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_h_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}


static inline void sqsub_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];
    int      qc = 0;

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint32_t)sat_sub_s32((int32_t)a[i], (int32_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_s_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}


static inline void sqsub_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];
    int      qc = 0;

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = (uint64_t)sat_sub_s64((int64_t)a[i], (int64_t)b[i], &sat);
        qc  |= sat;
    }

    write_all_d_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}


/*===========================  UQSUB  ============================*/
static inline void uqsub_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t a[VREG_B_LANE_COUNT];
    uint8_t b[VREG_B_LANE_COUNT];
    uint8_t r[VREG_B_LANE_COUNT];
    int     qc = 0;

    read_all_b_vreg(s, Vn, a);
    read_all_b_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_sub_u8(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_b_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqsub_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t a[VREG_H_LANE_COUNT];
    uint16_t b[VREG_H_LANE_COUNT];
    uint16_t r[VREG_H_LANE_COUNT];
    int      qc = 0;

    read_all_h_vreg(s, Vn, a);
    read_all_h_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_sub_u16(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_h_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqsub_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t a[VREG_S_LANE_COUNT];
    uint32_t b[VREG_S_LANE_COUNT];
    uint32_t r[VREG_S_LANE_COUNT];
    int      qc = 0;

    read_all_s_vreg(s, Vn, a);
    read_all_s_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_sub_u32(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_s_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqsub_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t a[VREG_D_LANE_COUNT];
    uint64_t b[VREG_D_LANE_COUNT];
    uint64_t r[VREG_D_LANE_COUNT];
    int      qc = 0;

    read_all_d_vreg(s, Vn, a);
    read_all_d_vreg(s, Vm, b);

    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        r[i] = sat_sub_u64(a[i], b[i], &sat);
        qc  |= sat;
    }

    write_all_d_vreg(s, Vd, r);
    if (qc) s->fpsr.QC = 1;
}


/*===========================  SQSHL  ============================*/
static inline void sqshl_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t val[VREG_B_LANE_COUNT], sh[VREG_B_LANE_COUNT], res[VREG_B_LANE_COUNT];
    int qc = 0;
    read_all_b_vreg(s, Vn, val);
    read_all_b_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = (uint8_t)sat_shl_s8((int8_t)val[i], (int8_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_b_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqshl_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t val[VREG_H_LANE_COUNT], sh[VREG_H_LANE_COUNT], res[VREG_H_LANE_COUNT];
    int qc = 0;
    read_all_h_vreg(s, Vn, val);
    read_all_h_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = (uint16_t)sat_shl_s16((int16_t)val[i], (int16_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_h_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqshl_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t val[VREG_S_LANE_COUNT], sh[VREG_S_LANE_COUNT], res[VREG_S_LANE_COUNT];
    int qc = 0;
    read_all_s_vreg(s, Vn, val);
    read_all_s_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = (uint32_t)sat_shl_s32((int32_t)val[i], (int32_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_s_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void sqshl_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t val[VREG_D_LANE_COUNT], sh[VREG_D_LANE_COUNT], res[VREG_D_LANE_COUNT];
    int qc = 0;
    read_all_d_vreg(s, Vn, val);
    read_all_d_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = sat_shl_s64((int64_t)val[i], (int64_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_d_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

/*===========================  UQSHL  ============================*/
static inline void uqshl_bform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint8_t val[VREG_B_LANE_COUNT], sh[VREG_B_LANE_COUNT], res[VREG_B_LANE_COUNT];
    int qc = 0;
    read_all_b_vreg(s, Vn, val);
    read_all_b_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_B_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = sat_shl_u8(val[i], (int8_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_b_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqshl_hform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint16_t val[VREG_H_LANE_COUNT], sh[VREG_H_LANE_COUNT], res[VREG_H_LANE_COUNT];
    int qc = 0;
    read_all_h_vreg(s, Vn, val);
    read_all_h_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_H_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = sat_shl_u16(val[i], (int16_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_h_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqshl_sform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint32_t val[VREG_S_LANE_COUNT], sh[VREG_S_LANE_COUNT], res[VREG_S_LANE_COUNT];
    int qc = 0;
    read_all_s_vreg(s, Vn, val);
    read_all_s_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_S_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = sat_shl_u32(val[i], (int32_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_s_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}

static inline void uqshl_dform(a64rf_state_t *s,
                               const a64rf_vreg_idx_t Vd,
                               const a64rf_vreg_idx_t Vn,
                               const a64rf_vreg_idx_t Vm)
{
    uint64_t val[VREG_D_LANE_COUNT], sh[VREG_D_LANE_COUNT], res[VREG_D_LANE_COUNT];
    int qc = 0;
    read_all_d_vreg(s, Vn, val);
    read_all_d_vreg(s, Vm, sh);
    for (size_t i = 0; i < VREG_D_LANE_COUNT; ++i) {
        int sat = 0;
        res[i] = sat_shl_u64(val[i], (int64_t)sh[i], &sat);
        qc |= sat;
    }
    write_all_d_vreg(s, Vd, res);
    if (qc) s->fpsr.QC = 1;
}
#include "a64rf.h"
#include <stdint.h>
#include <assert.h>

#define VEC_F0_F1_G0_G1 V0
#define VEC_F2_F3_G2_G3 V1
#define VEC_F4_F5_G4_G5 V2
#define VEC_F6_F7_G6_G7 V3
#define VEC_F8_F9_G8_G9 V4

#define VEC_UU0_RR0_VV0_SS0 V5
#define VEC_UU1_RR1_VV1_SS1 V6

#define VEC_PROD V7
#define VEC_BUFFER V8

#define VEC_CONST_2X_2P30M1 V9
#define VEC_CONST_2X_2P32M1 V10

int main(void)
{
    a64rf_state_t st;
    a64rf_state_init(&st, 0, 0);

    
    uint32_t temp1[4] = {0x3ffffe25, 0x3fffffff, 0x1f356453, 0x1da563cb};
    uint32_t temp2[4] = {0x3fffffff, 0x3fffffff, 0x3839823a, 0x175ad1c8};
    uint32_t temp3[4] = {0x3fffffff, 0x3fffffff, 0x12e4d632, 0x3c8b76b6};
    uint32_t temp4[4] = {0x3fffffff, 0x3fffffff, 0x03c8e7df, 0x15847e03};
    uint32_t temp5[4] = {0x00007fff, 0x00000000, 0x00005bd6, 0x00000000};

    uint32_t temp6[4] = {0x2eb22888, 0x1b062d3e, 0x0b1f6f48, 0x1abd048e};
    uint32_t temp7[4] = {0xfffffffd, 0xffffffff, 0x00000001, 0xffffffff};


    uint32_t temp1_correct[4] = {0x257626eb, 0x33b7ba7a, 0x0d7e7f72, 0x2f936572};
    uint32_t temp2_correct[4] = {0x3ab3d280, 0x07e9bfe4, 0x3798a509, 0x18949ee6};
    uint32_t temp3_correct[4] = {0x1d1d13a9, 0x27b50977, 0x2f731b5f, 0x1578d58e};
    uint32_t temp4_correct[4] = {0x265b7372, 0x3fff4930, 0x14b82aae, 0x3fff8094};
    uint32_t temp5_correct[4] = {0xffffffff, 0x00000000, 0xffffffff, 0x00000000};

    write_all_s_vreg(&st, VEC_F0_F1_G0_G1, temp1);
    write_all_s_vreg(&st, VEC_F2_F3_G2_G3, temp2);
    write_all_s_vreg(&st, VEC_F4_F5_G4_G5, temp3);
    write_all_s_vreg(&st, VEC_F6_F7_G6_G7, temp4);
    write_all_s_vreg(&st, VEC_F8_F9_G8_G9, temp5);

    write_all_s_vreg(&st, VEC_UU0_RR0_VV0_SS0, temp6);
    write_all_s_vreg(&st, VEC_UU1_RR1_VV1_SS1, temp7);


    // constants
    uint32_t CONST_2X_2P30M1[4] = {1073741823, 0, 1073741823, 0};
    uint32_t CONST_2X_2P32M1[4] = {4294967295, 0, 4294967295, 0};
    write_all_s_vreg(&st, VEC_CONST_2X_2P30M1, CONST_2X_2P30M1);
    write_all_s_vreg(&st, VEC_CONST_2X_2P32M1, CONST_2X_2P32M1);


    // limb 0
    smull_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F0_F1_G0_G1, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F0_F1_G0_G1, 2);

    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);

    // limb 1
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F0_F1_G0_G1, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F0_F1_G0_G1, 3);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F0_F1_G0_G1, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F0_F1_G0_G1, 2);
    
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);

    // limb 2
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F2_F3_G2_G3, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F2_F3_G2_G3, 2);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F0_F1_G0_G1, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F0_F1_G0_G1, 3);
    
    and_vd2d_vn2d_vm2d(&st, VEC_F0_F1_G0_G1, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);
    
    
    
    // limb 3
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F2_F3_G2_G3, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F2_F3_G2_G3, 3);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F2_F3_G2_G3, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F2_F3_G2_G3, 2);
    
    and_vd16b_vn16b_vm16b(&st, VEC_BUFFER, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);
    shl_vd2d_vd2n_imm(&st, VEC_BUFFER, VEC_BUFFER, 32);
    orr_vd16b_vn16b_vm16b(&st, VEC_F0_F1_G0_G1, VEC_F0_F1_G0_G1, VEC_BUFFER);
    
    
    // limb 4
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F4_F5_G4_G5, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F4_F5_G4_G5, 2);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F2_F3_G2_G3, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F2_F3_G2_G3, 3);
    
    and_vd16b_vn16b_vm16b(&st, VEC_F2_F3_G2_G3, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);


    // limb 5
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F4_F5_G4_G5, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F4_F5_G4_G5, 3);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F4_F5_G4_G5, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F4_F5_G4_G5, 2);

    and_vd16b_vn16b_vm16b(&st, VEC_BUFFER, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);
    shl_vd2d_vd2n_imm(&st, VEC_BUFFER, VEC_BUFFER, 32);
    orr_vd16b_vn16b_vm16b(&st, VEC_F2_F3_G2_G3, VEC_F2_F3_G2_G3, VEC_BUFFER);

    // limb 6
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F6_F7_G6_G7, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F6_F7_G6_G7, 2);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F4_F5_G4_G5, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F4_F5_G4_G5, 3);

    and_vd16b_vn16b_vm16b(&st, VEC_F4_F5_G4_G5, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);


    // limb 7
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F6_F7_G6_G7, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F6_F7_G6_G7, 3);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F6_F7_G6_G7, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F6_F7_G6_G7, 2);

    and_vd16b_vn16b_vm16b(&st, VEC_BUFFER, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);
    shl_vd2d_vd2n_imm(&st, VEC_BUFFER, VEC_BUFFER, 32);
    orr_vd16b_vn16b_vm16b(&st, VEC_F4_F5_G4_G5, VEC_F4_F5_G4_G5, VEC_BUFFER);

    // limb 8
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F8_F9_G8_G9, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU0_RR0_VV0_SS0, VEC_F8_F9_G8_G9, 2);
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F6_F7_G6_G7, 1);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F6_F7_G6_G7, 3);

    and_vd16b_vn16b_vm16b(&st, VEC_F6_F7_G6_G7, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);


    // limb 9
    smlal_vd2d_vn2s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F8_F9_G8_G9, 0);
    smlal2_vd2d_vn4s_vms_lane(&st, VEC_PROD, VEC_UU1_RR1_VV1_SS1, VEC_F8_F9_G8_G9, 2);
    and_vd16b_vn16b_vm16b(&st, VEC_BUFFER, VEC_PROD, VEC_CONST_2X_2P30M1);
    sshr_vd2d_vn2d_imm(&st, VEC_PROD, VEC_PROD, 30);
    shl_vd2d_vd2n_imm(&st, VEC_BUFFER, VEC_BUFFER, 32);
    orr_vd16b_vn16b_vm16b(&st, VEC_F6_F7_G6_G7, VEC_F6_F7_G6_G7, VEC_BUFFER);

    and_vd16b_vn16b_vm16b(&st, VEC_F8_F9_G8_G9, VEC_PROD, VEC_CONST_2X_2P32M1);
    





    
    
    print_vreg_as_4s(&st, VEC_F0_F1_G0_G1);
    print_vreg_as_4s(&st, VEC_F2_F3_G2_G3);
    print_vreg_as_4s(&st, VEC_F4_F5_G4_G5);
    print_vreg_as_4s(&st, VEC_F6_F7_G6_G7);
    print_vreg_as_4s(&st, VEC_F8_F9_G8_G9);



}

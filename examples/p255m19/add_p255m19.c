#include "a64rf.h"

extern void bignum_add_p25519(uint64_t z[static 4], const uint64_t x[static 4], const uint64_t y[static 4]);

extern uint64_t x[4];
extern uint64_t y[4];

#define d0 X3
#define d1 X4
#define d2 X5
#define d3 X6
#define c0 X7
#define c1 X8
#define c2 X9
#define c3 X10

int main(void)
{
    uint64_t z[4] = {0};
    uint64_t correct_z[4] = {0};

    bignum_add_p25519(correct_z, x, y);
    
    
    a64rf_state_t s;
    a64rf_state_init(&s, 0, 0);
    
    a64rf_addr_t x_ptr = alloc_mem(&s, 32, 8);
    write_mem_64(&s, x_ptr, x[0]);
    write_mem_64(&s, x_ptr+8, x[1]);
    write_mem_64(&s, x_ptr+16, x[2]);
    write_mem_64(&s, x_ptr+24, x[3]);
    
    a64rf_addr_t y_ptr = alloc_mem(&s, 32, 8);
    write_mem_64(&s, y_ptr, y[0]);
    write_mem_64(&s, y_ptr+8, y[1]);
    write_mem_64(&s, y_ptr+16, y[2]);
    write_mem_64(&s, y_ptr+24, y[3]);
    
    a64rf_addr_t z_ptr = alloc_mem(&s, 32, 8);
    
    
    write_val_gpr(&s, X0, z_ptr);
    write_val_gpr(&s, X1, x_ptr);
    write_val_gpr(&s, X2, y_ptr);
    
    
    
    ldp_xt1_xt2_xn(&s, d0, d1, X1);
    ldp_xt1_xt2_xn(&s, c0, c1, X2);
    adds_xd_xn_xm(&s, d0, d0, c0);
    adcs_xd_xn_xm(&s, d1, d1, c1);
    
    ldp_xt1_xt2_xn_imm(&s, d2, d3, X1, 16);
    ldp_xt1_xt2_xn_imm(&s, c0, c1, X2, 16);
    
    adcs_xd_xn_xm(&s, d2, d2, c0);
    adc_xd_xn_xm(&s, d3, d3, c1);
    
    movz_xd_imm_lsl_shift(&s, c3, (uint32_t)0x8000 , 48);
    
    adds_xd_xn_imm(&s, c0, d0, 19);
    adcs_xd_xn_xm(&s, c1, d1, XZR);
    adcs_xd_xn_xm(&s, c2, d2, XZR);
    adcs_xd_xn_xm(&s, c3, d3, c3);
    
    
    csel_xd_xn_xm(&s, d0, d0, c0, CC);
    csel_xd_xn_xm(&s, d1, d1, c1, CC);
    csel_xd_xn_xm(&s, d2, d2, c2, CC);
    csel_xd_xn_xm(&s, d3, d3, c3, CC);
    
    
    stp_xt1_xt2_xn_imm(&s, d0, d1, X0, 0);
    stp_xt1_xt2_xn_imm(&s, d2, d3, X0, 16);
    print_all_regs_and_flags(&s);
    
    
    int success = 0;
    success = read_mem_64(&s, z_ptr, &(z[0]));
    success = read_mem_64(&s, z_ptr + 8, &(z[1]));
    success = read_mem_64(&s, z_ptr + 16, &(z[2]));
    success = read_mem_64(&s, z_ptr + 24, &(z[3]));
    printf("Read memory success: %d\n", success);
    for (int i = 0; i < 4; i++) {
        printf("        z[%d] = %llu\n", i, (unsigned long long)z[i]);
        printf("correct_z[%d] = %llu\n", i, (unsigned long long)correct_z[i]);
    }

    return 0;
}

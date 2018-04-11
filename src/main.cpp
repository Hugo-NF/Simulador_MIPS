#include <iostream>
#include <thread>
#include "../include/memory.hpp"

using namespace std;

int main(int argc, char **argv) {

    int32_t r1, r2, r3, r4;
    memory MIPS_mem;


    MIPS_mem.sb(0, 0, 0x04); MIPS_mem.sb(0, 1, 0x03); MIPS_mem.sb(0, 2, 0x02); MIPS_mem.sb(0, 3, 0x01);
    MIPS_mem.sb(4, 0, 0xFF); MIPS_mem.sb(4, 1, 0xFE); MIPS_mem.sb(4, 2, 0xFD); MIPS_mem.sb(4, 3, 0xFC);
    MIPS_mem.sh(8, 0, 0xFFF0); MIPS_mem.sh(8, 2, 0x8C);
    MIPS_mem.sw(12, 0, 0xFF);
    MIPS_mem.sw(16, 0, 0xFFFF);
    MIPS_mem.sw(20, 0, 0xFFFFFFFF);
    MIPS_mem.sw(24, 0, 0x05000000);

    r1 = MIPS_mem.lw(0,0);
    r3 = MIPS_mem.lhu(8,2);

    r2 = MIPS_mem.lw(0,0);
    r4 = MIPS_mem.lhu(8,2);


    printf("lw(0,0) em big: %.8X\nlw(0,0) em little: %.8X\n", r1, r2);
    printf("lhu(8,2) em big: %.4X\nlhu(8,2) em little: %.4X\n", r3, r4);

    printf("lb(0,1): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(0,0), MIPS_mem.lb(0,0));
    printf("lb(0,1): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(0,1), MIPS_mem.lb(0,1));
    printf("lb(0,2): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(0,2), MIPS_mem.lb(0,2));
    printf("lb(0,3): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(0,3), MIPS_mem.lb(0,3));
    printf("lb(4,0): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(4,0), MIPS_mem.lb(4,0));
    printf("lb(4,1): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(4,1), MIPS_mem.lb(4,1));
    printf("lb(4,2): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(4,2), MIPS_mem.lb(4,2));
    printf("lb(4,3): Dec = %d\tHex = %.2X\n",MIPS_mem.lb(4,3), MIPS_mem.lb(4,3));

    printf("\nlbu(4,0): Dec = %d\n",MIPS_mem.lbu(4,0));
    printf("lbu(4,1): Dec = %d\n",MIPS_mem.lbu(4,1));
    printf("lbu(4,2): Dec = %d\n",MIPS_mem.lbu(4,2));
    printf("lbu(4,3): Dec = %d\n",MIPS_mem.lbu(4,3));

    printf("\nlh(8,0): Dec = %d\tHex = %.4X\n", MIPS_mem.lh(8,0), MIPS_mem.lh(8,0));
    printf("lh(8,2): Dec = %d\tHex = %.4X\n", MIPS_mem.lh(8,2), MIPS_mem.lh(8,2));

    printf("\nlhu(8,0): Dec = %d\n",MIPS_mem.lhu(8,0));
    printf("lhu(8,2): Dec = %d\n",MIPS_mem.lhu(8,2));

    printf("\nlw(12,0): Dec = %d\tHex = %.X\n", MIPS_mem.lw(12,0), MIPS_mem.lw(12,0));
    printf("lw(16,0): Dec = %d\tHex = %.X\n", MIPS_mem.lw(16,0), MIPS_mem.lw(16,0));
    printf("lw(20,0): Dec = %d\tHex = %.X\n", MIPS_mem.lw(20,0), MIPS_mem.lw(20,0));
    printf("lw(24,0): Dec = %d\tHex = %.X\n", MIPS_mem.lw(24,0), MIPS_mem.lw(24,0));

    MIPS_mem.dump_mem(0, 7, _word);


    return 0;
}
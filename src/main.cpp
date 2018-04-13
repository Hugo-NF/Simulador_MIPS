#include <iostream>
#include "../include/processor.hpp"

using namespace std;

int main(int argc, char **argv) {
    processor MIPS;

    MIPS.mem.sw(0,0, 0x080004B0);
    MIPS.fetch();
    MIPS.decode();

    printf("OPCODE: %d\n", MIPS.inst_fields.opcode);
    printf("RS: %d\n", MIPS.inst_fields.rs);
    printf("RT: %d\n", MIPS.inst_fields.rt);
    printf("RD: %d\n", MIPS.inst_fields.rd);
    printf("SHAMT: %d\n", MIPS.inst_fields.shammt);
    printf("FUNCT: %d\n", MIPS.inst_fields.funct);
    printf("K16: %d\n", MIPS.inst_fields.k16);
    printf("K26: %d\n", MIPS.inst_fields.k26);

    MIPS.~processor();

    return 0;
}
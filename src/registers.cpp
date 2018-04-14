#include "../include/registers.hpp"

registers::registers() {
    this->PC = 0x00000000;
    this->HI = 0x00000000;
    this->LO = 0x00000000;
    this->RI = 0x00000000;
    this->regs_description[0] = "$zero (Constant 0):\t\t\t\t\t\t";
    this->regs_description[1] = "$at (Reserved for assembler):\t\t\t\t\t";
    this->regs_description[2] = "$v0 (Expression evaluation and results of a function 1):\t";
    this->regs_description[3] = "$v1 (Expression evaluation and results of a function 2):\t";
    this->regs_description[4] = "$a0 (Argument 1):\t\t\t\t\t\t";
    this->regs_description[5] = "$a1 (Argument 2):\t\t\t\t\t\t";
    this->regs_description[6] = "$a2 (Argument 3):\t\t\t\t\t\t";
    this->regs_description[7] = "$a3 (Argument 4):\t\t\t\t\t\t";
    this->regs_description[8] = "$t0 (Temporary 1 - not preserved across call):\t\t\t";
    this->regs_description[9] = "$t1 (Temporary 2 - not preserved across call):\t\t\t";
    this->regs_description[10] = "$t2 (Temporary 3 - not preserved across call):\t\t\t";
    this->regs_description[11] = "$t3 (Temporary 4 - not preserved across call):\t\t\t";
    this->regs_description[12] = "$t4 (Temporary 5 - not preserved across call):\t\t\t";
    this->regs_description[13] = "$t5 (Temporary 6 - not preserved across call):\t\t\t";
    this->regs_description[14] = "$t6 (Temporary 7 - not preserved across call):\t\t\t";
    this->regs_description[15] = "$t7 (Temporary 8 - not preserved across call):\t\t\t";
    this->regs_description[16] = "$s0 (Saved temporary 1 - preserved across call):\t\t";
    this->regs_description[17] = "$s1 (Saved temporary 2 - preserved across call):\t\t";
    this->regs_description[18] = "$s2 (Saved temporary 3 - preserved across call):\t\t";
    this->regs_description[19] = "$s3 (Saved temporary 4 - preserved across call):\t\t";
    this->regs_description[20] = "$s4 (Saved temporary 5 - preserved across call):\t\t";
    this->regs_description[21] = "$s5 (Saved temporary 6 - preserved across call):\t\t";
    this->regs_description[22] = "$s6 (Saved temporary 7 - preserved across call):\t\t";
    this->regs_description[23] = "$s7 (Saved temporary 8 - preserved across call):\t\t";
    this->regs_description[24] = "$t8 (Temporary 9 - not preserved across call):\t\t\t";
    this->regs_description[25] = "$t9 (Temporary 10 - not preserved across call):\t\t\t";
    this->regs_description[26] = "$k0 (Reserved for OS kernel 1):\t\t\t\t\t";
    this->regs_description[27] = "$k1 (Reserved for OS kernel 2):\t\t\t\t\t";
    this->regs_description[28] = "$gp (Pointer to global area):\t\t\t\t\t";
    this->regs_description[29] = "$sp (Stack pointer):\t\t\t\t\t\t";
    this->regs_description[30] = "$fp (Frame pointer):\t\t\t\t\t\t";
    this->regs_description[31] = "$ra (Return address - used by function call):\t\t\t";
}

registers::~registers() = default;

void registers::dump_regs(output_format format) {
    const char *data_format;
    char output[CONSOLE_LEN];
    int i;

    switch (format) {
        case _dec:
            data_format = "%d";
            break;
        case _octal:
            data_format = "%.8o";
            break;
        default:
        case _hex:
            data_format = "0x%.8X";
            break;
    }

    printf("PC (Program Counter):\t\t\t\t");
    printf(data_format, PC);

    printf("\nHI (High-order word of multiply product):\t");
    printf(data_format, HI);

    printf("\nLO (Lower-order word of multiply product):\t");
    printf(data_format, LO);

    printf("\nRI (Read Instruction):\t\t\t\t");
    printf(data_format, RI);
    printf("\n\n");

    for (i = 0; i < B_REGS_SIZE; i++) {
        sprintf(output, data_format, reg[i]);
        printf("%s%s\n", regs_description[i].c_str(), output);
    }
}
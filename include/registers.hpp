#ifndef T2_SIMULADORMIPS_REGISTERS_HPP
#define T2_SIMULADORMIPS_REGISTERS_HPP

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include "constants.hpp"

#define B_REGS_SIZE 32

using namespace std;

class registers{
private:
    string regs_description[B_REGS_SIZE]; //Registers description

public:
    //Special registers
    uint32_t PC;    //Program counter
    int32_t HI;    //High-order word of multiply product
    int32_t LO;    //Low-order word of multiply product
    uint32_t RI;    //Read Instruction

    int32_t reg[B_REGS_SIZE];     //Registers

    explicit registers();   //Class default constructor
    virtual ~registers();   //Class default destructor


    inline void update_pc(memory_sizes step) {PC += step;}
    inline void branch_addr(int16_t immediate){ PC += (_word + (immediate<<2));}
    inline void jump_addr(uint32_t immediate){ PC = ((PC & 0xF0000000)|((immediate << 2)&0x0FFFFFFF));}
    void dump_regs(output_format format);

};


#endif //T2_SIMULADORMIPS_REGISTERS_HPP

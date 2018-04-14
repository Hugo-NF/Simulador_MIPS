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
    int32_t b_regs[B_REGS_SIZE];     //Registers
    string regs_description[B_REGS_SIZE]; //Registers description

public:
    //Special registers
    uint32_t PC;    //Program counter
    uint32_t HI;    //High-order word of multiply product
    uint32_t LO;    //Low-order word of multiply product

    uint32_t RI;    //Read Instruction

    explicit registers();   //Class default constructor
    virtual ~registers();   //Class default destructor


    inline void update_pc(memory_sizes step) {PC += step;}
    void write_at(unsigned int reg_idx, int32_t data);
    int32_t read_from(unsigned int reg_idx);
    void dump_regs(output_format format);

};


#endif //T2_SIMULADORMIPS_REGISTERS_HPP

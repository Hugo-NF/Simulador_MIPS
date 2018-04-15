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

    /**
     * @fn @public inline void update_pc(memory_sizes step);
     * @brief Função inline que incrementa o PC em 'step'
     * @param step: constante do tipo memory_sizes que indica o tamanho do incremento.
     * */
    inline void update_pc(memory_sizes step) {PC += step;}

    /**
     * @fn @public inline void branch_addr(int16_t immediate);
     * @brief Função inline que move o PC para o endereço da branch apontada por 'immediate'.
     * @param immediate: campo immediate16 (k16) do formato de instrução I.
     * */
    inline void branch_addr(int16_t immediate){ PC += (_word + (immediate<<2));}

    /**
     * @fn @public inline void jump_addr(uint32_t immediate);
     * @brief Função inline que move o PC para o endereço do salto apontado por 'immediate'.
     * @param immediate: campo immediate26 (k26) do formato de instrução J.
     * */
    inline void jump_addr(uint32_t immediate){ PC = ((PC & 0xF0000000)|((immediate << 2)&0x0FFFFFFF));}

    /**
     * @fn @public void dump_regs(output_format format);
     * @brief Função para exibir no console o conteúdo dos registradores, incluindo os especiais (PC, HI, LO, RI)
     * @param format: constante do tipo output_format que indica o formato de exibição (_hex, _dec, _oct) dos dados dos registradores.
     * */
    void dump_regs(output_format format);

};


#endif //T2_SIMULADORMIPS_REGISTERS_HPP

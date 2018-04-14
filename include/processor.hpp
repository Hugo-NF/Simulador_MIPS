#ifndef T2_SIMULADORMIPS_PROCESSOR_HPP
#define T2_SIMULADORMIPS_PROCESSOR_HPP

#include <fstream>
#include "registers.hpp"
#include "memory.hpp"
#include "constants.hpp"

#define BASE_DATA_ADDRESS 0x2000
#define PC_OUT_OF_BOUNDS  "Program Counter has joined data memory area\n"
#define UNKNOWN_OPCODE  "Could not solve OPCODE (Operation Code)\n"
#define UNKNOWN_FILE    "Could not find the specified file\n"

typedef struct decode{
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shammt;
    uint8_t funct;
    int16_t k16;
    uint32_t k26;
}decode_fields;

class processor{

private:
    decode_fields inst_fields;

    inline void lw(){}
    inline void lb(){}
    inline void lbu(){}
    inline void lh(){}
    inline void lhu(){}
    inline void lui(){}
    inline void sw(){}
    inline void sb(){}
    inline void sh(){}
    inline void beq(){}
    inline void bne(){}
    inline void blez(){}
    inline void bgtz(){}
    inline void addi(){}
    inline void slti(){}
    inline void sltiu(){}
    inline void andi(){}
    inline void ori(){}
    inline void xori(){}
    inline void j(){}
    inline void jal(){}
    inline void add(){}
    inline void sub(){}
    inline void mult(){}
    inline void div(){}
    inline void _and(){}
    inline void _or(){}
    inline void _xor(){}
    inline void nor(){}
    inline void slt(){}
    inline void jr(){}
    inline void sll(){}
    inline void srl(){}
    inline void sra(){}
    inline void syscall(){}
    inline void mfhi(){}
    inline void mflo(){}

public:
    memory mem;
    registers b_reg;

    explicit processor();
    virtual ~processor();

    void load_memory(const char *path, memory_section sec);
    void fetch(); //Throws
    void decode();
    void execute();
    void step(unsigned int amount);
    void run();
};

#endif //T2_SIMULADORMIPS_PROCESSOR_HPP

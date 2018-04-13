#ifndef T2_SIMULADORMIPS_PROCESSOR_HPP
#define T2_SIMULADORMIPS_PROCESSOR_HPP

#include "registers.hpp"
#include "memory.hpp"
#include "constants.hpp"

#define BASE_DATA_ADDRESS 0x2000
#define PC_OUT_OF_BOUNDS  "Program Counter has joined data memory area"
#define UNKNOWN_OPCODE  "Could not solve OPCODE (Operation Code)"

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

public:
    decode_fields inst_fields;

    memory mem;
    registers b_reg;

    explicit processor();
    virtual ~processor();

    void fetch(); //Throws
    void decode();
    void execute();
};

#endif //T2_SIMULADORMIPS_PROCESSOR_HPP

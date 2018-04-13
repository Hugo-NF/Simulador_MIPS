#ifndef T2_SIMULADORMIPS_MEMORY_HPP
#define T2_SIMULADORMIPS_MEMORY_HPP

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <exception>
#include "constants.hpp"

#define MEMORY_AMOUNT 4096
#define WORD_SIZE   4
#define INVALID_ACCESS_ERROR_MSG   "Invalid Memory Access"

using namespace std;

typedef struct memory_cell {
    uint8_t cell[WORD_SIZE];
}mem_cell;

//---------------------------------------------------------------------------------------------------------------------------------------

class memory {
private:
    vector<int> crt_addr;
    mem_cell memory_array[MEMORY_AMOUNT];
    int endianness;
    int addr_output;
    int data_output;

    void validate_address(uint32_t address, int16_t offset, mem_sizes word_size); //Checks alignment and maps the memory array (Throws)

public:
    explicit memory(int sel_endianness = _big, int addresses_format = _hex, int data_format = _hex);//Class construction declaring constraints
    virtual ~memory();             //Class virtual default destructor

    void set_endianness(int sel_endianness);
    void set_addr_output(int addresses_output);
    void set_data_output(int data_output);

    int32_t lw(uint32_t address, int16_t offset); //Reads a signed aligned memory position (Throws)
    int32_t lh(uint32_t address, int16_t offset);   //Reads a signed aligned half-word (Throws)
    uint32_t lhu(uint32_t address, int16_t offset); //Reads an unsigned aligned half-word (Throws)
    int32_t lb(uint32_t address, int16_t offset);   //Reads a signed byte (Throws)
    uint32_t lbu(uint32_t address, int16_t offset);  //Reads an unsigned byte (Throws)
    void sw(uint32_t address, int16_t offset, uint32_t data);    //Writes a word in an aligned memory position (Throws)
    void sh(uint32_t address, int16_t offset, uint16_t data);    //Writes a half-word in an aligned memory position (Throws)
    void sb(uint32_t address, int16_t offset, uint8_t data);     //Write a byte in memory (Throws)

    void dump_mem(uint32_t address, uint32_t amount, mem_sizes word_size);   //Displays memory content

};

#endif //T2_SIMULADORMIPS_MEMORY_HPP

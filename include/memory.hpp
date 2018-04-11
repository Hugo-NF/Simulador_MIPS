#ifndef T2_SIMULADORMIPS_MEMORY_HPP
#define T2_SIMULADORMIPS_MEMORY_HPP

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <exception>

#define MEMORY_AMOUNT 4096
#define WORD_SIZE   4
#define CONSOLE_LEN 80
#define INVALID_ACCESS_ERROR_MSG   "Invalid Memory Access"

using namespace std;

typedef enum output{
    _hex, _char, _octal, _dec
}output_format;

typedef enum end{
    _little, _big
}endianness;

typedef enum mem_sizes{
    _word = 4, _half_word = 2, _byte = 1
}memory_sizes;

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

    void validate_address(uint32_t address, int16_t offset, mem_sizes word_size); //Checks alignment and maps the memory array

public:
    explicit memory(int sel_endianness = _big, int addresses_format = _hex, int data_format = _hex);//Class construction declaring constraints
    virtual ~memory();             //Class virtual default destructor

    void set_endianness(int sel_endianness);
    void set_addr_output(int addresses_output);
    void set_data_output(int data_output);

    int32_t lw(uint32_t address, int16_t offset); //Reads a signed aligned memory position
    int32_t lh(uint32_t address, int16_t offset);   //Reads a signed aligned half-word
    uint32_t lhu(uint32_t address, int16_t offset); //Reads an unsigned aligned half-word
    int32_t lb(uint32_t address, int16_t offset);   //Reads a signed byte
    uint32_t lbu(uint32_t address, int16_t offset);  //Reads an unsigned byte
    void sw(uint32_t address, int16_t offset, uint32_t data);    //Writes a word in an aligned memory position
    void sh(uint32_t address, int16_t offset, uint16_t data);    //Writes a half-word in an aligned memory position
    void sb(uint32_t address, int16_t offset, uint8_t data);     //Write a byte in memory

    void dump_mem(uint32_t address, uint32_t amount, mem_sizes word_size);   //Displays memory content

};

#endif //T2_SIMULADORMIPS_MEMORY_HPP

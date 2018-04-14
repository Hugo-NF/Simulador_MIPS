#include "../include/memory.hpp"

memory::memory(int sel_endianness, int addresses_format, int data_format){
    this->endianness = sel_endianness;
    this->addr_output = addresses_format;
    this->data_output = data_format;
    crt_addr[0] = 0;
    crt_addr[1] = 0;
}

memory::~memory() = default;

void memory::set_endianness(int sel_endianness){
    this->endianness = sel_endianness;
}

void memory::set_addr_output(int addresses_output) {
    this->addr_output = addresses_output;
}

void memory::set_data_output(int data_output){
    this->data_output = data_output;
}


int32_t memory::lw(uint32_t address, int16_t offset){
    validate_address(address, offset, _word);

    int i, j, k, step = this->endianness ? 1 : -1;
    int upper_limit = this->endianness ? 0 : WORD_SIZE-1, lower_limit = this->endianness ? WORD_SIZE : -1;
    int32_t data = 0;
    uint8_t d[WORD_SIZE];

    for (i = 0; i < WORD_SIZE; i++)
        d[i] = this->memory_array[crt_addr[0]].cell[crt_addr[1]+i];

    for(k = upper_limit, j = WORD_SIZE-1; j >=0, k != lower_limit; j--, k+=step)
        data = data | d[k] << j*8;

    return data;
}

int32_t memory::lh(uint32_t address, int16_t offset){
    validate_address(address, offset, _half_word);

    int i, j, k, step = this->endianness ? 1 : -1;
    int upper_limit = this->endianness ? 0 : (WORD_SIZE/2)-1, lower_limit = this->endianness ? (WORD_SIZE/2) : -1;
    int32_t data = 0;
    uint8_t d[WORD_SIZE/2];

    for (i = 0; i < (WORD_SIZE/2); i++)
        d[i] = this->memory_array[crt_addr[0]].cell[crt_addr[1]+i];

    for(k = upper_limit, j = (WORD_SIZE/2)-1; j >=0, k != lower_limit; j--, k+=step)
        data = data | d[k] << j*8;

    data = (int32_t) (data > pow(2,(WORD_SIZE*8/2)-1)-1 ? data - pow(UINT8_MAX + 1, WORD_SIZE / 2) : data);

    return data;
}

uint32_t memory::lhu(uint32_t address, int16_t offset){
    validate_address(address, offset, _half_word);

    int i, j, k, step = this->endianness ? 1 : -1;
    int upper_limit = this->endianness ? 0 : (WORD_SIZE/2)-1, lower_limit = this->endianness ? (WORD_SIZE/2) : -1;
    uint32_t data = 0;
    uint8_t d[WORD_SIZE/2];

    for (i = 0; i < (WORD_SIZE/2); i++)
        d[i] = this->memory_array[crt_addr[0]].cell[crt_addr[1]+i];

    for(k = upper_limit, j = (WORD_SIZE/2)-1; j >=0, k != lower_limit; j--, k+=step)
        data = data | d[k] << j*8;

    return data;
}

int32_t memory::lb(uint32_t address, int16_t offset){
    validate_address(address, offset, _byte);

    int32_t data = 0;

    data = this->memory_array[crt_addr[0]].cell[crt_addr[1]];
    data = (int32_t) ((data > pow(2,8-1)-1) ? data - (UINT8_MAX+1) : data);

    return data;
}

uint32_t memory::lbu(uint32_t address, int16_t offset){
    validate_address(address, offset, _byte);

    uint32_t data = 0;

    data = this->memory_array[crt_addr[0]].cell[crt_addr[1]];

    return data;
}

void memory::sw(uint32_t address, int16_t offset, uint32_t data){
    validate_address(address, offset, _word);

    int i, j, k, step = this->endianness ? 1 : -1;
    int upper_limit = this->endianness ? 0 : WORD_SIZE-1, lower_limit = this->endianness ? WORD_SIZE : -1;
    uint8_t d[WORD_SIZE];

    for (i=0; i< WORD_SIZE ; i++)
        d[i] = ((uint8_t*)&data)[WORD_SIZE-1-i];

    for(k = upper_limit, j = 0; j < WORD_SIZE-1, k != lower_limit; j++, k+=step)
        this->memory_array[crt_addr[0]].cell[crt_addr[1]+j] = d[k];

}

void memory::sh(uint32_t address, int16_t offset, uint16_t data) {
    validate_address(address, offset, _half_word);

    int i, j, k, step = this->endianness ? 1 : -1;
    int upper_limit = this->endianness ? 0 : (WORD_SIZE / 2) - 1, lower_limit = this->endianness ? (WORD_SIZE / 2) : -1;
    uint8_t d[WORD_SIZE / 2];

    for (i = 0; i < WORD_SIZE / 2; i++)
        d[i] = ((uint8_t *) &data)[(WORD_SIZE / 2) - 1 - i];

    for (k = upper_limit, j = 0; j < (WORD_SIZE / 2) - 1, k != lower_limit; j++, k += step)
        this->memory_array[crt_addr[0]].cell[crt_addr[1] + j] = d[k];
}

void memory::sb(uint32_t address, int16_t offset, uint8_t data){    //Stores a byte in memory
    validate_address(address, offset, _byte);
    this->memory_array[crt_addr[0]].cell[crt_addr[1]] = data;
}

void memory::dump_mem(uint32_t address, uint32_t amount, mem_sizes word_size){
    int i;
    const char *addr_format, *data_format;

    switch (this->addr_output){
        case _octal:
            addr_format = "Memory at %.8o: ";
            break;
        case _dec:
            addr_format = "Memory at %.8d: ";
            break;
        default:
        case _hex:
            addr_format = "Memory at %.8X: ";
            break;
    }
    switch (this->data_output){
        case _octal:
            data_format = "%.2o";
            break;
        case _dec:
            data_format = "%d";
            break;
        case _char:
            data_format = "%c";
            break;
        default:
        case _hex:
            data_format = "%.2X";
            break;
    }

    while (amount != 0){
        try {
            validate_address(address, 0, word_size);
        } catch (exception const &exc) {
            break;
        }

        printf(addr_format, (crt_addr[0]*4 + crt_addr[1]));
        for(i = 0; i < word_size; i++)
            printf(data_format, this->memory_array[crt_addr[0]].cell[crt_addr[1]+i]);

        printf("\n");

        address += word_size;
        amount--;
    }
}

void memory::validate_address(uint32_t address, int16_t offset, mem_sizes word_size){
    bool is_valid = false;
    uint32_t abs_addr = address + offset;

    if(abs_addr < WORD_SIZE*MEMORY_AMOUNT && abs_addr >= 0) {
        switch (word_size) {
            case _word:
                if (abs_addr % _word == 0) {
                    crt_addr[0] = abs_addr / _word;
                    crt_addr[1] = 0;
                    is_valid = true;
                }
                break;
            case _half_word:
                if (abs_addr % _half_word == 0) {
                    crt_addr[0] = abs_addr / _word;
                    crt_addr[1] = abs_addr % _word;
                    is_valid = true;
                }
                break;
            case _byte:
                crt_addr[0] = abs_addr / _word;
                crt_addr[1] = abs_addr % _word;
                is_valid = true;
                break;
            default:
                break;
        }
    }
    if(!is_valid)
        throw logic_error(INVALID_ACCESS_ERROR_MSG);
}
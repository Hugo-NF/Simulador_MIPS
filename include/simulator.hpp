#ifndef T2_SIMULADORMIPS_SIMULATOR_HPP
#define T2_SIMULADORMIPS_SIMULATOR_HPP

#include "processor.hpp"

class simulator {
private:
    processor MIPS;

public:
    explicit simulator();
    virtual ~simulator();

    inline void read_binary(const char *path, memory_section sec){ this->MIPS.load_memory(path, sec); }
    void step(unsigned int amount);
    void run();
};

#endif //T2_SIMULADORMIPS_SIMULATOR_HPP

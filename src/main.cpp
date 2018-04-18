#include <iostream>
#include <chrono>
#include "../include/processor.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    system_clock::time_point start = system_clock::now();

    if(argc == 3) {
        processor MIPS;
        MIPS.load_memory_binary(argv[0], _text);
        MIPS.load_memory_binary(argv[1], _data);

        MIPS.run();

        MIPS.b_reg.dump_regs(_hex);
        MIPS.mem.dump_mem(0, 30, _word);
    }
    system_clock::time_point end = system_clock::now();
    system_clock::duration elapsed = (end - start);
    printf("Elapsed Time: %d miliseconds\n", elapsed.operator/=(1000000));

    return 0;
}
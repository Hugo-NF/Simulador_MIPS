#include <iostream>
#include <chrono>
#include "../include/processor.hpp"


using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    system_clock::time_point start = system_clock::now();

    //printf("%ld\n", strtol("20082000", nullptr, 16));
    processor MIPS;



    //MIPS.load_memory_text("../test/text", _text, 16);
    //MIPS.load_memory_text("../test/data", _data, 16);
    MIPS.load_memory_binary("../test/text1.bin", _text);
    MIPS.load_memory_binary("../test/data1.bin", _data);

   /* MIPS.mem.sw(0, 0, 0x20082000);
    MIPS.mem.sw(4, 0, 0x8D080000);
    MIPS.mem.sw(8, 0, 0x20020001);
    MIPS.mem.sw(12, 0, 0x00082020);
    MIPS.mem.sw(16, 0, 0x0000000C);
    MIPS.mem.sw(20, 0, 0x00082040);
    MIPS.mem.sw(24, 0, 0xAC042000);
    MIPS.mem.sw(28, 0, 0x0000000C);
    MIPS.mem.sw(32, 0, 0x20020011);
    MIPS.mem.sw(36, 0, 0x2004000B);
    MIPS.mem.sw(40, 0, 0x0000000C);
    MIPS.mem.sw(0x2000,0,0x00000021);*/
    MIPS.mem.dump_mem(0, 10,_word);
    MIPS.run();

    system_clock::time_point end = system_clock::now();
    system_clock::duration elapsed = (end - start);
    printf("Elapsed Time: %d miliseconds\n", elapsed.operator/=(1000000));

    return 0;
}
#include <iostream>
#include <chrono>
#include "../include/processor.hpp"
#include "../include/simulator.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv) {
    system_clock::time_point start = system_clock::now();

    simulator SIM;

    SIM.read_binary("text.bin", _text);

    SIM.~simulator();

    system_clock::time_point end = system_clock::now();
    system_clock::duration elapsed = (end - start);
    printf("Elapsed Time: %d miliseconds\n", elapsed.operator/=(1000000));
    return 0;
}
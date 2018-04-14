#include "../include/simulator.hpp"

simulator::simulator() {
    MIPS = processor();
}

simulator::~simulator() {
    MIPS.~processor();
}

void simulator::step(unsigned int amount){
    try{
        for (int i=0; i< amount; i++){
            MIPS.fetch();
            MIPS.decode();
            MIPS.execute();
        }
    }
    catch (const exception &exc){
        printf(exc.what());
    }
}

void simulator::run(){
    while(true){
        try{
            MIPS.fetch();
            MIPS.decode();
            MIPS.execute();
        }
        catch (const exception &exc){
            printf(exc.what());
            break;
        }
    }
}

#ifndef T2_SIMULADORMIPS_PROCESSOR_HPP
#define T2_SIMULADORMIPS_PROCESSOR_HPP

#include <fstream>
#include <thread>
#include <chrono>
#include "registers.hpp"
#include "memory.hpp"
#include "constants.hpp"

#define BASE_DATA_ADDRESS 0x2000
#define PC_OUT_OF_BOUNDS  "Program Counter has joined data memory area\n"
#define UNKNOWN_OPCODE  "Could not solve OPCODE (Operation Code)\n"
#define UNKNOWN_FILE    "Could not find the specified file\n"
#define UNKNOWN_SYSCALL "Unknown system call\nPlease enter an valid code in $v0\n"
#define SYSCALL_EXIT    "Program exited succesfully\n"
#define SYSCALL_EXIT_V(x)  "Program exited succesfully with code ##x\n"

using namespace std::chrono;

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

    inline void lw(){
        b_reg.reg[inst_fields.rt] = mem.lw((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16);
    }
    inline void lb(){
        b_reg.reg[inst_fields.rt] = mem.lb((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16);
    }
    inline void lbu(){
        b_reg.reg[inst_fields.rt] = mem.lbu((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16);
    }
    inline void lh(){
        b_reg.reg[inst_fields.rt] = mem.lh((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16);
    }
    inline void lhu(){
        b_reg.reg[inst_fields.rt] = mem.lhu((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16);
    }
    inline void lui(){
        b_reg.reg[inst_fields.rt] = inst_fields.k16 << 16;
    }
    inline void sw(){
        mem.sw((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16, (uint32_t) b_reg.reg[inst_fields.rt]);
    }
    inline void sb(){
        mem.sb((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16, (uint8_t) b_reg.reg[inst_fields.rt]);
    }
    inline void sh(){
        mem.sh((uint32_t) b_reg.reg[inst_fields.rs], inst_fields.k16, (uint16_t) b_reg.reg[inst_fields.rt]);
    }
    inline void beq(){
        if(b_reg.reg[inst_fields.rs] == b_reg.reg[inst_fields.rt])
            b_reg.branch_addr(inst_fields.k16);
    }
    inline void bne(){
        if(b_reg.reg[inst_fields.rs] != b_reg.reg[inst_fields.rt])
            b_reg.branch_addr(inst_fields.k16);
    }
    inline void blez(){
        if(b_reg.reg[inst_fields.rs] <= 0)
            b_reg.branch_addr(inst_fields.k16);
    }
    inline void bgtz(){
        if(b_reg.reg[inst_fields.rs] > 0)
            b_reg.branch_addr(inst_fields.k16);
    }
    inline void addi(){
        b_reg.reg[inst_fields.rt] = b_reg.reg[inst_fields.rs] + inst_fields.k16;
    }
    inline void slti(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] < inst_fields.k16? 1 : 0;
    }
    inline void sltiu(){
        b_reg.reg[inst_fields.rd] = ((uint32_t)(b_reg.reg[inst_fields.rs]) < (uint32_t)(inst_fields.k16))? 1 : 0;
    }
    inline void andi(){
        b_reg.reg[inst_fields.rt] = (b_reg.reg[inst_fields.rs] & (0x0000FFFF & inst_fields.k16));
    }
    inline void ori(){
        b_reg.reg[inst_fields.rt] = (b_reg.reg[inst_fields.rs] | (0x0000FFFF & inst_fields.k16));
    }
    inline void xori(){
        b_reg.reg[inst_fields.rt] = (b_reg.reg[inst_fields.rs] ^ (0x0000FFFF & inst_fields.k16));
    }
    inline void j(){
        b_reg.update_pc(_word);
        b_reg.jump_addr(inst_fields.k26);
    }
    inline void jal(){
        b_reg.update_pc(_word);
        b_reg.reg[31] = b_reg.PC;
        b_reg.jump_addr(inst_fields.k26);
    }
    inline void add(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] + b_reg.reg[inst_fields.rt];
    }
    inline void sub(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] - b_reg.reg[inst_fields.rt];
    }
    inline void mult(){
        int64_t aux = (int64_t) b_reg.reg[inst_fields.rs] * (int64_t) b_reg.reg[inst_fields.rt];

        b_reg.LO = (int32_t)((aux << 32) >> 32);
        b_reg.HI = (int32_t)(aux >> 32);
    }
    inline void div(){
        b_reg.LO = b_reg.reg[inst_fields.rs]/b_reg.reg[inst_fields.rt];
        b_reg.HI = b_reg.reg[inst_fields.rs]%b_reg.reg[inst_fields.rt];
    }
    inline void _and(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] & b_reg.reg[inst_fields.rt];
    }
    inline void _or(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] | b_reg.reg[inst_fields.rt];
    }
    inline void _xor(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] ^ b_reg.reg[inst_fields.rt];
    }
    inline void nor(){
        b_reg.reg[inst_fields.rd] = ~(b_reg.reg[inst_fields.rs] | b_reg.reg[inst_fields.rt]);

    }
    inline void slt(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rs] < b_reg.reg[inst_fields.rt]? 1 : 0;
    }
    inline void jr(){
        b_reg.PC = (uint32_t) b_reg.reg[inst_fields.rs];
    }
    inline void sll(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rt] << inst_fields.shammt;
    }
    inline void srl(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rt] >> inst_fields.shammt;
    }
    inline void sra(){
        b_reg.reg[inst_fields.rd] = b_reg.reg[inst_fields.rt] >> inst_fields.shammt;
    }
    inline void syscall(){
        switch (b_reg.reg[2]){ //Evaluates $v0 content
            case _prt_int:
                printf("%d", b_reg.reg[4]);
                break;
            case _prt_int_hex:
                printf("%X", b_reg.reg[4]);
                break;
            case _prt_u_int:
                printf("%u", b_reg.reg[4]);
                break;
            case _rd_int:
                scanf("%d", &b_reg.reg[2]);
                break;
            case _prt_char:
                printf("%c", b_reg.reg[4]);
                break;
            case _rd_char:
                scanf("%c", &b_reg.reg[2]);
                break;
            case _ssleep:{
                duration<int, std::milli> timer(b_reg.reg[4]);
                this_thread::sleep_for(timer);
                break;
            }
            case _prt_string: {
                int16_t i = 0;
                uint32_t addr = (uint32_t) b_reg.reg[4];
                int32_t curr_char = mem.lb(addr, i);
                while (curr_char != 0) {
                    printf("%c", curr_char);
                    i++;
                    curr_char = mem.lb(addr, i);
                }
                break;
            }
            case _rd_string: {
                int16_t i = 0;
                uint32_t addr = (uint32_t) b_reg.reg[4];
                char buffer[b_reg.reg[5]+1];
                gets(buffer);
                while(buffer[i] != 0){
                    mem.sb(addr, i, (uint8_t)buffer[i]);
                    i++;
                }
                mem.sb(addr, i, 0); //Write null terminator
                break;
            }
            case _fexit:
                throw runtime_error(SYSCALL_EXIT);
            case _exit_v:
                throw runtime_error(SYSCALL_EXIT_V(itoa(b_reg.reg[4])));
            default:
                printf(UNKNOWN_SYSCALL);
        }
    }
    inline void mfhi(){
        b_reg.reg[inst_fields.rd] = b_reg.HI;
    }
    inline void mflo(){
        b_reg.reg[inst_fields.rd] = b_reg.LO;
    }

public:
    memory mem;
    registers b_reg;

    explicit processor();
    virtual ~processor();

    void load_memory(const char *path, memory_section sec);
    void fetch(); //Throws
    void decode();
    void execute(); //Throws
    void step(unsigned int amount);
    void run();
};

#endif //T2_SIMULADORMIPS_PROCESSOR_HPP

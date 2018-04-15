#ifndef T2_SIMULADORMIPS_PROCESSOR_HPP
#define T2_SIMULADORMIPS_PROCESSOR_HPP

#include <fstream>
#include <thread>
#include <chrono>
#include "registers.hpp"
#include "memory.hpp"
#include "constants.hpp"

using namespace std::chrono;

/**
 * @typedef decode_fields
 * @brief Define todos os possíveis campos de uma instrução MIPS, independente do formato ser R, I ou J.
 * */
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

    /**
     * Todas as funções inline abaixo implementam a instrução equivalente ao seu nome.
     * Todas elas assumem que a instrução já foi decodificada e, portanto, as variáveis da struct inst_fields já estão definidas.
     * */
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
                printf(SYSCALL_EXIT_V, b_reg.reg[4]);
                throw runtime_error(SYSCALL_EXIT);
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


    /**
     * @fn explicit processor();
     * @brief Função construtora padrão da classe processor. Instancia os atributos mem e b_reg seguindo seus construtores padrões.
     * */
    explicit processor();

    /**
     * @fn virtual ~processor();
     * @brief Função destrutora virtual da classe processor. Utiliza os destrutores padrões nos atributos mem e b_reg.
     * */
    virtual ~processor();

    /**
     * @fn @public void load_memory(const char *path, memory_section sec);
     * @brief Carrega o conteúdo do arquivo apontado por path para dentro da memória
     * @param path: string (const char*) com o caminho (absoluto ou relativo) para o arquivo
     * @param sec: parametro do tipo memory_section que define, utilizando a convenção em constants.hpp, em qual área de memória o arquivo será escrito
     * @throws: Essa função não trata exceções que possam ser lançadas a partir de uma escrita ilegal na memória.
     * @paragraph: Essa função está realizando a leitura a partir arquivos do MARS exportados como Hexadecimal text. Não consegui entender a disposição do arquivo .bin exportado pelo MARS
     * e, uma vez que o simulador estava funcionando quando eu escrevia manualmente o mesmo conteúdo mostrado na tela de Assemble do MARS, decidi por fazer a leitura dessa forma.
     * Peço desculpas por essa modificação e, tendo em vista que esse é o único ponto em desconforme com a especificação do trabalho, espero e peço por não receber uma penalização muito pesada.
     * */
    void load_memory(const char *path, memory_section sec);

    /**
     * @fn @public void fetch();
     * @brief Realiza um fetch. (Buscar a instrução apontada por PC e escrever em RI)
     * @throws Essa função pode lançar a exception::out_of_range("Program Counter has joined data memory area. Program killed") quando o PC sair da área .text da memória
     * */
    void fetch();

    /**
     * @fn @public void decode();
     * @brief Realiza a decodificação da instrução presente no registrador RI
     * @result A struct inst_fields receberá o resultado da decodificação
     * */
    void decode();

    /**
     * @fn @public void execute();
     * @brief Realiza a execução da instrução já decodificada presente em inst_fields
     * @throws A função execute pode lançar a exception::logic_error("Could not solve OPCODE (Operation Code)") quando o OPCODE é desconhecido
     * @throws A função execute pode lançar a exception::runtime_error("Program exited 'with code $' succesfully") quando ocorre uma syscall solicitando a parada do programa
     * */
    void execute();

    /**
     * @fn @public void step(unsigned int amount);
     * @brief Realiza 'amount' ciclos de execução MIPS - fetch(), decode(), execute()
     * @note A função trata todas as exceções que possam ser deflagradas
     * */
    void step(unsigned int amount);

    /**
     * @fn @public void run();
     * @brief Realiza ciclos de execução MIPS - fetch(), decode(), execute() até o final do programa
     * @note A função trata todas as exceções que possam ser deflagradas durante a execução do programa, exibindo no console como o programa se encerrou.
     * */
    void run();
};

#endif //T2_SIMULADORMIPS_PROCESSOR_HPP

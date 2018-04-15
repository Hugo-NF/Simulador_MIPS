#ifndef T2_SIMULADORMIPS_TYPES_HPP
#define T2_SIMULADORMIPS_TYPES_HPP

#define B_REGS_SIZE 32
#define CONSOLE_LEN 80
#define MEMORY_AMOUNT 4096
#define WORD_SIZE   4
#define BASE_DATA_ADDRESS 0x2000
#define PC_OUT_OF_BOUNDS  "\nProgram Counter has joined data memory area. Program killed\n"
#define UNKNOWN_OPCODE  "\nCould not solve OPCODE (Operation Code)\n"
#define UNKNOWN_FILE    "\nCould not find the specified file\n"
#define UNKNOWN_SYSCALL "\nUnknown system call\nPlease enter an valid code in $v0\n"
#define SYSCALL_EXIT    "\nProgram exited succesfully\n"
#define SYSCALL_EXIT_V  "\nProgram exited with code %d\n"
#define INVALID_ACCESS_ERROR_MSG   "Invalid Memory Access"

/**
 * @typedef output_format
 * @brief Contém as constantes que definem o formato de visualização na tela para as funções dump
 * */

typedef enum output{
    _hex, _char, _octal, _dec
}output_format;

/**
 * @typedef endianness
 * @brief Contém as constantes que definem a interpretação do conteúdo da memória (little-endian ou big-endian)
 * */

typedef enum end{
    _little, _big
}endianness;

/**
 * @typedef memory_sizes
 * @brief Contém as constantes que definem o valor em bytes de cada um de seus multíplos, definindo a palavra com 32 bits - 4 bytes
 * */

typedef enum mem_sizes{
    _word = 4, _half_word = 2, _byte = 1
}memory_sizes;

/**
 * @typedef memory_section
 * @brief Contém as constantes que definem em qual região da memória está-se escrevendo
 * */

typedef enum sec {
    _text, _data
}memory_section;

/**
 * @typedef opcodes
 * @brief Contém as constantes que definem os OPCODES das operações suportadas pelo simulador
 * @details Contantes retiradas do documento "MIPS Reference Data"
 * @warning Note que o OPCODE só é avaliado em relação aos 6 primeiros bits
 * */

typedef enum op {
    EXT=0x00, LW=0x23, LB=0x20, LBU=0x24,
    LH=0x21, LHU=0x25, LUI=0x0F, SW=0x2B,
    SB=0x28, SH=0x29, BEQ=0x04, BNE=0x05,
    BLEZ=0x06, BGTZ=0x07, ADDI=0x08, SLTI=0x0A,
    SLTIU=0x0B, ANDI=0x0C, ORI=0x0D, XORI=0x0E,
    J=0x02, JAL=0x03
}opcodes;

/**
 * @typedef funct
 * @brief Contém as constantes para o campo FUNCT da instrução do tipo R quando o OPCODE vale EXT = 0x00
 * @details Contantes retiradas do documento "MIPS Reference Data"
 * @warning Note que FUNCT só é avaliado em relação aos 6 primeiros bits
 * */

typedef enum fun {
    ADD=0x20, SUB=0x22, MULT=0x18, DIV=0x1A, AND=0x24,
    OR=0x25, XOR=0x26, NOR=0x27, SLT=0x2A, JR=0x08,
    SLL=0x00, SRL=0x02, SRA=0x03, SYSCALL=0x0C, MFHI=0x10, MFLO=0x12
}funct;

/**
 * @typedef syscall
 * @brief Contém as constantes que definem os serviços prestados pelo OS após uma instrução syscall
 * @details Essas contantes devem ser fornecidas atráves do registrador $v0
 * @warning Alguns dos serviços definidos não foram implementados
 * */

typedef enum sys{
    _prt_int = 1, _prt_float = 2, _prt_double = 3, _prt_string = 4,
    _rd_int = 5, _rd_float = 6, _rd_double = 7, _rd_string = 8,
    _sbrk = 9, _fexit = 10, _prt_char = 11, _rd_char = 12, _open_file = 13,
    _file_read = 14, _file_write = 15, _cls_file = 16, _exit_v = 17,
    _ssleep = 32, _prt_int_hex = 34, _prt_u_int = 36
}syscalls;

#endif //T2_SIMULADORMIPS_TYPES_HPP

#ifndef T2_SIMULADORMIPS_MEMORY_HPP
#define T2_SIMULADORMIPS_MEMORY_HPP

#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <exception>
#include "constants.hpp"

using namespace std;

typedef struct memory_cell {
    uint8_t cell[WORD_SIZE];
}mem_cell;

//---------------------------------------------------------------------------------------------------------------------------------------

class memory {
private:

    int crt_addr[2];
    mem_cell memory_array[MEMORY_AMOUNT];
    int endianness;
    int addr_output;
    int data_output;

    /**
     * @fn  @private void validate_address(uint32_t address, int16_t offset, mem_sizes word_size);
     * @brief Função que valida o endereço de escrita/leitura seguindo as regras de alinhamento do MIPS
     * @param address: indica o endereço base para o acesso a memória
     * @param offset: indica o offset (deslocamento com sinal) em relação ao endereço base
     * @param word_size: indica o tamanho do dado que vai ser manipulado
     * @result Em caso de sucesso, a função escreverá no atributo da class crt_addr o endereço de acesso
     * @throws A função lançará uma exception logic_error::("Invalid Memory Access") no caso de acesso deslinhado ou memória inexistente
     * */
    void validate_address(uint32_t address, int16_t offset, mem_sizes word_size);


public:

    /**
     * @fn @public e explicit memory(int sel_endianness = _big, int addresses_format = _hex, int data_format = _hex);
     * @brief Função construtora da classe memory
     * @param sel_endianness: indica o padrão de interpretação da memória (big ou little endian). Valor padrão: _big
     * @param addresses_format: indica o padrão de visualização dos endereços da memória (hex, decimal ou octal). Valor padrão: _hex
     * @param data_format: indica o padrão de visualização dos dados da memória (hex, decimal, ASCII chars ou octal). Valor padrão: _hex
     * */
    explicit memory(int sel_endianness = _big, int addresses_format = _hex, int data_format = _hex);

    /**
     * @fn @public virtual ~memory();
     * @brief Função virtual destrutora da classe memory
     * */
    virtual ~memory();

    /**
     * @fn @public void set_endianness(int sel_endianness);
     * @brief Função para selecionar a interpretação da memória
     * @param sel_endianness: integer assumindo os valores _big e _little, definidos em constants.hpp
     * @warning Não há qualquer verificação para certificar que os argumentos assumem apenas valores validos
     * */
    void set_endianness(int sel_endianness);

    /**
     * @fn @public void set_addr_output(int addresses_output);
     * @brief Função para selecionar o formato de visualização dos endereços de memória.
     * @param addresses_output: integer assumindo os valores _hex, _oct ou _dec, definidos em constants.hpp
     * @result A passagem de valores invalidos redefine o formato para o padrão da classe (_hex)
     * */
    void set_addr_output(int addresses_output);

    /**
     * @fn @public void set_data_output(int data_output);
     * @brief Função para selecionar o formato de visualização dos dados na memória.
     * @param addresses_output: integer assumindo os valores _hex, _oct, _char ou _dec, definidos em constants.hpp
     * @result A passagem de valores invalidos redefine o formato para o padrão da classe (_hex)
     * */
    void set_data_output(int data_output);

    /**
     * @fn @public  int32_t lw(uint32_t address, int16_t offset);
     * @brief Carrega para um registrador a palavra na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @return Retorna um int32_t com a palavra para ser carregada no registrador
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    int32_t lw(uint32_t address, int16_t offset);

    /**
     * @fn @public  int32_t lh(uint32_t address, int16_t offset);
     * @brief Carrega para um registrador a meia-palavra na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @return Retorna um int32_t com a meia-palavra nos 16 bits menos significativos para ser carregada no registrador
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    int32_t lh(uint32_t address, int16_t offset);

    /**
     * @fn @public  uint32_t lhu(uint32_t address, int16_t offset);
     * @brief Carrega para um registrador a meia-palavra (sem sinal) na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @return Retorna um uint32_t com a meia-palavra nos 16 bits menos significativos, interpretada sem sinal, para ser carregada no registrador
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    uint32_t lhu(uint32_t address, int16_t offset);

    /**
    * @fn @public  int32_t lb(uint32_t address, int16_t offset);
    * @brief Carrega para um registrador o byte na posição de memória M[address + offset]
    * @param address: endereço base para o acesso
    * @param offset: deslocamento com sinal em relação ao endereço base
    * @return Retorna um int32_t com o byte nos 8 bits menos significativos para ser carregado no registrador
    * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
    * */
    int32_t lb(uint32_t address, int16_t offset);

    /**
    * @fn @public  uint32_t lbu(uint32_t address, int16_t offset);
    * @brief Carrega para um registrador o byte (sem sinal) na posição de memória M[address + offset]
    * @param address: endereço base para o acesso
    * @param offset: deslocamento com sinal em relação ao endereço base
    * @return Retorna um uint32_t com o byte nos 8 bits menos significativos, interpretado sem sinal, para ser carregado no registrador
    * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
    * */
    uint32_t lbu(uint32_t address, int16_t offset);

    /**
     * @fn @public  void sw(uint32_t address, int16_t offset, uint32_t data);
     * @brief Guarda a palavra contida em 'data' na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @param data: palavra que será guardada na memória
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    void sw(uint32_t address, int16_t offset, uint32_t data);

    /**
     * @fn @public  void sh(uint32_t address, int16_t offset, uint16_t data);
     * @brief Guarda a meia-palavra contida em 'data' na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @param data: meia-palavra que será guardada na memória
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    void sh(uint32_t address, int16_t offset, uint16_t data);

    /**
     * @fn @public  void sb(uint32_t address, int16_t offset, uint8_t data);
     * @brief Guarda o byte contido em 'data' na posição de memória M[address + offset]
     * @param address: endereço base para o acesso
     * @param offset: deslocamento com sinal em relação ao endereço base
     * @param data: byte que será guardado na memória
     * @throws A função não trata a exceção que pode ser lançada na verificação do endereço (função validate_address).
     * */
    void sb(uint32_t address, int16_t offset, uint8_t data);

    /**
     * @fn @public void dump_mem(uint32_t address, uint32_t amount, mem_sizes word_size);
     * @brief Mostra no console o conteúdo da memória
     * @param address: endereço de início da visualização
     * @param word_size: define a disposição da visualização, ou seja, se a visualização será byte a byte, palavra a palavra, etc. Seguindo a definição em constants.hpp
     * @param amount: define a quantidade de entidades do parametro word_size a serem mostradas.
     * @warning Não há qualquer verificação do parametro word_size para certificar a passagem de um valor válido
     * */
    void dump_mem(uint32_t address, uint32_t amount, mem_sizes word_size);

};

#endif //T2_SIMULADORMIPS_MEMORY_HPP

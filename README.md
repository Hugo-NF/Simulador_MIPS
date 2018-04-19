# Simulador da arquitetura MIPS
- Este projeto consiste em construir um software em linguagem C++ para simular a execução, sem pipeline, das instruções na arquitetura MIPS e constitui a entrega total do trabalho 2 da disciplina de Organização e Arquitetura de Computadores (semestre 2018/1) da Universidade de Brasília.

- Compilação:
    1. Através do arquivo CMakeLists.txt, utilizando o CMake ($ cmake CMakeLists.txt)
        - Obs.: a diretiva cmake_minimum_required(VERSION 3.X)
        pode ser alterada de acordo com a versão do CMake disponível
    2. Compilação através do Makefile gerado ($ make)

- Execução
    1. Linha de comando passando como argumentos os endereços dos arquivos .text e .data, respectivamente.
        - Obs.: O simulador irá rodar o programa inserido na linha de comando até o final (MIPS.run()).
        Caso deseje executar outras funcionalidades, o arquivo main.c deve ser editado.

- Desenvolvimento
    1. Desenvolvido na plataforma Windows (IDE CLion 2018.1), compilador GNU gcc/g++.
    2. Testado no Windows 10 (CMake 3.9.0) e Ubuntu 16.04 (CMake 3.5.1)
# Trabalhos Algebra Linear Computacional - COC473

Este repositório contém os trabalhos produzidos para a disciplina COC473 - Álgebra Linear Computacional no período de 2019/1 da UFRJ.

O repositório utiliza a suite de testes unitários [googletest](https://github.com/google/googletest) como submódulo. Para clonar com o submódulo, use 
```
git clone --recursive
```
ou
```
git submodule update --init --recursive
```
se o repositório já foi clonado anteriormente.

## Instruções para Compilação

O projeto pode ser compilado utilizando a aplicação CMake, através dos comandos a seguir no diretório do projeto.
```
cmake . -Bbuild
cmake --build build
```
Ou ainda através do Makefile incluso, executando o comando abaixo no diretório do projeto.
```
make
```
Em ambos os casos será gerado um executável ```alc``` no diretório ```build```, que será criado se não existir.
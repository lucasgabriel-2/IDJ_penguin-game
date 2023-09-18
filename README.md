# Game - Let's get the aliens (The penguin Game)

## Aluno

| Matrícula  | Aluno                                                                   |
|------------|-------------------------------------------------------------------------|
| 19/0112123 | [Lucas Gabriel Sousa Carmargo Paiva](https://github.com/lucasgabriel-2) |

## Sobre

Nesse repositório estão os trabalhos realizados durante a disciplina de Introdução ao Desenvolvimento de Jogos da Universidade de Brasília, com intuito de programar um jogo do estilo Top Down Shooter 2D.

## Tecnologias utilizadas 

**Ferramenta**: GNU Make <br/>

**Linguagem**: C++ <br/>

**Biblioteca**: Simple DirectMedia Layer (SDL) <br/>

## Instalação para distros Linux baseadas no Debian

1- Atualize a lista de pacotes disponíveis e os pacotes instalados para a versão mais recente disponível

    sudo apt-get update && sudo apt-get upgrade

2- Instale o GNU Make e o compilador g++ para linguagem C++

    sudo apt-get install build-essential

3- Verifique sua versão do g++ (necessário versão 4.7 ou superior)

    g++ --version

4- Instale as bibliotecas necessárias da SDL

    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev  libsdl2-ttf-dev libsdl2-ttf-2.0-0 libsdl2-2.0-0

## Compilação do projeto para distros Linux baseadas no Debian

Para compilar o código em modo release

1- Abra o terminal no local onde está o Makefile (o qual foi criado pelos monitores da disciplina de Introdução ao Desenvolvimento de Jogos)

2- Execute o comando
    
    make config=release

3- Caso deseje executar o programa compilado basta executar o comando

    ./penguinGame_release

Para compilar o código em modo debug

1- Abra o terminal no local onde está o Makefile (o qual foi criado pelos monitores da disciplina de Introdução ao Desenvolvimento de Jogos)

2- Execute o comando 
    
    make

3- Caso deseje executar o programa compilado basta executar o comando

    ./penguinGame_debug

# Exercício 3 - Contagem de Ciclos
## Nome: Guilherme Lucas da Silva
## RA: 155618

## 1. Introdução
Desde a invenção da Computação, engenheiros procuram por projetos de hardware cada vez mais rápidos e melhores, para realizar uma enorme gama de atividades de maneira mais eficaz, levando a maiores lucros e resultados significativos para os usuários. Junto com essas melhorias, é necessária a criação de métodos que avaliem as máquinas de maneira transparente e verdadeira, para que o usuário possa escolher qual equipamento melhor se encaixa na sua necessidade. Dito isso, existem várias maneiras de comparar hardwares disponíveis:  

- Tempo gasto do início ao fim de uma atividade.  
- Porcentagem de memória gasta para o processo analisado.  
- Ciclos gastos para execução de uma instrução (CPI).    

O nosso foco nesse experimento é analisar esse último critério apresentado. Para podermos entender o que é **CPI** (ciclos por instrução) devemos ter em mente que um processador realiza suas tarefas por meio de ciclos, que são estágios em que o computador realizar algum tipo de tarefa muito bem definida. Nesse exercício, vamos analisar a arquitetura **MIPS**. Essa tem os seguintes estágios que definem um ciclo:  

    1. Instruction fetch cycle (IF).
    2. Instruction decode/Register fetch cycle (ID).
    3. Execution/Effective address cycle (EX).
    4. Memory access (MEM).
    5. Write-back cycle (WB).  
    
Os nomes desses estágios são, na maioria dos casos, utilizados com seu nome em inglês e por isso decidi mantê-los. Cada estágio tem o seguinte significado:  

    1. Busca da instrução na memória.
    2. Decodificação da instrução, setando sinais de controle para executá-la corretamente.  
    3. Ciclo em que as operações aritiméticas são executadas, para algum tipo de operação matemática do programa ou deslocamente de endereço.
    4. Acesso de memória para buscar dados necessários para executar a instrução.
    5. Escreve os resultados de volta na memória.  
    
Assim, fica claro que **CPI** é uma medida de extrema importância quando estamos analisando um sistema, já que quanto mais ciclos um processador gastar para executar uma instrução, existe uma grande chance dele gastar mais tempo e energia.  
Então, notamos que, para avaliarmos máquinas diferentes em simulares, continua sendo importante medidas como **tempo, CPI e quantidade de memória**.  

## 2. Resumo  
O objetivo desse exercício foi, principalmente, nos familiarizar com a ferramenta de simulação de arquiteturas **ArchC**, linguagem que se assemelha muito ao **C**, usado para descrever arquiteturas de hardware. Assim, para começar, foi necessário criar os arquivos necessários para simulação e depois compilá-lo, com os seguintes comandos:  

```
acsim mips.ac -abi
make
```  
Após esse passo, criamos um programa para teste, e compilamos para a arquitetura **MIPS**:  

```
mips-newlib-elf-gcc -specs=archc hello.c -o hello.mips
```  
E a partir desse ponto realizamos a simulação com o seguinte comando:  

```
./mips.x --load=hello.mips
```  

Após nos habituarmos com esses passos, conseguimos analisar número de vezes que cada instrução era executada e também calcular o **CPI Médio** de cada benchmark rodando na arquitetura **MIPS**.  

## 3. Experimento  
Nessa seção, irei descrever e mostrar os resultados dos exercícios propostos.  
### 3.1 Contando instruções 
Esse exercício se baseava em analisar quantas vezes determinadas isntruções eram realizadas.Para isso, usei o código **hello.c** para realizar testes. Esse codigo soma dois números e printa o resultado deles. Após editar também o código presente em **mips_isa.cpp**, para analisar quantas vezes cada parte do código era executada, obtive os seguintes resultados:  


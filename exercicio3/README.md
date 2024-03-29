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
Esse exercício se baseava em analisar quantas vezes determinadas isntruções eram realizadas.Para isso, usei o código **hello.c** para realizar testes. Esse codigo soma dois números e printa o resultado deles. Após editar também o código presente em **mips_isa.cpp** (as funções modificadas foram ac_behaviour(add), ac_behavior(addi), ac_behaviour(addu), ac_behaviour(addiu), ac_behaviour(begin), ac_behaviour(end)), para analisar quantas vezes cada parte do código era executada, obtive os seguintes resultados: 

1. Contador_Add = 674.
2. Contador_Begin = 1.
3. Contador_End = 1.

Após olhar esses resultados, notamos que eles fazem sentido, uma vez que o **begin** e o **end** são executados somente uma vez cada, como o próprio enunciado explicou e as operações de **add** são usadas muitas vezes durante a execução de um simples **hello.c**, já que é necessário computador **saltos** e **escritas no kernel**. 
Além disso, essa parte do experimento pediu para que usássemos o a ferramenta **objdump** para olhar o **assembly** gerado por esse código. Este resultado, gerado pelo comando  

```
mips-newlib-elf-objdump -d hello.mips
```  
está no arquivo **dump.out**, também nesse repositório. Após analisar rapidamente o código gerado, é possível notar várias operações muito conhecidas, como por exemplo:  

- **SW:** operação que copia valores entre registradores.
- **ADDI:** usada para somar o valor de um registrador com algum imediato.
- **JAL:** indica que o programa deve saltar para algum outro ponto do código.  

Agora, analisando o código da função **ac_behavior( add )**, vemos que é extremamente intuitivo descobrir o que ele faz. No caso, ocorre a soma entre dois **registradores**, indexados dentro do **banco de registradores** e seu resultado sendo direcionado para um **registrador destino**. Além disso, ao final é checado se ocorreu ou não **overflow** por meio da análise do **bit de sinal** dos membros envolvidos na operação.  

### 3.2 Avaliando o desempenho 
Nesse trecho do experimento, vamos calcular o **CPI Médio** de alguns programas sugeridos na arquitetura **MIPS**. Seguem os resultados abaixo:  

#### 3.2.1 Hello World
Essa análise diz respeito a saida do simulador quando testado com o código **hello.c**. A saída completa esta no arquivo **saida_hello.txt**, também nesse diretório.  

**CPI Médio = (Total de Ciclos)/(Total de instruções) = 17982/3919 = 4,58**  


#### 3.2.2 Rijndael Coder
Essa análise diz respeito a saida do simulador quando testado com o código **Rijndael Coder**. A saída completa esta no arquivo **saida_rijndael.txt**, também nesse diretório.  

**CPI Médio = (Total de Ciclos)/(Total de instruções) = 43867/9581 = 4,57**

#### 3.2.3 SHA (Large)
Essa análise diz respeito a saida do simulador quando testado com o código **SHA**. A saída completa esta no arquivo **saida_sha.txt**, também nesse diretório. Esta foi a análise que levou mais tempo, já que não estava realizando as análises **small**, como nos outros casos.

**CPI Médio = (Total de Ciclos)/(Total de instruções) = 909786967/137088789 = 6,63**  

## 4. Conclusão
Após realizar esse experimento, fica claro que com a ajuda de alguns softwares de simulação fica muito simples e eficaz comparar desempenho de diversas arquiteturas, podendo ser analisadas métricas como **CPI, tempo e memória**, sendo o critério escolhido de acordo com a finalidade que o usuário necessita. Além disso, podemos ver que os **CPI's Medios** acabam dando valores relativamente próximos. Isso faz certo sentido, já que as tarefas tem instruções bem diversificadas, e a arquitetura analisada é a mesma.





 


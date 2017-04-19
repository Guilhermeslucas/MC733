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

**Mudanças no código mips_isa.cpp:**  

```
void ac_behavior(begin)
 66 {
 67   dbg_printf("@@@ begin behavior @@@\n");
 68   RB[0] = 0;
 69   npc = ac_pc + 4;
 70
 71   // Is is not required by the architecture, but makes debug really easier
 72   for (int regNum = 0; regNum < 32; regNum ++)
 73     RB[regNum] = 0;
 74   hi = 0;
 75   lo = 0;
 76
 77   RB[29] =  AC_RAM_END - 1024 - processors_started++ * DEFAULT_STACK_SIZE;
 78   printf("Contador begin: %d\n", contador_begin + 1);
 79 }  

 void ac_behavior(end)
 83 {
 84   dbg_printf("@@@ end behavior @@@\n");
 85   printf("Contador end: %d\n", contador_end + 1);
 86 }  


 void ac_behavior( addi )
230 {
231   dbg_printf("addi r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
232   RB[rt] = RB[rs] + imm;
233   dbg_printf("Result = %#x\n", RB[rt]);
234   //Test overflow
235   if ( ((RB[rs] & 0x80000000) == (imm & 0x80000000)) &&
236        ((imm & 0x80000000) != (RB[rt] & 0x80000000)) ) {
237     fprintf(stderr, "EXCEPTION(addi): integer overflow.\n"); exit(EXIT_FAILURE);
238   }
239   contador_add++;
240   printf("Contador Add: %d\n", contador_add);
241 };
242
243 //!Instruction addiu behavior method.
244 void ac_behavior( addiu )
245 {
246   dbg_printf("addiu r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
247   RB[rt] = RB[rs] + imm;
248   dbg_printf("Result = %#x\n", RB[rt]);
249   contador_add++;
250   printf("Contador Add: %d\n", contador_add);
251 };  

14 //!Instruction add behavior method.
315 void ac_behavior( add )
316 {
317   dbg_printf("add r%d, r%d, r%d\n", rd, rs, rt);
318   RB[rd] = RB[rs] + RB[rt];
319   dbg_printf("Result = %#x\n", RB[rd]);
320   //Test overflow
321   if ( ((RB[rs] & 0x80000000) == (RB[rd] & 0x80000000)) &&
322        ((RB[rd] & 0x80000000) != (RB[rt] & 0x80000000)) ) {
323     fprintf(stderr, "EXCEPTION(add): integer overflow.\n"); exit(EXIT_FAILURE);
324   }
325   contador_add++;
326   printf("Contador Add: %d\n", contador_add);
327 };  

328
329 //!Instruction addu behavior method.
330 void ac_behavior( addu )
331 {
332   dbg_printf("addu r%d, r%d, r%d\n", rd, rs, rt);
333   RB[rd] = RB[rs] + RB[rt];
334   //cout << "  RS: " << (unsigned int)RB[rs] << " RT: " << (unsigned int)RB[rt] << endl;
335   //cout << "  Result =  " <<  (unsigned int)RB[rd] <<endl;
336   dbg_printf("Result = %#x\n", RB[rd]);
337   contador_add++;
338   printf("Contador Add: %d\n", contador_add);
339 };  






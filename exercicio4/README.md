# Exercício 4
# Nome: Guilherme Lucas da Silva

## 1. Introdução e Objetivo   
Ao decorrer do tempo, computadores deixaram de ser componentes simples e monolíticos para se 
tornarem um grande conjunto de componentes com funções muito específicas que se comunicam por algum
tipo de padrão que deve ter especificações muito rígidas, para que funcione como o esperado. Assim,
o objetivo desse experimento é explorar e analisar o uso de periféricos e a comunicação entre 
eles.

## 2. Experimento   
### 2.1 Primeiros Exercícios e Simulações
A primeira parte do experimento consistiu em realizer um teste de escrita e leitura em uma posição
de memória do periférico e fazer a leitura dessa mesma posição. Esse teste foi realizado com o 
código [first_test.c](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/firt_test.c). 
Esse programa é bem simples, e simplesmente tenta escrever o ***valor 1*** no endereço base do 
periférico.
Porém, após tentar realizar a leitura, esse variável retornou o ***valor 0*** como mostrado abaixo:
```
addr: 4000008, data: 1000000
Lock Value: 0
```

Após analisar o código ```peripheral.cpp```, notei que isso faz realmente sentido, já que a leitura
de uma posição de memória do periférico retorna sempre 0, devido a esse trecho de código:

```
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  *((uint32_t *) &d) = 0;
  return SUCCESS;
}
```
Dito isso, fiz alguma simples mudanças no código ***peripheral.cpp*** para que ele realmente escreva
e leia os valores que eu enviei para ele, realizando o teste ainda com mesmo codigo
[first_test.c](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/firt_test.c). As
modificações que eu fiz foram as seguintes:

***1 - Criação de uma variável global para guardar os valores:***   

```
#include "peripheral.h"

//////////////////////////////////////////////////////////////////////////////

volatile int value;
```   


***2 - Mudança no método de escrita:***   

```
ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d )
{
  value = d;
  cout << "addr: " << std::hex << a << ", data: " << d << endl;
  return SUCCESS;
}
```

***3 - Mudança no método de leitura:***   

```
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  *((uint32_t *) &d) = value;
  return SUCCESS;
}
```

Feitas essas modificações e rodando o mesmo 
[código de teste](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/firt_test.c)
que anteriormente, obtivemos a seguinte resposta:
```
addr: 4000008, data: 1000000
Lock Value: 1
```
Como descrito no código, ***1*** era realmente o valor esperado pelo código.

Agora, implementei o periférico que foi pedido no exercício, que escreve o valor que foi passado 
para ele e quando é solicitada a leitura, muda o valor para 1. Esse codigo ficou bem semelhante ao 
que usamos no exercício anterior. Ele pode ser visto na íntegra no código
[peripheral_lock.cpp](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/peripheral_lock.cpp). 
Porém, as principais mudanças foram essas: 

```
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  aux = value;
  value = 1;
  *((uint32_t *) &d) = aux;
  return SUCCESS;
}
```
Como pode notar, quando acontece a leitura, retornamos o valor que estava nessa posição de memoria
e logo depois setamos o conteúdo pra essa posição como **1**.
A função de escrita continua a mesma do exercício anterior e está descrita 
[aqui](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/peripheral_lock.cpp#L34-L39).

Para testar essa nova funcionalidade, usamos o programa 
[hello_world_lock.c](https://github.com/Guilhermeslucas/MC733/blob/master/exercicio4/hello_world_lock.c). 
Para tornar simples a compreensão do código, os printf's mostram o valor esperado e qual valor esta
realmente armazenado na posição de memoria. Assim, a saída foi:

```
First Lock Value(should be two): 2
Value after reading(should be one):1
addr: 4000008, data: 3000000
Second lock value(should be three):3
Value after reading(should be one):1
```

Assim, fica claro que nossos resultados são exatamente o que estávamos esperando.

### 3.2 Aplicação Multicore
Para realizar um experimento na arquitetura multicore, decidi realizar um programa que soma dois 
vetores posição a posição e armazena esse resultado em um terceiro vetor. Para conseguir fazer essa
aplicação funcionar, tive que realizar as seguintes modificações nos códigos da arquitetura:
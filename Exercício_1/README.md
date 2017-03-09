#Relatório Exercício 1 - Compilação e Otimização
##Nome: Guilherme Lucas da Silva
##RA: 155618

## 1. Introdução
Ao longo dos anos, várias ferramentas foram desenvolvidas para tornar a vida dos desenvolvedores de software mais agradável, entre elas compiladores com muitos truques para otimizar a execução dos códigos e programas que ajudam a localizar e arrumar problemas indesejados, os famosos **depuradores**, como é o caso do **GDB (GNU Debugger)**, que pode ser usado simplesmente digitando o comando ```gdb``` no terminal de sua preferência, após compilar com a flag ```-g```, podendo incluir breakpoints, imprimir as variáveis e ter total controle do estado do software. Como comentado acima **depurar** é o processo de procurar e corrigir erros dentro do código, processo que pode ser muito custoso sem o auxílio dos **depuradores**. Assim, esse exercício tem o objetivo de nos familiarizer com as ferramentas citadas acima.

##2. Resumo
Ao longo desse experimento, foi necessário revisitar algumas tecnicas de compilação, otimização e debug, muito úteis durante o processo de desenvolvimento.

Para automatizar a tarefa de compilar e buildar o programa, também lancei mão do **GNU Make**, que é um software que recebe algumas regras por meio de um **Makefile**. Ao usá-lá, me questionei sobre o porque não usar um **Shell Script** ou até mesmo outra linguagem para esse processo, e cheguei a conclusão de que é muito melhor usar o Make pelos seguintes argumentos:
 
* O **Makefile** toma conta de alterar somente as builds que tiveram os arquivos que as geram modificadas, sendo minimalista e muito mais eficiente, já que não faz sentido compilar novamente algo que não mudou. Isso não acontece com scripts, que, por padrão irá compilar tudo novamente, a menos que o programador tenha algum trabalho para tratar esse problema.
* É possível criar facilmente dependências de arquivos necessários no processo de compilação e diversas regras chamadas por argumento de linha de comando no **Makefile**, o que levaria algumas linhas de codigo a mais para o programador.

Para poder analisar de maneira completa o desempenho do programa, também usamos o gprof para ter algumas informações como, por exemplo, qual parte do código está consumindo mais tempo. Essa é, assim como o gdb, uma ferramenta muito simples de ser usada. Essa pode ser usada digitando ```gprof``` adicionando ```-pg``` ao compilar. Ao usar ferramentas como essas nos questionamos sobre qual a melhor maneira de escrever um programa que tire proveito do gigantesco multiprocesamento de clusters e afins. Assim, podemos usar os avanços dos compiladores, bibliotecas de processamento distribuído e algumas vezes GPU's e hardwares do gênero, com auxílio de programação paralela.

##3. Experimentos e Análise
Nessa parte do relatório, vamos descrever como realizamos os experimentos e quais resultados obtivemos em cada caso. Nas representações abaixo, o tempo que realmente foi  decorrido para o a finalização do processo está na coluna **Real**. Além disse, a coluna **Usuário** diz respeito ao tempo que o programa gastou de CPU no modo de usuário padrão. Diferente de **Sistema**, que é o tempo que o programa gastou no kernel, ou seja, em chamadas de sistema. O Para passar os parâmetros citados em cada item para o compilador basta passar as flags desejadas da seguinte maneira:
```
gcc -parametro1 -parametro2 primo.c -o primo
```
Além disso, usamos o comando ```time``` para obter as informações sobre tempo de execução. Para usá-lo, basta escrever, antes do seu comando desejado, a palavra ```time```.

###3.1 Código original sem nenhuma flag de compilação
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.358s|0.358s|0.000s|

Esse teste e os outros com o código original foram feitos usando o arquivo ```primo.c```.

###3.2 Código original com flags -OX
|Flag|Real|Usuário|Sistema|
|:--:|:--:|:-----:|:-----:|
|-O0|0.355s|0.355s|0.000s|
|-O1|0.335s|0.335s|0.000s|
|-O2|0.365s|0.365s|0.000s|
|-O3|0.372s|0.372s|0.000s|

Após obter e analisar os tempos, notamos que a flag que gerou o melhor desempenho foi a ```-O1```. Somos induzidos a pensar que, quanto maior o número, maior será o desempenho, mas esse é um bom exemplo que não é bem assim. O que acontece é que cada número diz respeito a um tipo de otimização, que pode ser melhor ou pior para o tipo de problema que você está tratando.

###3.3 Código original com flags -mtune
Usando a flag ```-mtune=native```, que seleciona a sua arquitetura e aplica as melhores otimizações para ela especificamente, obtive os seguintes resultados:

| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.355s|0.355s|0.0000s|

Esse resultado se assemelha bastante com o que obtemos com ```-O0```, mas ainda está longe do melhor resultado que obtemos com a flag ```-O1```.

###3.4 Codigo separado em dois arquivos, com flag -O1 e script de compilação
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.330s|0.330s|0.0000s|

Como podemos observar, o resultado entre a compilação via linha de comando com um arquivo só e usando o script de compilação ```compile_script.sh```, com dois arquivos possui tempos muito próximos, não parecendo ser de grande influência as ações citadas. Esse teste o e **3.5** foram feitos com os arquivos ```main.c``` e ```calc_primo.c```.

###3.5 Codigo separado em dois arquivos, com flag -O1 e Makefile
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.333s|0.333s|0.0000s|

O resultado ainda se mantém muito próximo a compilação com script com arquivos separados e pela linha de comando com um arquivo só. Essa era realmente o resultado esperado, já que essas ações não influenciam mudanças no código de máquina final, que é trancrito durante o período de compilação.

###3.6 Código n_primos.c em um único arquivo com flag -O1
Esse experimento cobre o caso do código que busca quantos números primos existem entre 1 e o número dado via linha de comando. Testando com o número **500000**, que será usado em todos os testes referente aos **N_primos** dentro do intervalo, e com flag de compilação 
```-O1``` obtive o seguinte tempo:

| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|31.246s|31.258s|0.004s|

###3.7 Programa N_Primos dois arquivos e flag -O1
Testes feitos com os arquivos ```n_primos_main.c``` e ```calc_primo.c```.

| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|31.718s|31.733s|0.000s|

Como podemos notar, o código para achar quantos números primos existem em um determinado intervalo tem também performances extremamente próximas, como era esperado. Isso acontece porque o compilador linka todas as bibliotecas durante a compilação, para transcrever o codigo de máquina. Tal processo, claramente, não é afetado por separar o código em arquivos.

###3.8 Código N_Primos em dois arquivos e somente percorrendo os ímpares
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|31.814s|31.814s|0.000s|

Ao analisar esses números, achei que estavam errados a princípio, já que os tempos estavam muito próximos. Porém, depois de refletir um pouco sobre o problema, pensei que faz sentido isso acontecer, uma vez que os números pares eram dados como não primos logo na primeira comparação do loop da função que define se o número é primo ou não, processo extremamente rápido. Sendo assim, esses números não causam uma diferença muito grande na soma final dos tempos. Também foram usados os arquivos ```n_primos_main.c``` e calc_primo.c```, sem flags de compilação.

###3.9 Colentando algumas estatísticas com GProf e Paraleizando código
Para que eu pudesse ter uma boa noção onde eu deveria otimizar o código, usei o **GProf**. **Gprof** é um software de profiling, ou seja, da alguns dados e estatísticas sobre seu programa. Utilizá-lo é extremamente simples, uma vez que basta compilar o código com a flag ```-pg```, rodar o executável normalmente e executar o seguinte comando:

```
gprof executavel > stats.txt
```
onde ```executável``` é o compilado do código e ```stats.txt``` é o arquivo com dados sobre seu programa, como onde ele gasta mais tempo.      
Após analisar o arquivo ```run.txt``` notei que a função para identificar se o número é primo é que estava gastando mais tempo, assim tentei paralelizar seu loop principalcom o auxílio da biblioteca **OpenMP**. Essa pode ser facilmente usada para paralelizar loops escrevendo a linha ```#pragma omp parallel for``` logo acima do loop que deseja paralelizar e compilar usando a flag ```-fopenmp```. Porém, encontrei alguns problemas. A função ```primo``` que o professor nos deu, tem valores de retorno no meio do loop, o que nos impede de usar o **OpenMP** nesse trecho sem modificá-lo. A modificação que tentei usar foi usar uma **flag** que quebraria o loop ao notar que o número não é primo. Além disso, essa **flag** seria usada para defifinir se o número era primo ou não, ao terminar o loop. Porém, isso acaba piorando o desempenho do programa, uma vez que todos os números entre **2** e **N** são testados, diferente do que acontecia anteriormente, onde o loop era quebrado assim que era descoberto que o número não era primo. Assim, paralelizei o loop da função `main`, dentro do arquivo ```n_primo_main_paralela.c```. Após compilar com a regra **n_primos_paralelo** do **Makefile** (que conta com a flag ```-fopenmp```) obtive os seguintes resultados, ainda testando com **500000**:

| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|19.943s|49.247s|0.028s|

Como podemos notar, essa foi a versão mais rápido de todas até agora, devido a paralelização. É interessante notar que o tempo de **Usuário** é maior que o **Real**, o que parece estranho. Na verdade, isso acontece pois o tempo de **Usuário** está somando o tempo de cada Thread.

##4. Conclusões
Após realizar todos os testes pedidos pelo professor, notamos que é possível melhorar vertiginosamente o desempenho de um programa com o auxílio do compilador e com mudanças no código, como usar bibliotecas que paralelizam código e achar maneiras de melhorar o algotitimo. Além disso, notamos que para consegui tirar o maior proveito possível de arquiteturas de multiprocessamento devemos tomar cuidado com threads que compartilham regiões na memória, pois isso pode causar assincronia de valores, implicando em resultados errados. Existem algumas bibliotecas de processamento paralelo que auxiliam muito nesses problemas como é o caso do **CUDA**, para **GPU's** e **OpenCL**, para **arquiteturas heterogêneas**. Outra técnica que se mostra muito eficiente, é usar estrututuras de dados em **Matriz** ou **Vetores**, que são muito fáceis de serem paralelizados.

##5. Programa para a competição
Após procurar em muitas fontes sobre bons jeitos de otimizar o código para a competição, cheguei a algumas conclusões. Por isso no meu código final para a competição ```competicao.c```, optei por paralelizar com **OpenMP** e as flags que se mostraram melhor para o meu processador foram as seguintes, usadas na regra ```competicao``` do **Makefile**:

```
-fopenmp -funroll-loops -mcmodel=medium -ftree-vectorize -Wl,q -mtune=native -Ofast -fpeel-loops -flto -lm
```

As flags que estou usando tem as seguintes funções:

* **fopenmp:** flag usada para conseguirmos usar o OpenMP dentro do código, biblioteca esta que paraleliza o loop.
* **funroll-loops:** "desenrola" loops que podem ter seus índices determinados em tempo de compilação.
* **ftree-vectorize:** vetoriza o código automaticamente.
* **Ofast:** Otimização de codigo da familia **OX**.
* **mtune=native:** faz as melhores compilações para a sua arquitetura.
* **fpeel-loops:** também ajuda a "desenrolar" loops em que é possível saber seu tamanho de antemão.

Além disso, fiz algumas modificações na função dos primos que agora só usa divisores primos para ver se um candidato é primo ou não. Assim que essa função encontra um novo primo, ela adiciona no vetor de primos esse novo candidato, parando ao encontrar o n-ésimo. Outra modificação que fiz foi procurar por divisores até a raiz quadrada do candidato, já que acima disso não é possível encontrar um divisor válido, o que ajudou muito no desempenho do programa.
 
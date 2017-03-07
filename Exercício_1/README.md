#Relatório Exercício 1 - Compilação e Otimização
##Nome: Guilherme Lucas da Silva
##RA: 155618

## 1. Introdução
Ao longo dos anos, várias ferramentas foram desenvolvidas para tornarem a vida dos desenvolvedores de software mais agradável, entre elas compiladores com muitos truques para otimizar a execução dos códigos e programas que ajudam a localizar e arrumar problemas indesejados, os famosos depuradores, como é o caso do GDB (GNU Debugger), que pode ser usado simplesmente digitando o comando ```gdb``` no terminal de sua preferência, após compilar com a flag ```-g```, podendo incluir breakpoints, imprimir as variáveis e ter total controle do estado do software. Como comentado acima depurar é o processo de procurar e corrigir erros dentro do código. Assim, esse exercício tem o objetivo de nos familiarizer com as ferramentas citadas acima.

##2. Resumo
Ao longo desse experimento, foi necessário revisitar algumas tecnicas de compilação, otimização e debug, muito úteis durante o processo de desenvolvimento.

Para automatizar a tarefa de compilar e buildar o programa, também lancei mão do GNU Make, que é um software que recebe algumas regras por meio de um Makefile. Ao usá-lá, me questionei sobre o porque não usar um Script em Shell ou até mesmo Python para esse processo, e cheguei a conclusão de que é muito melhor usar o Make pelos seguintes argumentos:
 
* O Makefile toma conta de alterar somente as builds que tiveram os arquivos que as geram modificadas, sendo minimalista e muito mais eficiente, já que não faz sentido compilar novamente algo que não mudou. Isso não acontece com scripts, que, por padrão irá compilar tudo novamente, a menos que o programador tenha algum trabalho para tratar esse problema.
* É possível criar facilmente dependências de arquivos necessários no processo de compilação e diversas regras chamadas por argumento de linha de comando no Makefile, o que levaria algumas linhas de codigo a mais para o programador.

Para poder analisar de maneira completa o desempenho do programa, também usamos o gprof para ter algumas informações como, por exemplo, qual parte do código está consumindo mais tempo. Essa é, assim como o gdb, uma ferramenta muito simples de ser usada. Essa pode ser usada digitando ```gprof``` adicionando ```-pg``` ao compilar. Ao usar ferramentas como essas nos questionamos sobre qual a melhor maneira de escrever um programa que tire proveito do gigantesco multiprocesamento de clusters e afins. Assim, podemos usar os avanços dos compiladores, bibliotecas de processamento distribuído e algumas vezes GPU's e hardwares do gênero, com auxílio de programação paralela.

##3. Experimentos e Análise
Nessa parte do relatório, vamos descrever como realizamos os experimentos e quais resultados obtivemos em cada caso. Nas representações abaixo, o tempo que realmente foi  decorrido para o a finalização do processo está na coluna Real. Para passar os parâmetros desejados para o compilador basta passar as flags desejadas da seguinte maneira:
```
gcc -parametro1 -parametro2 primo.c -o primo
```
Além disso, usamos o comando ```time``` para obter as informações sobre tempo de execução. Para usá-lo, basta escrever, antes do seu comando desejado, a palavra ```time```.

###3.1 Código original sem nenhuma flag de compilação
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.358s|0.358s|0.000s|

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

Como podemos observar, o resultado entre a compilação via linha de comando com um arquivo só e usando o script de compilação ```compile_script.sh```, com dois arquivos possui tempos muito próximos, não parecendo ser de grande influência as ações citadas.

###3.5 Codigo separado em dois arquivos, com flag -O1 e Makefile
| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|0.333s|0.333s|0.0000s|

O resultado ainda se mantém muito próximo a compilação com script com arquivos separados e pela linha de comando com um arquivo só. Essa era realmente o resultado esperado, já que essas ações não influenciam mudanças no código de máquina final, que é trancrito durante o período de compilação.

###3.6 Código N_Primos em um único arquivo com flag -O1
Esse experimento cobre o caso do código que busca quantos números primos existem entre 1 e o número dado via linha de comando. Testando com o número 500000 (usado nos testes anteriores) e com flag de compilação 
```-O1``` obtive o seguinte tempo:

| Real | Usuário | Sistema|
|:----:|:-------:|:------:|
|35.284s|35.246s|0.036s|



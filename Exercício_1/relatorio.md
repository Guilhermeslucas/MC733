#Relatório Exercício 1 - Compilação e Otimização

## 1. Introdução
Ao longo dos anos, várias ferramentas foram desenvolvidas para tornarem a vida dos desenvolvedores de software mais agradável, entre elas compiladores com muitos truques para otimizar a execução dos códigos e programas que ajudam a localizar e arrumar problemas indesejados, os famosos depuradores, como é o caso do GDB (GNU Debugger), que pode ser usado simplesmente digitando o comando ```gdb``` no terminal de sua preferência, após compilar com a flag ```-g```, podendo incluir breakpoints, imprimir as variáveis e ter total controle do estado do software. Como comentado acima depurar é o processo de procurar e corrigir erros dentro do código. Assim, esse exercício tem o objetivo de nos familiarizer com as ferramentas citadas acima.

##2. Resumo
Ao longo desse experimento, foi necessário revisitar algumas tecnicas de compilação, otimização e debug, muito úteis durante o processo de desenvolvimento. Ao relembrar essas tecnicas, usei alguns parâmetros no compilador da seguinte maneira:
```
gcc -parametro1 --parametro2 code.c -o code.out
```
-------------------------- Decidir quais são importantes pro meu processador -------------

Para automatizar a tarefa de compilar e buildar o programa, também lancei mão do GNU Make, que é um software que recebe algumas regras por meio de um Makefile. Ao usá-lá, me questionei sobre o porque não usar um Script em Shell ou até mesmo Python para esse processo, e cheguei a conclusão de que é muito melhor usar o Make pelos seguintes argumentos:
 
* O Makefile toma conta de alterar somente as builds que tiveram os arquivos que as geram modificadas, sendo minimalista e muito mais eficiente, já que não faz sentido compilar novamente algo que não mudou. Isso não acontece com scripts, que, por padrão irá compilar tudo novamente, a menos que o programador tenha algum trabalho para tratar esse problema.
* É possível criar facilmente dependências de arquivos necessários no processo de compilação e diversas regras chamadas por argumento de linha de comando no Makefile, o que levaria algumas linhas de codigo a mais para o programador.

Para poder analisar de maneira completa o desempenho do programa, também usamos o gprof para ter algumas informações como, por exemplo, qual parte do código está consumindo mais tempo. Essa é, assim como o gdb, uma ferramenta muito simples de ser usada. Essa pode ser usada digitando ```gprof``` adicionando ```-pg``` ao compilar. Ao usar ferramentas como essas nos questionamos sobre qual a melhor maneira de escrever um programa que tire proveito do gigantesco multiprocesamento de clusters e afins. Assim, podemos usar os avanços dos compiladores, bibliotecas de processamento distribuído e algumas vezes GPU's e hardwares do gênero, com auxílio de programação paralela.

##3. Experimentos
Nessa parte do relatório, vamos descrever como realizamos os experimentos e quais resultados obtivemos em cada caso.
####3.1 Programa original sem nenhuma flag de compilação

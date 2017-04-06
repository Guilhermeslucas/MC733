# Exercício 2 - Configuração de Cache
## Nome: Guilherme Lucas da Silva
## RA: 155618

## 1. Introdução  
Desde a criação dos primeiros computadores anos atrás, existe uma gigantesca competição para definir qual desses é o mais eficiente, rápido ou potente. Para alcançar esse objetivo, muitas técnicas diferentes foram desenvolvidas, entre elas paralelização de código em arquiteturas multiprocessadas, processadores mais rápido, compiladores com várias features e melhoria nas memórias. Nessa ultima categoria, além do desenvolvimento de memórias com acesso e escrita cada vez mais rápidas, foram criadas as memorias cache, memórias que ficam extremamente próximas do processador, resultando em um acesso extremamente rápido. Após o advento desse tipo de memória, começaram a estudar maneiras de deixá-las ainda melhores. Entre as alterações que podem ser feitas são, tamanho total da cache, tamanho de cada bloco de memória e associatividade, que é basicamente uma função que mapeia cada dado na memória. Dito isso, esse experimento procura realizar vários testes em caches com diferentes características, para que possamos concluir qual a melhor combinação de atributos.

## 2. Resumo
Para realizar esse exercício, o primeiro passo foi instalar o **DineroIV**, com as informções dadas pelo professor na página do exercício. Depois disso, escrevi o script **cache_size.sh** que testa, para os quatro programas escolhidos **(crafty_f2b, gcc_f2b, gzip_f2b, mcf_f2b)**, tamanhos de cache entre **8k** e **64k**, para podermos analisar qual o tamanho da o melhor "custo-beneficio". Depois disso, fixamos o melhor tamanho e começamos a variar associatividade e tamanho de bloco, também por meio do script, conseguindo assim plotar gráficos e mostrar dados importantes sobre desempenho para cada configuração de cache.

## 3. Procedimento
Após instalar o **DineroIV** com as instruções que estavam na página do exercício, usei o script **cache_size.sh** para encontrar o tamanho que me dava o melhor "tamanho-benefício".   

# Parte 3 - Relatório de Desempenho
## Nome: Guilherme Lucas da Silva
## RA: 155618

## 1. Introdução
Conseguir distinguir dispositivos computacionais pelos seus desempenhos é extreamente importante hoje em dia, uma vez que estamos submetidos a um ritmo que exige produção de altíssima qualidade o mais rápido possível, como a máxima contemporânea diz: "tempo é dinheiro". Dessa maneira, a busca por métodos que avaliem de maneira precisa o quão boas são essas máquinas é incessante.  
Após realizar uma série de benchmarks com diferentes máquinas possuímos em mãos uma infinidade de dados que nos permitem criar uma maneira para avaliar essas máquinas, procurando classificá-las.  

## 2. Resumo  
Ao longo desse experimento, escolheremos uma maneira de rankear as máquinas de acordo com os resultados obtidos nos passos anteriores. Para fazer isso da melhor maneira, lancei um olhar crítico sobre os resultados na planilha e descartei alguns dados, por serem esdrúxulos, programas usados para benchmark com poucos dados e projetos que não aprentavam dados sufiecientes, somente mostrando a pontuação final, por exemplo.

## 3. Procedimentos
O primeiro passo para analisar as máquinas descritas foi observar as planilhas de dados de cada programa para decidir se alguns deles não seriam avaliados. No fim das contas, além dos programas que o professor desclassicou, decidi não usar os listados abaixo:   
- **NAS Parallel (10):** poucas medidas.  
- **AES Crypto (12):** também foram executadas poucas medidas.  
- **Sorting (16):** usava somente dados baseados no tempo, gerando o score final a partir disso.  
- **AES with CBC (18):** também possui poucas medidas realizadas.  
- **FFTW (19):** somente três medidas foram feitas.  

Além disso, tive que olhar para cada benchmark e analisar o que as notas altas representavam, ou seja, listar quando altas notas representavam um melhor ou pior desempenho. Porém, somente o **GNU GZip** foi diferente nesse aspecto, sendo as maiores notas representando os piores desempenhos.  
Feito isso, notei que teria problema em comparar o desempenho das máquinas, uma vez que as pontuações não eram padronizadas, ou seja, não variavam dentro de um intervalo fixo. Visto isso, tive que padronizar todos os scores, colocando-os em um intervalo de **0** a **100**, fazendo com que o maior de todos eles se tornasse o **100**. Simplificando, cada nova nota **Z(N)** baseada no antigo score **N** é dada pela seguinte fórmula:  
  
**Z(N) = (N/maiorValor)x100**  

Vale ressaltar que **maiorValor** é o maior valor dentro do benchmark que esta sendo analisado no momento.    
Fazendo o método citado acima, é possível definir a pontuação em cada caso, ou seja, analisar de maneira crítica qual computador se da melhor em cada tipo de tarefa. Porém, para obter uma média e conseguirmos estimar qual a melhor máquina de maneira geral, fazemos uma media de nota, por meio da soma das pontuações dos benchmarks que a maquina participou divido pelo número de benchmarks.  
Feito isso, plotamos os gráficos para cada benchmark, ou seja, a pontuação das máquinas participantes para cada programa. Segue abaixo as pontuações calculadas a partir da fórmula mostrada acima e os gŕaficos de cada teste:  

**Benchmark 1 - Gnu Plot**  

| Pontuação | Máquinas |
|-----------|----------|
| 100       | 11       |
| 78        | 7        |
| 28        | 55       |
| 80        | 16       |
| 34        | 21       |
| 70        | 22       |
| 78        | 19       |
| 72        | 35       |
| 22        | 43       |
| 80        | 34       |
| 30        | 40       |
| 76        | 33       |
| 72        | 36       |
| 70        | 26       |
| 70        | 25       |
| 64        | 32       |
| 76        | 52       |
| 90        | 51       |
| 88        | 12       |
| 48        | 31       |

![Gráfico 1](graficos/benchmark1_gnuplot.jpeg)






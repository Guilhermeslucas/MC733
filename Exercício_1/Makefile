primo: main.c calc_primo.c
	gcc -O1 main.c calc_primo.c -o primo.out

n_primo: n_primos_main.c calc_primo.c
	gcc -O1 -pg n_primos_main.c calc_primo.c -o n_primo.out

n_primo_paralelo: n_primos_main_paralela.c calc_primo.c
	gcc -fopenmp n_primos_main_paralela.c calc_primo.c -o n_primo.out

competicao: competicao.c
	gcc -fopenmp -funroll-loops -mcmodel=medium -ftree-vectorize -Wl,-q -mtune=native -Ofast -fpeel-loops -flto competicao.c -o competicao.out -lm

clean: 
	rm -rf *.out

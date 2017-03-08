primo: main.c calc_primo.c
	gcc -O1 main.c calc_primo.c -o primo.out

n_primo: n_primos_main.c calc_primo.c
	gcc -O1 -pg n_primos_main.c calc_primo.c -o n_primo.out

clean: 
	rm -rf *.out

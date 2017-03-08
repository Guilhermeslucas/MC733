#include <stdio.h>
#include <stdlib.h>

unsigned int n_primo(unsigned int n, unsigned int* primos) {
    unsigned int ultimo = 1;
    unsigned int i;
    unsigned int candidato = 3;
    int flag;
    
    primos[0] = 2;
    
    while (ultimo < n) {
        flag = 0;
        for(i = 0; i < ultimo && !flag; i++) {
            if (candidato % i == 0) {
                flag = 1;
                break;
            }
        }
        
        if (flag) {
            primos[ultimo] = candidato;
            candidato = candidato + 2;
            ultimo++;
        }
    }
    return primos[n - 1];
}

int main(int argc, char *argv[]) {
    unsigned int n = atoi(argv[1]);
    unsigned int* primos = malloc(n*sizeof(unsigned int));
    printf("Esse eh o argumento: %d\n", n);
    return 0;
}

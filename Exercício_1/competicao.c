#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int n_primo(unsigned int n, unsigned int* primos) {
    unsigned int ultimo = 1;
    unsigned int i;
    unsigned int candidato = 3;
    int flag;
    
    primos[0] = 2;
    
    while (ultimo < n) {
        flag = 0;
        for(i = 0; i < ultimo && !flag && i <= sqrt(n); i++) {
            if (candidato % primos[i] == 0) {
                flag = 1;
                break;
            }
        }
        
        if (!flag) {
            primos[ultimo] = candidato;
            ultimo++;
        }
        
        candidato = candidato + 2;
    }
    return primos[n - 1];
}

int main(int argc, char *argv[]) {
    unsigned int n = atoi(argv[1]);
    unsigned int* primos = malloc(n*sizeof(unsigned int));
    
    printf("Aqui esta: %d\n",n_primo(n,primos)); 

    return 0;
}

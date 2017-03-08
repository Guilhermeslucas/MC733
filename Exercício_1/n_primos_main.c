#include <stdio.h>
#include<stdlib.h>

int primo(int n);

int main(int argc, char *argv[] ) {
    int i;
    int counter = 1;
    int n = atoi(argv[1]);
    
    if (n == 1) {
        printf("Existem 0 números primos no intervalo dado\n");
        exit(1);
    }
    
    if (n == 2) {
        printf("Existe 1 número primo no intervalo dado\n");
        exit(1);
    }
    for (i = 3; i <= n; i = i + 2) {
        if (primo(i))
            counter++;
    }
    
    printf("Existem %d números primos no intervalo dado\n", counter);
    return 0;
}

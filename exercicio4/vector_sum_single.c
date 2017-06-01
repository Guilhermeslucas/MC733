#include <stdio.h>
#include <stdlib.h>


//volatile int *lock = (int *) 67108872U; 


int main(int argc, char *argv[]){
    int i;
    int a[100];
    int b[100];
    int c[100];

    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = a[i] + b[i];
    }

    printf("Resultado: \n");
    
    for (i = 0; i < 100;i++)
        printf("%d ", c[i]);
    
    exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
}


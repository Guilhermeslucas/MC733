#include <stdio.h>
#include <stdlib.h>


volatile int *lock = (int *) 67108872U; 


int main(int argc, char *argv[]){
    //escrita na variável lock
    *lock = 1;

    printf("Lock Value: %d\n", *lock);
    exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
}


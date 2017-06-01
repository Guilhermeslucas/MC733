#include <stdio.h>
#include <stdlib.h>


volatile int *lock = (int *) 67108872U; 


int main(int argc, char *argv[]){
    //write on lock variable
    *lock = 1;

    printf("Lock Value: %d\n", *lock);
    exit(0); 
    return 0;
}


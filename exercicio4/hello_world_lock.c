#include <stdio.h>
#include <stdlib.h>


volatile int *lock = (int *) 67108872U; 


int main(int argc, char *argv[]){
    //escrita na variável lock
    *lock = 2;

    printf("First Lock Value(should be two): %d\n", *lock);

    printf("Value after reading(should be one):%d\n", *lock>>24);
    
    *lock = 3;

    printf("Second lock value(should be three):%d\n", *lock);

    printf("Value after reading(should be one):%d\n", *lock>>24); 
    
    
    exit(0); // To avoid cross-compiler exit routine
    return 0; // Never executed, just for compatibility
}


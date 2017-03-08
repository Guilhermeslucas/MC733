#include <stdio.h>
#include<stdlib.h>

int primo(int n)
{
  int i;
  for(i = 2; i < n; i ++)
    if (n % i == 0)
      return 0;

  return 1;
}

int main(int argc, char *argv[] ) {
    int i;
    int counter = 0;

    for (i = 2; i <= atoi(argv[1]); i++) {
        if (primo(i))
            counter++;
    }
    
    printf("Existem %d números primos no intervalo dado\n", counter);
    return 0;
}

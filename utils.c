#include <stdlib.h>
#include <time.h>

double rand_percent(){  //returns double [0,1)
    int a=rand();
    int b=rand();
    while(a==b)
        b=rand();
    if(a<b)
        return (double)a/b;
    else
        return (double)b/a;
}
void init_rand(){
    srand(time(NULL));
}
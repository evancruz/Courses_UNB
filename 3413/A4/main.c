#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 

//globals
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//protos
// pthread_create(&avgThread, NULL, getAvg, numInput); 

/*requirements
You do not want extra hydrogen or oxygen elements. Therefore, you must guarantee that the producing threads 
(hydrogen and oxygen) will wait to produce more elements until after the water molecule is created. 
EX: If an oxygen thread produces oxygen when no hydrogen is present, it has to wait
for two hydrogen elements to be produced.
It takes a random amount of time, between 2 and 5 seconds, to create each hydrogen or oxygen element.

When an element is created you are to output what was produced. For example,
We have hydrogen. We have oxygen.

When you have two hydrogen and one oxygen, they are consumed to form water. For example,
     We now have water!

Your program will run for n seconds, where n is specified on the command line (ie. 100 seconds):
./a.out 100
*/
int main (int argc, char const *argv[]) {
    if(argc != 2){
      printf("Please provide 1 argument for the amount of time to run \nExample: ./main 100\n");
      exit(EXIT_FAILURE);
   }
   int runTime = ((int)*argv[1])-48;
   pthread_t * Oxygen;
   pthread_t * Hydrogen;
   pthread_t * Bond;
   //The sranddev() function initializes a seed, using random(4)
   sranddev();
   int random = ((rand()%5)+2) %6;

   
}
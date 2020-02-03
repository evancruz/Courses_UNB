#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

//functions
void produceOxygen();
int getRandomNum();
void produceHydrogen();
void produceWater();

//globals
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool FINISH;
int hydrogen = 0;
int oxygen = 0;
int runTime;
bool oxyFlag;
bool hydFlag;


int main (int argc, char const *argv[]) {
    if(argc != 2){
      printf("Please provide 1 argument for the amount of time to run \nExample: ./main 100\n");
      exit(EXIT_FAILURE);
   }
   //The sranddev() function initializes a seed, using random(4)  
   sranddev(); 
   runTime = atoi(argv[1]);
   oxygen = 0;
   hydrogen = 0;
   oxyFlag = false;
   hydFlag = false;
   pthread_t OxygenT;
   pthread_t HydrogenT;
   pthread_t BondT;


   pthread_create(&OxygenT, NULL, (void *) produceOxygen, NULL);
   pthread_create(&HydrogenT, NULL, (void *) produceHydrogen, NULL);
   pthread_create(&BondT, NULL, (void *) produceWater, NULL);
   pthread_join(OxygenT, NULL);
   pthread_join(HydrogenT, NULL);
   pthread_join(BondT, NULL);
   
}

 
void produceOxygen(){
   int ready = getRandomNum();
   int i = 0;
   while(i  < runTime){
      // printf("oxy i: %d\n", i);
      pthread_mutex_lock(&mutex);
      if(oxygen == 0 && ready <= 0) {
         oxygen++;
         printf("%s\n", "We have oxygen.");
         ready = getRandomNum() + 1;
      }
      pthread_mutex_unlock(&mutex);
      ready--;
      i++;
      sleep(1);
   }
}

void produceHydrogen(){
   int ready = getRandomNum();
   int i = 0;
   while(i  < runTime){
      // printf("hyd i: %d\n", i);
      pthread_mutex_lock(&mutex);
      if(hydrogen < 2 && ready <= 0) {
         hydrogen++;
         printf("%s\n", "We have hydrogen.");
         ready = getRandomNum() + 1;
      }
      pthread_mutex_unlock(&mutex);
      ready--;
      i++;
      sleep(1);
   }
}

void produceWater(){
   int i = 0;
   while(i  < runTime){
      // printf("water i: %d\n", i);
      pthread_mutex_lock(&mutex);
      if(oxygen == 1 && hydrogen == 2) {
         printf("%s\n", "We have water!");
         oxygen = 0;
         hydrogen = 0;
      }
      pthread_mutex_unlock(&mutex);
      i++;
      sleep(1);
   }
}

int getRandomNum(){
   return ((rand()%5)+2) %6;
}

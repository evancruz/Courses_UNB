
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//functions
void printNums(int * arr, int len);
void * getAvg ();
void * getMin(void * arg);
void * getMax(void * arg);

//globals
int maxValue;
int runningTotal;
int runningAverage;
int minumum;
int totalInput;
int bufferSize = 10000;
int pipe1[2];
int pipe2[2];
int pipe3[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//fgets(input, bufferSize, stdin);

//MAIN
int main (int argc, char const *argv[]) {
   pipe(pipe1);
   pipe(pipe2);
   pipe(pipe3);
   totalInput = 0;
   maxValue = 0;
   runningTotal = 0;
   runningAverage = 0;

   int numRead;
   pthread_t * avgThread;
   pthread_t * minThread;
   pthread_t * maxThread;
   pthread_create(&avgThread, NULL, getAvg, NULL); 
   pthread_create(&minThread, NULL, getMin, NULL); 
   pthread_create(&maxThread, NULL, getMax, NULL);
   while(scanf("%d", &numRead)) {
      if(numRead == 0)
         break;
      totalInput++;
      if(totalInput == 1)
         minumum = numRead;

      write(pipe1[1], &numRead, sizeof(numRead));
      write(pipe2[1], &numRead, sizeof(numRead)); 
      write(pipe3[1], &numRead, sizeof(numRead));  

   }
   pthread_join(avgThread, NULL);
   pthread_join(minThread, NULL);
   pthread_join(maxThread, NULL);
   printf("The average value is %d ", runningAverage);
   printf("The minimum value is %d ", minumum);
   printf(" The maximum value is %d", maxValue);
  

   //The average value is 82 The minimum value is 72 The maximum value is 95
   // printNums(numbers, numInput);

}//end main

void * getAvg (){
   int temp;
   read(pipe1[0], &temp, sizeof(temp));
   runningTotal += temp;
   runningAverage = runningTotal/totalInput;
}
void * getMin(void * arg){
   int temp;
   read(pipe2[0], &temp, sizeof(temp));
   if(temp < minumum)
      minumum = temp;
}

void * getMax(void * arg){
   int temp;
   read(pipe3[0], &temp, sizeof(temp));
   if(temp > maxValue)
      maxValue = temp;
}

void printNums(int * arr, int len){
   int i = 0;
   while(i < len){
      printf("%d\t", arr[i]);
      i++;
   }
}


//   printf("rt: %d\n", runningTotal);
//  printf("totalIn: %d  runningTotal: %d rt/totalIn %d  \n", totalInput, runningTotal, (float)(runningTotal/totalInput));
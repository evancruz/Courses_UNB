#include <stdio.h>
#include <stdlib.h>
 #include <pthread.h>

 /*
 Create a global int variable (initialized to 0) that should be incremented by 1 (100 times) by one child process while the 
 second child process does the same, but decrements the same variable. 
 Have the parent of the children wait for the two children to complete and then print the value of the variable.*/

void incrementGlobal();
void decrementGlobal();


 int globalVar = 0;
 
int main (int argc, char const *argv[]) {
   pthread_t thread1,  thread2;

  pthread_create(&thread1, NULL, (void *) incrementGlobal, NULL);
  pthread_create(&thread2, NULL,  (void *) decrementGlobal, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Global Var:  %d\n", globalVar);
  
}

void incrementGlobal(){
   for(int i = 0; i < 100; i ++){
      globalVar++;
   }
}

void decrementGlobal(){
   for(int i = 0; i < 100; i ++){
      globalVar--;
   }
}


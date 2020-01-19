#include <stdio.h>
#include <stdlib.h>
 #include <stdbool.h>

bool isDone(int A);
int main (int argc, char const *argv[]) {
   bool ret = isDone(2);
   printf("%d\n", ret);
   printf("true: %d\n", true);
   printf("false: %d\n", false);



   
   
}


bool isDone(int A){
   if(A == 2) 
      return true;
   else
      return false;
}


/*
        while(node){
           if(node->cycle == periodLength){
               //move to back
               printf("node and cycle: %s %d\n", node->process, node->cycle);
               //passing in head when time == 4. headRL should be A. but then should be called again to move A to back
               //node and cycle should be printed a total of 4 times because they've both used up 2 cycles
               headRL = moveToBack(node, headRL);
               printf("node and cycle: %s %d\n", headRL->process, headRL->cycle);
               node->cycle = 0;
            }
            node = node->next;
        }
*/
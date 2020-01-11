#include <stdio.h>
#include <stdlib.h>
 
 /*LISTS*/

struct JobList{
   char *user[100];
   char *process[100];
   int arrival;
   int duration;
   struct JobList *next;
};
struct RunList{
   char *user[100];
   char *process[100];
   int arrival;
   int duration;
   struct RunList *next;
};
struct JobList* getJobRequests();
void printJobList(struct JobList *head);



 /*
 * as jobs arrive they are added to the run list. Jobs in the run list are then each given a fixed period of time to run on the processor. 
 * If the job is not finished its execution when the time is up, then it goes back into the run list to wait for another turn to continue execution. 
 * If two jobs arrive at the same time, then the job with the shortest duration goes first in the run list.
 *  To implement pre-emption, you only execute a job for up to the fixed period and then you add it back into the run list.
*/

/* 
 * grab all jobs -> into JOB REQUESTS
 * DO 
 * LOOP tick time
 * check for new job request (by checking arrival time. If arrival time == time add to list
 *                                                                                     IF multiple add shortest duration first
 * run job at front of list for 2 periods
 * if  duration == 0 then remove from run list
 * else add to BACK of list 
 * WHILE JOB REQUESTS IS NOT EMPTY
*/

int MAXSIZE = 1000;
int main (int argc, char const *argv[]) {
   if(argc != 2){
      printf("Please provide one and only one argument. \nExample: ./a.out 2\n");
      exit(EXIT_FAILURE);
   }
   
   struct JobList *headJL = getJobRequests();

   int time = 0;
   do{
      
      if(getNextJob(time)){

      }
      
      time++;
      //make a function to delete a node and then return a pointer to head node
   }while(headJL);

   //FREE ALL MEMORY
   //WILL NEED TO CHANGE FOR WHEN DURATION = 0;
   struct JobList *freeList = headJL;
   freeList = head;
   while(freeList){
      freeList = freeList->next;
      free(head);
      head = freeList;
   }

}//end main




//FUNCTIONS!!
  struct JobList* getJobRequests(){
     //skips over the first line
   char buffer[MAXSIZE];
   //what happens if file is empty?
   fgets(buffer, MAXSIZE, stdin);

   struct JobList *head = NULL;
   while(fgets(buffer, MAXSIZE, stdin)){
      if(head == NULL){
         struct JobList *newJob = malloc(sizeof(struct JobList));
         if (newJob == NULL){
            printf("allocation failed\n");
            return NULL;
         }
         sscanf(buffer, "%s %s %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration));
         newJob->next = NULL;
         head = newJob;
      } else{
         //there is at least one job. add new job to back
         struct JobList *ptr = head;
         while(ptr->next){
            ptr = ptr->next;
         }
         //allocate memory for job
         struct JobList *newJob = malloc(sizeof(struct JobList));
         sscanf(buffer, "%s %s %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration));
         newJob->next = NULL;
         ptr->next = newJob;
      }
   }
   return head;
}

void printJobList(struct JobList *head){
   while(head){
      printf("%s %s %d %d\n", head->user, head->process, head->arrival, head->duration);
      head = head->next;
   }
}




//EXTRA NOTES

/*
User	Process	Arrival	Duration
Jim	A	2	5
Mary	B	2	3
Sue	D	5	5
Mary	C	6	2
*/

/* MAKEFILE
> outputTest.txt && diff outputTest.txt input1.txt > diff.txt 
*/
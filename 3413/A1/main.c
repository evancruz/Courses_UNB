#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


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

 /*LISTS*/
struct JobList{
   char *user[100];
   char *process[100];
   int arrival;
   int duration;
   struct JobList *next;
};

//FunctionDeclarations
void getJobRequests();
void printJobList(struct JobList *head);
struct JobList * nextJobRequest(int time);
struct JobList * removeJob(struct JobList *node, struct JobList *head);
void addToRunList(struct JobList *node);
void sortRunList(struct JobList *job, int time);
void insertFront(struct JobList *job, struct JobList *head);
void insertBehind(struct JobList *node, struct JobList *node2);

//constants and globals
struct JobList *headJL = NULL;
struct JobList *headRL = NULL;


/***************************************************************
 * MAIN                                                                                        *
 *                                                                                                 *
 * **************************************************************
*/
int main (int argc, char const *argv[]) {
   if(argc != 2){
      printf("Please provide one and only one argument. \nExample: ./a.out 2\n");
      exit(EXIT_FAILURE);
   }

   //fill JobList. HeadJL points to it
   getJobRequests();
   int time = 0;
   int maxCycle = (int)(argv[1]);
   int maxTurns = maxCycle;
   while(time!= 16){
      printf("cycle %d\n", time);
      
      struct JobList * job;
      if(headJL){
         //returns jl node
         while( job = nextJobRequest(time)){
            printf("new job: %s\n", job->process);
            sortRunList(job, time);
            headJL = removeJob(job, headJL);
            struct JobList* ptr = headJL;
            if(!headJL)
               break;
         }
         printf("printing run list\n");
         printJobList(headRL);
         printf("\n");
         
         //do a cycle on run list
 
         }
         time++;
      }
      


   struct JobList *temp = headRL;
   while(headRL){
      temp = headRL->next;
      free(headRL);
      headRL = temp;
   }
   
}//end main













void getJobRequests(){
   int max = 1000;
     //skips over the first line
   char buffer[max];
   //what happens if file is empty?
   fgets(buffer, max, stdin);

   while(fgets(buffer, max, stdin)){
      if(headJL == NULL){
         struct JobList *newJob = malloc(sizeof(struct JobList));
         sscanf(buffer, "%s %s %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration));
         newJob->next = NULL;
         headJL = newJob;
      } else{
         //there is at least one job. add new job to back
         struct JobList *ptr = headJL;
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
}

void printJobList(struct JobList *head){
   if(head == NULL){
      printf("NULL\n");
   } else {
      printf("\t*Printing JobList from %s:\t*\n", head->process);
      while(head){
         printf("%s %s %d %d\n", head->user, head->process, head->arrival, head->duration);
         head = head->next;
      }
   }
}

struct JobList * nextJobRequest(int time){
   printf("getting next request\n");
   printf("headJL and next %s %s:\n", headJL-> process, headJL->next);
   struct JobList *ptrJL = headJL;
   while(ptrJL){
      if(ptrJL->arrival == time){
         return ptrJL;
      }
      ptrJL = ptrJL->next;
   }
   printf("no job returning\n");
   
   return NULL;
}

struct JobList * removeJob(struct JobList *node, struct JobList *head){
   printf("removing job:  %s where head process:  %s\n", node->process, head->process);

   if(strcmp(node->process,head->process) == 0){
      printf("node: %s      nodenext: %s\n", node->process, node->next);
      head = node->next;
      free(node);
      printf("returning: %s\n", head);
      return head;
   } else {
      printf("node->process %s\n", node->process);
      struct JobList *prev = head;
      struct JobList *current = head->next;
      while(current){
         if(strcmp(node->process, current->process) == 0){
            prev->next = current->next;
            free(current);
            return head;
         }
         prev = current;
         current = current->next;
      }
      return head;
   }
}

// void addToRunList(struct JobList *node){
//    //jobs are added to run list when arrival == time
//    if(headRL == NULL){
//       headRL = malloc(sizeof(struct JobList));
//       strcpy(headRL->user, node->user);
//       strcpy(headRL->process, node->process);
//       headRL->arrival = node->arrival;
//       headRL->duration = node->duration;
//       headRL->next = NULL;
//    } else{
//       struct JobList *ptr = headRL;
//       //add to list then sort after
//       while(ptr->next){
//          ptr = ptr->next;
//       }
//       struct JobList *newJob = malloc(sizeof(struct JobList));
//       strcpy(newJob->user, node->user);
//       strcpy(newJob->process, node->process);
//       newJob->arrival = node->arrival;
//       newJob->duration = node->duration;
//       newJob->next = NULL;
//       ptr->next = newJob;
//    }
// }

//while nxtptr
// while not equal to the time
//if node equals time then do comparison
//if comparison fails go to next node
void sortRunList(struct JobList *job, int time){
   //this runs after every job is added to runlist
   printf("sorting list with jobJL: %s \n", job->process);
   
   if(!headRL){
      insertFront(job, headRL);
   }else{
      struct JobList *node = headRL;
      while(node->next){
         if(node->arrival == job->arrival && node->duration > job->duration){
            insertBehind(node, job);
            return;
         } else {
            node = node->next;
         }
      } //if no node next we are at end
      //make comparison. 
      if(node->arrival == job->arrival && node->duration > job->duration){
            insertBehind(node, job);
         } else {
            insertFront(job, headRL);
         }
   }
}

void insertFront(struct JobList *job, struct JobList *head){
   if(head == NULL){
      struct JobList *runListTask = malloc(sizeof(struct JobList));
      strcpy(runListTask->user, job->user);
      strcpy(runListTask->process, job->process);
      runListTask->arrival = job->arrival;
      runListTask->duration = job->duration;
      runListTask->next = NULL;
      headRL = runListTask;
   } else {
      struct JobList *endOfList = head;
      while(endOfList->next){
         endOfList= endOfList->next;
      }
      struct JobList *runListTask = malloc(sizeof(struct JobList));
      strcpy(runListTask->user, job->user);
      strcpy(runListTask->process, job->process);
      runListTask->arrival = job->arrival;
      runListTask->duration = job->duration;
      runListTask->next = NULL;
      endOfList->next = runListTask;
   }
   
}

void insertBehind(struct JobList *node, struct JobList *node2){
   //node is RL. node2 is JL job
   printf("inserting node %s behind node %s\n", node2->process, node->process);
   //case 1 behind head
   //case 2 after head (middle element)

   struct JobList *runListTask = malloc(sizeof(struct JobList));
   strcpy(runListTask->user, node2->user);
   strcpy(runListTask->process, node2->process);
   runListTask->arrival = node2->arrival;
   runListTask->duration = node2->duration;

   if(strcmp(node->process, headRL->process)==0){
      printf("here6\n");
      runListTask->next = node;
      headRL = runListTask;
   } else {
      printf("here7\n");
      struct JobList *ptr = headRL;
      while(ptr->next != node){
         ptr=ptr->next;
      }
      ptr->next = runListTask;
      runListTask->next = node;
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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


 /*LISTS*/
struct JobList{
   char *user[100];
   char *process[100];
   int arrival;
   int duration;
   struct JobList *next;
};

struct User{
   char *user[100];
   int finishTime;
   struct User *next;
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
void nextTask();
void createUser(char * user);
void recordFinish(char * userName, int time);

//constants and globals
struct JobList *headJL = NULL;
struct JobList *headRL = NULL;
struct User *headUser = NULL;


/***************************************************************
 * MAIN                                                                                        *
 *                                                                                                 *
 * *************************************************************/

int main (int argc, char const *argv[]) {
   if(argc != 2){
      printf("Please provide one and only one argument. \nExample: ./a.out 2\n");
      exit(EXIT_FAILURE);
   }


   //fill JobList. HeadJL points to it
   getJobRequests();


   printf("Time\tJob\n");
   //start cpu time
   int time = 0;
   int maxCycle = ((int)*argv[1])-48;
   int maxTurns = maxCycle;
   while(headRL || headJL){
         struct JobList * job;

         if(headJL){
            while(job = nextJobRequest(time)){
               sortRunList(job, time);
               headJL = removeJob(job, headJL);
               struct JobList* ptr = headJL;
               if(!headJL)
                  break;
            }
         }         

      //give cpu to first in list
      if(headRL){
         /*free and move to next task
         * record finish time
         */
         if(headRL->duration == 0){
            recordFinish(headRL->user, time);
            nextTask();
            maxTurns = maxCycle;
            if(!headRL){
               break;
            }
         }else {
            if(!maxTurns){
               //move next task up front
               nextTask();
               maxTurns = maxCycle;
            }
         }
         printf("%d\t%s\n", time, headRL->process);
         headRL->duration--;
         maxTurns--;
      }
      
      time++;
   }
   printf("%d\tIDLE\n\n", time);
   printf("Summary\n");
   struct User * node = headUser;
   while(node){
      printf("%s\t%d\n", node->user, node->finishTime);
      node = node->next;
   }

   //free Users
   node = headUser;
   while(node){
      node = node->next;
      free(headUser);
      headUser = node;
   }
   
   
}//end main




/***************************************************************
 * Functions                                                                                  *
 *                                                                                                 *
 * *************************************************************/


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
      while(head){
         printf("%s %s %d %d\n", head->user, head->process, head->arrival, head->duration);
         head = head->next;
      }
   }
}

struct JobList * nextJobRequest(int time){
   struct JobList *ptrJL = headJL;
   while(ptrJL){
      if(ptrJL->arrival == time){
         return ptrJL;
      }
      ptrJL = ptrJL->next;
   }
   return NULL;
}

struct JobList * removeJob(struct JobList *node, struct JobList *head){
   if(strcmp(node->process,head->process) == 0){
      head = node->next;
      free(node);
      return head;
   } else {
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

void sortRunList(struct JobList *job, int time){
   //this runs after every job is added to runlist
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
   struct JobList *runListTask = malloc(sizeof(struct JobList));
   strcpy(runListTask->user, job->user);
   strcpy(runListTask->process, job->process);
   runListTask->arrival = job->arrival;
   runListTask->duration = job->duration;
   runListTask->next = NULL;
   if(head == NULL){
      headRL = runListTask;
   } else {
      struct JobList *endOfList = head;
      while(endOfList->next){
         endOfList= endOfList->next;
      }
      endOfList->next = runListTask;
   }
   createUser(runListTask->user);
}

/*
*   node is RL. node2 is JL job
*   case 1 behind head
*   case 2 after head (middle node)
*/
void insertBehind(struct JobList *node, struct JobList *node2){

   struct JobList *runListTask = malloc(sizeof(struct JobList));
   strcpy(runListTask->user, node2->user);
   strcpy(runListTask->process, node2->process);
   runListTask->arrival = node2->arrival;
   runListTask->duration = node2->duration;

   if(strcmp(node->process, headRL->process)==0){
      runListTask->next = node;
      headRL = runListTask;
      
   } else {
      struct JobList *ptr = headRL;
      while(ptr->next != node){
         ptr=ptr->next;
      }
      ptr->next = runListTask;
      runListTask->next = node;
   }
   createUser(runListTask->user);
}

//move task to the back and bring the next one in line to the front
void nextTask(){
   if(headRL->duration == 0){
      struct JobList *nextJob = headRL->next;
      free(headRL);
      headRL = nextJob;
   } else {
      struct JobList *eofList = headRL->next;
      //only 1 in run list
      if(eofList == NULL){
         return;
      } else {
         //get to end
         while(eofList->next){
            eofList = eofList->next;
         }
         //ensure headRL points to first node
         struct JobList *nextJob = headRL->next;
         eofList->next = headRL;
         headRL->next = NULL;
         headRL = nextJob;
      }
   }
}

void createUser(char * name){
   if(!headUser){
      headUser = malloc(sizeof(struct User));
      strcpy(headUser->user, name);
      headUser->next = NULL;
   } else {
      struct User *node = headUser;
      while(node->next){
         if(strcmp(node->user, name) ==0){
            return;
         }
         node = node->next;
      }
      if(strcmp(node->user, name)==0){
            return;
      } else {
         struct User *newUser = malloc(sizeof(struct User));
         node->next = newUser;
         strcpy(newUser->user, name);
         newUser->next = NULL;
      }
   }
}

void recordFinish(char * userName, int time){
   struct User *node= headUser;
   while(node){
      if(strcmp(node->user, userName) == 0){
         node->finishTime = time;
         return;
      }
      node = node->next;
   }
}
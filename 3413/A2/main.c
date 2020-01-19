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
   int priority;
   struct JobList *next;
};

struct User{
   char *user[100];
   int completedTime;
   struct User *next;
};

//FunctionDeclarations
void getJobRequests();
void printJobList(struct JobList *head);
struct JobList * nextJobRequest(int time);
struct JobList * removeJob(struct JobList *node, struct JobList *head);
void addToRunList(struct JobList *node);
void insertRunList(struct JobList *job, int time);
void insertFront(struct JobList *job, struct JobList *head);
void insertBehind(struct JobList *node, struct JobList *node2);
void nextTask();
bool isDone(struct JobList *node);
struct JobList * moveToBack(struct JobList *node, struct JobList *head);
void createUser(char * user);
void recordFinish(char * userName, int time);
bool isSameNode(struct JobList *node1, struct JobList *node2);

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
      printf("Please provide 1 argument for the amount of CPU's \nExample: ./main 3\n");
      exit(EXIT_FAILURE);
   }
   int const cores = ((int)*argv[1])-48;
   int numCPU;

   //fill JobList. HeadJL points to it
   getJobRequests();

   //Print Titles
   printf("Time\t");
   for(numCPU = 1; numCPU <= cores; numCPU++){
      printf("CPU%d\t", numCPU);
   }
   printf("\n");

   /*Start cpu time
   *Run until both both Run List and Job List are empty */

   int time = 0;
   while(headRL || headJL){
         struct JobList * job;

         /*if there are still jobs left in JL then check for a job request
         * Insert job requests into the Run List (RL)*/
         if(headJL){
            while(job = nextJobRequest(time)){
               //insert to RunList based on criteria. Remove from JL
               insertRunList(job, time);
               headJL = removeJob(job, headJL);
               if(!headJL)
                  break;
            }
         }         

      if(headRL){
         struct JobList *runPtr = headRL;
         while(runPtr){
            if(isDone(runPtr)){
               struct JobList * node = runPtr;
               runPtr = runPtr->next;
               recordFinish(node->user, time);
               headRL = removeJob(node, headRL);
               //if nothing to run at the moment then break and see if there are more job requests
               if(!headRL){
                  if(!headJL)
                     goto END;
                  printf("%d\t%s\n", time, "IDLE");
                  goto NEXTREQUEST;
               }
            } else {
               runPtr = runPtr->next;
            }
         }

        struct JobList * node = headRL;

         //run through a cycle
         node = headRL;
         // printJobList(headRL);
         printf("%d\t", time);
         for(numCPU = 1; numCPU <= cores; numCPU++){
            if(node){
               printf("%s\t", node->process);
               node->duration--;
               node = node->next;
            } else {
               printf("-\t");
            }
         }
         printf("\n");
        
      }//go to next cpu cycle

      NEXTREQUEST:
      time++;
   }//end run time
   END:
   printf("%d\tIDLE\n\n", time);
   printf("Summary\n");
   struct User * node = headUser;
   while(node){
      printf("%s\t%d\n", node->user, node->completedTime);
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
         sscanf(buffer, "%s %s %d %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration), &(newJob->priority));
         newJob->next = NULL;
         headJL = newJob;
      } else{
         //there is at least one job. add new job to back
         struct JobList *node = headJL;
         while(node->next){
            node = node->next;
         }
         //allocate memory for job
         struct JobList *newJob = malloc(sizeof(struct JobList));
         sscanf(buffer, "%s %s %d %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration), &(newJob->priority));
         newJob->next = NULL;
         node->next = newJob;
      }
   }
}

void printJobList(struct JobList *head){
   if(head == NULL){
      printf("NULL\n");
   } else {
      while(head){
         printf("%s %s %d %d\n", head->user, head->process, head->arrival, head->duration, head->priority);
         head = head->next;
      }
   }
   printf("done print\n");
}

struct JobList * nextJobRequest(int time) { 
   struct JobList *nodeJL = headJL;
   while(nodeJL){
      if(nodeJL->arrival == time){
         return nodeJL;
      }
      nodeJL = nodeJL->next;
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
      //if it reaches here then it means no job was removed
      return head;
   }
}

//this runs after every job is added to runlist
void insertRunList(struct JobList *job, int time){
   if(!headRL){
      insertFront(headRL, job);
      return;
   } else{
      struct JobList *node = headRL;
      while(node->next){
         if(node->priority > job->priority){
            insertFront(node, job);
            return;
         }
         if((node->priority == job->priority) && (node->duration > job->duration)){
            insertFront(node, job);
            return;
         }
         if(node->duration == job->duration && (node->arrival > job->arrival)){
            insertFront(node, job);
            return;
         }
         node = node->next;
      } 
      //we are at end node. make comparison
      if(node->priority > job->priority){
         insertFront(node, job);
         return;
      }
      if((node->priority == job->priority) && (node->duration > job->duration)){
         insertFront(node, job);
         return;
      }
      if(node->duration == job->duration && (node->arrival > job->arrival)){
         insertFront(node, job);
         return;
      }
      insertBehind(node, job);
   }
}

void insertFront(struct JobList *node, struct JobList *job) {
   struct JobList *runListTask = malloc(sizeof(struct JobList));
   strcpy(runListTask->user, job->user);
   strcpy(runListTask->process, job->process);
   runListTask->arrival = job->arrival;
   runListTask->duration = job->duration;
   runListTask->priority = job->priority;
   if(headRL == NULL){
      headRL = runListTask;
      runListTask->next = NULL;
   } else {
      if(isSameNode(node, headRL)){
         runListTask->next = node;
         headRL = runListTask;
      } else {
         struct JobList * previousToNode = headRL;
         while(previousToNode->next){
            if(isSameNode(previousToNode->next, node)){
               previousToNode->next = runListTask;
               runListTask->next = node;
               break;
            }
            previousToNode = previousToNode->next;
         }
      }
   }
    createUser(runListTask->user);
}

//only gets run if there is at least 1 in RL
void insertBehind(struct JobList *node, struct JobList *job){
   struct JobList *runListTask = malloc(sizeof(struct JobList));
   strcpy(runListTask->user, job->user);
   strcpy(runListTask->process, job->process);
   runListTask->arrival = job->arrival;
   runListTask->duration = job->duration;
   runListTask->priority = job->priority;
   runListTask->next = NULL;

   node->next = runListTask;
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


bool isDone(struct JobList *node){
   if(node->duration == 0) 
      return true;
   else
      return false;
}

struct JobList * moveToBack(struct JobList *node, struct JobList *head){
   //already at back
   if(node->next == NULL)
      return head;
   //go through to back of list
   struct JobList * eoList = head;
   while(eoList->next){
      eoList = eoList->next;
   }
   if(isSameNode(node, head)){
      eoList->next = node;
      head = node->next;
      node->next = NULL;
      return head;
   } else {
      //node is not at back nor is it the head
     struct JobList * previousToNode = head;
     while(previousToNode->next){
        if(isSameNode(previousToNode->next, node)){
           break;
        }
        previousToNode = previousToNode->next;
     }
     previousToNode->next = node->next;
     eoList->next = node;
     node->next = NULL;
   }
}

bool isSameNode(struct JobList *node1, struct JobList *node2){
   if(strcmp(node1->process, node2->process)==0)
      return true;
   else
      return false;
}

void recordFinish(char * userName, int time){
   struct User *node= headUser;
   while(node){
      if(strcmp(node->user, userName) == 0){
         node->completedTime = time;
         return;
      }
      node = node->next;
   }
}

void createUser(char * name){
   struct User *newUser = malloc(sizeof(struct User));
   if(!headUser){
      headUser = newUser;
      strcpy(headUser->user, name);
      headUser->next = NULL;
   } else {
      struct User *node = headUser;
      while(node->next){
         if(strcmp(node->user, name) ==0){
            free(newUser);
            return;
         }
         node = node->next;
      }
      if(strcmp(node->user, name)==0){
            free(newUser);
            return;
      } else {
         node->next = newUser;
         strcpy(newUser->user, name);
         newUser->next = NULL;
      }
   }
}
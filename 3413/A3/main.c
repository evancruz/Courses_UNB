#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

 /*LISTS*/
struct Task{
   char *user[100];
   char *process[100];
   int arrival;
   int duration;
   int deadline;
   struct Task *next;
};

struct User{
   char *user[100];
   int completedTime;
   struct User *next;
};



//FunctionDeclarations
void printList(struct Task *head);
void getJobRequests();
struct Task * nextJobRequest(int time);
struct Task * removeJob(struct Task *node, struct Task *head);
void insertRunList(struct Task *job, int time);
void insertFront(struct Task *job, struct Task *head);
void insertBehind(struct Task *node, struct Task *node2);
void nextTask();
bool isDone(struct Task *node);
void createUser(char * user);
struct Task * moveToBack(struct Task *node, struct Task *head);
bool isSameNode(struct Task *node1, struct Task *node2);
void recordFinish(char * userName, int time);
void * processJob (struct Task *node);

//constants and globals
struct Task *JobList = NULL;
struct Task *RunList = NULL;
struct User *headUser = NULL;
int missedDeadlines = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

   //fill Task. JobList points to it
   getJobRequests();
   //Print Titles
   printf("Time\t");
   for(numCPU = 1; numCPU <= cores; numCPU++){
      printf("CPU%d\t", numCPU);
   }
   printf("\n");

   //make an array of pthreads equal to number of CPU's
   pthread_t * pthreadPtr = malloc(sizeof(pthread_t) * numCPU);



   /****************
    * Start cpu time
   *Run until both both Run List and Job List are empty */
   int time = 0;
   while(RunList || JobList){
         struct Task * job;

         /*if there are still jobs left in JL then check for a job request
         * Insert job requests into the Run List (RL)*/
         if(JobList){
            while(job = nextJobRequest(time)){
               //insert to RunList based on criteria. Remove from JL
               insertRunList(job, time);
               JobList = removeJob(job, JobList);
               if(!JobList)
                  break;
            }
         }         
      
      if(RunList){
         struct Task *runPtr = RunList;
         while(runPtr){
            if(isDone(runPtr)){
               struct Task * node = runPtr;
               runPtr = runPtr->next;
               recordFinish(node->user, time);
               //check for deadline completion. if not completed, then add to missed deadlines variable
               if(node->deadline < time){
                  missedDeadlines++;
               }
               RunList = removeJob(node, RunList);
               //if RL is empty and there are no more jobs that may arrive then go to END
               // otherwise see if there are more job requests
               if(!RunList){
                  if(!JobList)
                     goto END;
                  printf("%d\t%s\n", time, "IDLE");
                  goto NEXTREQUEST;
               }
            } else {
               runPtr = runPtr->next;
            }
         }

        struct Task * node = RunList;

         node = RunList;
         printf("%d\t", time);
         for(numCPU = 1; numCPU <= cores; numCPU++){
            pthread_create(&(pthreadPtr[numCPU-1]), NULL, processJob, node); 
            pthread_join(pthreadPtr[numCPU-1], NULL);
            if(node){
               printf("%s\t", node->process);
               node = node->next;
            } else {
               printf("-\t");
            }
         }
         printf("\n");
        
      }
      //go to next cpu cycle
      NEXTREQUEST:
      time++;
   }
   //end run time
   END:
   printf("%d\tIDLE\n\n", time);
   printf("Summary\n");
   struct User * node = headUser;
   while(node){
      printf("%s\t%d\n", node->user, node->completedTime);
      node = node->next;
   }
   printf("%d missed deadlines\n", missedDeadlines);

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
void printList(struct Task *head){
   if(head == NULL){
      printf("NULL\n");
   } else {
      while(head){
         printf("%s %s %d %d %d\n", head->user, head->process, head->arrival, head->duration, head->deadline);
         head = head->next;
      }
   }
   printf("done print\n");
}

void getJobRequests(){
   int max = 1000;
     //skips over the first line
   char buffer[max];
   //what happens if file is empty?
   fgets(buffer, max, stdin);

   while(fgets(buffer, max, stdin)){
      if(JobList == NULL){
         struct Task *newJob = malloc(sizeof(struct Task));
         sscanf(buffer, "%s %s %d %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration), &(newJob->deadline));
         newJob->next = NULL;
         JobList = newJob;
      } else{
         //there is at least one job. add new job to back
         struct Task *node = JobList;
         while(node->next){
            node = node->next;
         }
         //allocate memory for job
         struct Task *newJob = malloc(sizeof(struct Task));
         sscanf(buffer, "%s %s %d %d %d", newJob->user, newJob->process, &(newJob->arrival), &(newJob->duration), &(newJob->deadline));
         newJob->next = NULL;
         node->next = newJob;
      }
   }
}

struct Task * nextJobRequest(int time) { 
   struct Task *nodeJL = JobList;
   while(nodeJL){
      if(nodeJL->arrival == time){
         return nodeJL;
      }
      nodeJL = nodeJL->next;
   }
   return NULL;
}

struct Task * removeJob(struct Task *node, struct Task *head){
   if(isSameNode(node, head)){
      head = node->next;
      free(node);
      return head;
   } else {
      struct Task *prev = head;
      struct Task *current = head->next;
      while(current){
         if(isSameNode(node, current)){
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

//TO DO: fix up statements
/* When considering what job to complete, you pick the job that has the earliest deadline. 
* To break ties, you pick the shortest job first. If you still have a tie then you pick the job that arrived first.
*/
void insertRunList(struct Task *job, int time){
   if(!RunList){
      insertFront(RunList, job);
      return;
   } else{
      struct Task *node = RunList;
      while(node->next){
         if(node->deadline > job->deadline){
            insertFront(node, job);
            return;
         }
         if((node->deadline == job->deadline) && (node->duration > job->duration)){
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
      if(node->deadline > job->deadline){
         insertFront(node, job);
         return;
      }
      if((node->deadline == job->deadline) && (node->duration > job->duration)){
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

void insertFront(struct Task *node, struct Task *job) {
   struct Task *runListTask = malloc(sizeof(struct Task));
   strcpy(runListTask->user, job->user);
   strcpy(runListTask->process, job->process);
   runListTask->arrival = job->arrival;
   runListTask->duration = job->duration;
   runListTask->deadline = job->deadline;
   if(RunList == NULL){
      RunList = runListTask;
      runListTask->next = NULL;
   } else {
      if(isSameNode(node, RunList)){
         runListTask->next = node;
         RunList = runListTask;
      } else {
         struct Task * previousToNode = RunList;
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
void insertBehind(struct Task *node, struct Task *job){
   struct Task *runListTask = malloc(sizeof(struct Task));
   strcpy(runListTask->user, job->user);
   strcpy(runListTask->process, job->process);
   runListTask->arrival = job->arrival;
   runListTask->duration = job->duration;
   runListTask->deadline = job->deadline;
   runListTask->next = NULL;

   node->next = runListTask;
   createUser(runListTask->user);
}


//move task to the back and bring the next one in line to the front
void nextTask(){
   if(RunList->duration == 0){
      struct Task *nextJob = RunList->next;
      free(RunList);
      RunList = nextJob;
   } else {
      struct Task *eofList = RunList->next;
      //only 1 in run list
      if(eofList == NULL){
         return;
      } else {
         //get to end
         while(eofList->next){
            eofList = eofList->next;
         }
         //ensure RunList points to first node
         struct Task *nextJob = RunList->next;
         eofList->next = RunList;
         RunList->next = NULL;
         RunList = nextJob;
      }
   }
}

bool isDone(struct Task *node){
   if(node->duration == 0) 
      return true;
   else
      return false;
}

struct Task * moveToBack(struct Task *node, struct Task *head){
   //already at back
   if(node->next == NULL)
      return head;
   //go through to back of list
   struct Task * eoList = head;
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
     struct Task * previousToNode = head;
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

bool isSameNode(struct Task *node1, struct Task *node2){
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

void * processJob (struct Task *node) {
   if(node){
      pthread_mutex_lock(&mutex);
	   node->duration--;
	   pthread_mutex_unlock(&mutex);
   }
	sleep(1);
}
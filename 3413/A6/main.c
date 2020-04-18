#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

//FUNCTION DECLARATIONS
struct Process * createNewProcess(int process, int memoryNeeded);
struct Process * firstFit(int process, int memoryNeeded);
void addToList(struct Process *ptr);
bool processExists(int processID);
void removeFromList(int processID);
bool isSameNode(struct Process *node1, struct Process *node2);
int findFinalAvailableMemory();

//STRUCTS
struct Process{
  int ID;
  int memoryTaken;
  int * start;
  int * end;
  struct Process * next;
};

//GLOBALS
const int MAXBUFF = 1000;
char algorithm;
int memoryAvailable;
int * memory;
int totalMemoryAllocated;
int numProcessCreated;
int totalProcessesTerminated;
int totalFreedMemory;
struct Process * head;
int fSearchIndex;



/***************************************************************
*• Firstfit.Allocate the first hole that is big enough.Searching can start either 
at the beginning of the set of holes or at the location where the previous first-fit search ended. 
We can stop searching as soon as we find a free hole that is large enough.

• Best fit. Allocate the smallest hole that is big enough. We must search the entire list, 
unless the list is ordered by size. This strategy produces the smallest leftover hole.

• Worst fit. Allocate the largest hole. Again, we must search the entire list, unless it is sorted by size. 
This strategy produces the largest leftover hole
*                                                                                                 *
***************************************************************/

/***************************************************************
*MAIN                                                          *
*                                                        *
***************************************************************/
int main (int argc, char const *argv[]) {
    if(argc != 4){
        printf("input should look like: ./main -s # -f");
        exit(EXIT_FAILURE);
    }

    //get input arguments
    int i; 
    for(i = 1; i < argc; i++){
        char * cla = argv[i];
        if(strcmp(cla, "-s") == 0){
            memoryAvailable = atoi(argv[i+1]);
            i++;
        } else {
            if(strcmp(cla, "-f") == 0){
                algorithm = 'f';
            } else if(strcmp(cla, "-b") == 0){
                algorithm = 'b';
            } else {
                algorithm = 'w';
            }
        } 
    }
    //initialize memory and begin getting requests
    memory = calloc(memoryAvailable, sizeof(int));
    if(!memory){
        printf("Memory Calloc Failed\n");
        exit(1);
    }
    totalMemoryAllocated = 0;
    numProcessCreated = 0;
    totalProcessesTerminated = 0;
    totalFreedMemory = 0;
    fSearchIndex = 0;
    bool getNextInput = true;
    /*
    N indicates the process (1) that is being created needs memory (500 bytes). 
    The result of this operation is either successful 
    (indicated by a memory address returned that references the new memory) 
    or a failure (indicated by a NULL memory address returned). 
    The T operation is terminating the process (process 7 in this case) 
    and freeing the memory that was assigned to the process. 
    The S operation is to stop the program and print the report.

    */
 

    
    while(getNextInput){
        char buffer[MAXBUFF];
        char operation;
        int processID;
        int memoryNeeded;
        fgets(buffer, MAXBUFF, stdin);
        sscanf(buffer, "%c", &operation);
        switch(operation) {
            case 'N' :
                //check to see if enough memory
                sscanf(buffer, "%c %d %d", &operation, &processID, &memoryNeeded);
                struct Process * tmp = createNewProcess(processID, memoryNeeded);
                if(!tmp){
                    printf("Process %d failed to allocate %d memory\n", processID, memoryNeeded);
                } else {
                    addToList(tmp);
                }        
                break;
            case 'T' :
                //check if process has been created (ie go through list)
                sscanf(buffer, "%c %d", &operation, &processID);
                if(processExists(processID)){
                    removeFromList(processID);
                } else {
                    printf("Process %d failed to free memory\n", processID);  
                }
                //if created then free
                break;
            case 'S' :
                getNextInput = false;
                int availMem = findFinalAvailableMemory();
                printf("Total Processes created %d, Total allocated memory %d, Total Processes terminated %d, Total freed memory %d, Final memory available %d\n", numProcessCreated, totalMemoryAllocated, totalProcessesTerminated, totalFreedMemory, availMem);
                break;
        }
    }

    //ensure list gets freed
    struct Process * tmp = head;
    while(tmp){
      tmp = tmp->next;
      free(head);
      head = tmp;
   }

}


/***************************************************************
*FUNCTION IMPLEMENTATION                                       *
*                                                              *
***************************************************************/

struct Process * createNewProcess(int processID, int memoryNeeded){
    switch (algorithm) {
    case 'f':
        return firstFit(processID, memoryNeeded);
        break;
    }
    return NULL;
}

struct Process * firstFit(int processID, int memoryNeeded){
    struct Process * ptr = NULL;
    if(!head){
        if(memoryNeeded <= memoryAvailable){
            ptr = malloc(sizeof(struct Process));
            ptr->ID = processID;
            ptr->memoryTaken = memoryNeeded;
            ptr->start = 0;
            ptr->end = memoryNeeded-1;
            totalMemoryAllocated += memoryNeeded;
            fSearchIndex = memoryNeeded -1;
        }
    } else {
        int index;
        do{
            index = fSearchIndex;
            struct Process * ptr = head;
            
            while(ptr){
                if(ptr->start == index){
                    index = ptr->end;
                    break;
                }
                ptr->next;
            }

            index++;
        }while(index != fSearchIndex);
    }

    if(ptr){
        numProcessCreated++;
    }
    return ptr;
    // fSearchIndex
    
}

void addToList(struct Process *ptr){
    if(!head){
        head = ptr;
        ptr->next = NULL;
    } else {
        //possible FUTURE implementation: sort by what regions of memory it occupies 
        struct Process * p = head;
        while(p->next){
            p = p->next;
        }
        p->next = ptr;
        ptr->next = NULL;
    }
}

bool processExists(int processID){
    struct Process * tmp = head;
    while(tmp){
        if(processID == tmp->ID){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}


void removeFromList(int processID){
    if(processID == head->ID){
        struct Process *tmp = head;
        head = head->next;
        totalProcessesTerminated++;
        totalFreedMemory += tmp->memoryTaken;
        free(tmp);
    } else {
        struct Process * p = head;
        struct Process * n = head->next;
        while(n){
            if(processID == n->ID){
                totalProcessesTerminated++;
                totalFreedMemory += n->memoryTaken;
                p = n->next;
                free(n);
                break;
            }
            p = n;
            n = n->next;
        }
    }
   
}



bool isSameNode(struct Process *node1, struct Process *node2){
   if(node1->ID == node2->ID)
      return true;
   else
      return false;
}

int findFinalAvailableMemory(){
    int memAvail = 0;
    int i;
    for(i = 0; i < memoryAvailable; i++){
        struct Process * ptr = head;
        while(ptr){
            if(ptr->start == i){
                i = ptr->end;
                break;
            }
            ptr->next;
        }
        memAvail++;
    }
    return memAvail;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//FUNCTION DECLARATIONS
void initializeFrames();
void freeFrames();
unsigned int check(unsigned int table);
unsigned int isAvail();
void translate(unsigned int logAddress, unsigned int offset, unsigned int index);
void swap(char replacementPolicy, unsigned int ** PMEM, unsigned int pageTableNum);
void fifo(unsigned int ** PMEM, unsigned int pageTableNum);
void LRU(unsigned int ** PMEM, unsigned int pageTableNum);


//GLOBALS
unsigned int ** PMEM;
int minorPageFaults;
int majorPageFaults;
int pageHits;
unsigned int numFrames;
unsigned int offsetMask;
unsigned int * pageTable;
int usedFramesCount;
unsigned int pageSize;


/***************************************************************
*MAIN                                                          *           
*                                                              *
***************************************************************/

int main (int argc, char const *argv[]) {
    //ensure correct inputs
    if(argc < 3 || argc > 4){
        printf("2 parameters needed: ./main.c -POLICY #\nWhere POLICY is F/L/O and # is a positive int up to 2^20\n");
        return EXIT_FAILURE;
    } else if (strtol(argv[2], NULL, 10) < 0 || strtol(argv[2], NULL, 10) > pow(2,20)){
        printf("# is a positive int up to 2^20\n");
        return EXIT_FAILURE;
    }

    char replacementPolicy;
    char * cla = argv[1];
    if(strcmp(cla, "-F") == 0) {
        replacementPolicy = 'F';
    } else if (strcmp(cla, "-L") == 0){
        replacementPolicy = 'L';
    } else {
        replacementPolicy = 'O';
    }

    numFrames = strtol(argv[2], NULL, 10);
    PMEM = malloc(numFrames * sizeof(unsigned int *));
    usedFramesCount = 0;
    pageSize = pow(2,12);
    offsetMask = (pow(2,12)-1);
    minorPageFaults = 0;
    majorPageFaults = 0;
    pageHits = 0;
    // pageTable = (unsigned int *) malloc(pow(2,20)*sizeof(unsigned int));

    initializeFrames();

    unsigned int logAddress;
    char r_w;
    int numRead = scanf("%c %u\n", &r_w, &logAddress);
    while(numRead == 2){
        //ensure address is within range
        if(logAddress > pow(2,32)){
            printf("Address is too larg, only 2^32 memory available\n");
        }
        else if(logAddress < 0){
            printf("positive address only\n");
        } else {
            unsigned int pageTableNum = logAddress >> 12; //keeps leftmost 20 bits
            unsigned int offset = logAddress & offsetMask;
            unsigned int index = check(pageTableNum);
            //if != -1 that means the frame is stored
            if(index != -1){
                pageHits++;
                // translate(logAddress, offset, index);
            } else {
                //FIND EMPTY FRAME
                if (usedFramesCount < numFrames) {
                PMEM[usedFramesCount][0] = pageTableNum;
                // translate(logAddress, offset, usedFramesCount);
                usedFramesCount++;
                minorPageFaults++;
                } else {
                //use algorithm to swap out frames and add majorpagefault
                swap(replacementPolicy, PMEM, pageTableNum);
                // translate(logAddress, offset, numFrames-1);
                majorPageFaults++;
                }
            }
        }
    //get next address
    numRead = scanf("%c %u\n", &r_w, &logAddress);
  }//while 
  printf("Total number of Minor page faults: %d\n", minorPageFaults);
  printf("Total number of Major page faults: %d\n", majorPageFaults);
  printf("Total number of page hits: %d\n", pageHits);
  printf("Pages currently stored in swap: %d\n", usedFramesCount);
  freeFrames();

}


/***************************************************************
*Function Implementations                                      *
*                                                              *                                 *
***************************************************************/  

void initializeFrames() {
  //2D array
  int i, j;
  for (i=0; i<numFrames; i++) {
    PMEM[i] = calloc(2, sizeof(int)); 
  }

  for(i = 0; i < numFrames; i++){
    //initialize first entry to -1
    for(j = 0; j < 1; j++){
      PMEM[i][j] = -1;
    }
  }
}

void freeFrames() {
  int i, j = 0;
  for (i=0; i<numFrames; i++) {
    free(PMEM[i]);
  }
  free(PMEM);
}

unsigned int check(unsigned int pageTableNum) {
	int i = 0;
	int found = -1;
	while (i < numFrames && usedFramesCount != 0) {
  	if (PMEM[i][0] != -1 && PMEM[i][0] == pageTableNum) {
  		found = i;
      PMEM[i][1]++;
  		break;
  	}
  	i++;
  }
  return found;
}

void translate(unsigned int logAddress, unsigned int offset, unsigned int index) {
  printf("%u -> %u\n", logAddress, index * pageSize + offset);
}

void fifo(unsigned int ** PMEM, unsigned int pageTableNum){
  if(numFrames == 1){
    PMEM[0][0] = pageTableNum;
  } else {
    int i, j;

    for(i = 0; i < numFrames-1; i++){
      for(j = 0; j < 2; j++){
        PMEM[i][j] = PMEM[i+1][j];
      }
    }

    PMEM[numFrames-1][0] = pageTableNum;
    PMEM[numFrames-1][1] = 0;
  }
}

void LRU(unsigned int ** PMEM, unsigned int pageTableNum) {
  int i;
  int leastUsed = PMEM[0][1];
  int row = 0;
  int temp;
  for(i = 1; i < numFrames; i++){
    int temp = PMEM[i][0];
    if (temp < leastUsed) {
      leastUsed = temp;
      row = i;
  	}
  }

  PMEM[row][0] = pageTableNum;
  PMEM[row][1] = 0;
}

void swap(char replacementPolicy, unsigned int ** PMEM, unsigned int pageTableNum){
  switch (replacementPolicy) {
  case 'F':
    fifo(PMEM, pageTableNum);
    break;
  case 'L':
    LRU(PMEM, pageTableNum);
    break;
  case 'O':
    /* code */
    break;
  }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//FUNCTION DECLARATIONS
void initializeFrames();
void freeFrames();
long int check(long int table);
long int isAvail();
void translate(long int logAddress, long int offset, long int index);
void fifo(long int * PMEM, long int pageTableNum);

//GLOBALS
long int * PMEM;
int pageFaults;
long int numFrames;
long int offsetMask;
long int * pageTable;
int usedFramesCount;
long int pageSize;


/***************************************************************
*MAIN                                                          *           
*                                                              *
***************************************************************/
 
int main (int argc, char const *argv[]) {
  //ensure correct inputs
  if(argc < 2 || argc > 3){
    printf("1 parameter needed: ./main.c #\nWhere # is a positive int up to 2^20\n");
    return EXIT_FAILURE;
  } else if (strtol(argv[1], NULL, 10) < 0 || strtol(argv[1], NULL, 10) > pow(2,20)){
    printf("# is a positive int up to 2^20\n");
    return EXIT_FAILURE;
  }


  numFrames = strtol(argv[1], NULL, 10);
  usedFramesCount = 0;
  pageSize = pow(2,12);
  offsetMask = (pow(2,12)-1);
  pageFaults = 0;
  // pageTable = (long int *) malloc(pow(2,20)*sizeof(long int));
  
  initializeFrames();
  
  long int logAddress;
  int numRead = scanf("%ld\n", &logAddress);
  while(numRead == 1){
    //ensure address is within range
    if(logAddress > pow(2,32)){
      printf("Address is too largy, only 2^32 memory available\n");
    }
    else if(logAddress < 0){
      printf("positive address only\n");
    } else {
      long int pageTableNum = logAddress >> 12; //keeps leftmost 20 bits
      long int offset = logAddress & offsetMask;
      long int index = check(pageTableNum);
      //if != -1 that means the frame is stored
      if(index != -1){
        translate(logAddress, offset, index);
      } else {
        //PAGE FAULT
        pageFaults++;
        //FIND EMPTY FRAME
        if (usedFramesCount < numFrames) {
          PMEM[usedFramesCount] = pageTableNum;
          translate(logAddress, offset, usedFramesCount);
          usedFramesCount++;
        } else {
          //use fifo to swap out first frame and put new one at the end
          fifo(PMEM, pageTableNum);
          translate(logAddress, offset, numFrames-1);
        }
      }
    }
    //get next address
    numRead = scanf("%ld\n", &logAddress);
  }//while 
  printf("Total number of Page Faults: %d\n", pageFaults);
  freeFrames();

}


/***************************************************************
*Function Implementations                                      *
*                                                              *                                 *
***************************************************************/  

void initializeFrames() {
	PMEM = malloc(numFrames * sizeof(long int));
	int i = 0;
	while(i < numFrames) {
		PMEM[i] = -1;
		i++;
	}
}
void freeFrames() {
  free(PMEM);
}

long int check(long int pageTableNum) {
	int i = 0;
	int found = -1;
	while (i < numFrames && usedFramesCount != 0) {
  	if (PMEM[i] != -1 && PMEM[i] == pageTableNum) {
  		found = i;
  		break;
  	}
  	i++;
  }
  return found;
}

void translate(long int logAddress, long int offset, long int index) {
  printf("%ld -> %ld\n", logAddress, index * pageSize + offset);
}

void fifo(long int * PMEM, long int pageTableNum){
  if(numFrames == 1){
    PMEM[0] = pageTableNum;
  } else {
    int i, j;
    for(i = 0, j = 1; j < numFrames; i++, j++){
      PMEM[i] = j;
    }
    PMEM[i] = pageTableNum;
  }
}
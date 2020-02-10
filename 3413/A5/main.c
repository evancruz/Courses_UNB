#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>

//structs
struct Car{
  char * driver[1000];
  char direction;
  int arrival;
  int duration;
  bool onBridge;
  struct Car * next;
};

//functions
void getCars();
void queCar(struct Car *newCar);
void freeList(struct Car * head);
void insertFront(struct Car * newCar, struct Car * car, struct Car * head);
void insertBack(struct Car * newCar, struct Car * head);
bool isSameCar(struct Car *car1, struct Car *car2);
void printList(struct Car *head);
void * bridgeArrival(struct Car * carIn);
void removeCar(struct Car * car, char * direction);


//globals
sem_t mutex; 
struct Car * NorthList = NULL;
struct Car * SouthList = NULL;
int numCars = 0;
bool allCrossed = false;
bool carsOnBridge = false;
char trafficFlow = '0';

/*PROTOS

int sem_init(sem_t *sem, int pshared, unsigned int value);

*/

/***************************************************************
* MAIN PROGRAM                                                                     *
*ASSUMPTIONS:                                                                       *
* An old bridge across a river has only one lane so cars can travel*
* in just one direction at a time. Doesn't say there's a limit to how *
* many cars can be on the bridge crossing at once. For example:   *
* there could be 5 cars on the bridge going South                        *
***************************************************************/
int main (int argc, char const *argv[]) {
   getCars();
   pthread_t car[numCars];
   int i = 0;
   struct Car * vehicleN = NorthList;
   struct Car * vehicleS = SouthList;
   vehicleS = SouthList;

   //start time
   sem_init(&mutex, 0, 1); 
   int timer;
   for(timer = 0; !allCrossed; timer++){
   if(vehicleN){
      if(vehicleN->arrival == timer){
      pthread_create(&car[i], NULL, (void *) bridgeArrival, vehicleN);
      vehicleN = vehicleN->next;
      i++;
      }
   }
   if(vehicleS){
      if(vehicleS->arrival == timer){
         pthread_create(&car[i], NULL, (void *) bridgeArrival, vehicleS);
         vehicleS = vehicleS->next;
         i++;
      }
   }

   // printf("time: %d\n", timer); // time display
   sleep(1);
  }

  //wait for all threads to finish
   for(i = 0; i < numCars; i++){
      pthread_join(car[i], NULL);
   }

   //ensure that lists are freed
   freeList(NorthList);
   freeList(SouthList);
   
}




/***************************************************************
* FUNCTION IMPLEMENTATIONS                                                *
*                                                                                            *
***************************************************************/

void getCars(){
   int max = 1000;
   char buffer[max];
   //skips over the first line
   fgets(buffer, max, stdin);
   while(fgets(buffer, max, stdin)){
      struct Car * newCar = malloc(sizeof(struct Car));
      sscanf(buffer, "%s %c %d %d", newCar->driver, &(newCar->direction), &(newCar->arrival), &(newCar->duration));
      newCar->next = NULL;
      newCar->onBridge = false;
      queCar(newCar);
      numCars++;
   }
}

//don't assume that they come in order
//get direction then get arrival
void queCar(struct Car *newCar){
   struct Car * currentCar;
   if(newCar->direction == 'N'){
      if(!NorthList){
         NorthList = newCar;
      } else{
         currentCar = NorthList;
         while(currentCar){
            if(currentCar->arrival > newCar->arrival){
               insertFront(newCar, currentCar, NorthList);
               return;
            }
            currentCar = currentCar->next;
         }
         insertBack(newCar, NorthList);
      }
   } else {
      //direction South
      if(!SouthList){
         SouthList = newCar;
      } else {
      currentCar = SouthList;
      while(currentCar){
         if(currentCar->arrival > newCar->arrival){
            insertFront(newCar, currentCar, SouthList);
            return;
         }
         currentCar = currentCar->next;
      }
      insertBack(newCar, SouthList);
      }
   }  
}


void insertFront(struct Car * newCar, struct Car * nextCar, struct Car * head) {
   if(isSameCar(nextCar, head)){
      if(isSameCar(head, NorthList)){
         NorthList = newCar;
         newCar->next = nextCar;
      } else {
         SouthList = newCar;
         newCar->next = nextCar;
      }
   } else {
      //find where car is
      struct Car * ptr = head;
      while(ptr->next){
         if(isSameCar(ptr->next, nextCar)){
            ptr->next = newCar;
            newCar->next = nextCar;
            return;
         }
         ptr = ptr->next;
      }
   }
}

void insertBack(struct Car * newCar, struct Car * head){
   struct Car * car = head;
   while(car->next){
      car = car->next;
   }
   car->next = newCar;
}

bool isSameCar(struct Car *car1, struct Car *car2){
   if((strcmp(car1->driver, car2->driver)==0) && car1->arrival == car2->arrival)
      return true;
   else
      return false;
}


void printList(struct Car *head){
   if(head == NULL){
      printf("NULL\n");
   } else {
      while(head){
         printf("%s %c %d %d\n", head->driver, head->direction, head->arrival, head->duration);
         head = head->next;
      }
   }
   printf("done print\n");
}

void freeList(struct Car * head){
   if(head == NULL)
      return;
   struct Car * ptr = head;
   while(head != NULL){
      head = head->next;
      free(ptr);
      ptr = head;
   }
}


void * bridgeArrival(struct Car * carIn){
   //check for direction of traffic, if any cars are crossing
   if(carIn->direction == trafficFlow){
      goto GETONBRIDGE;
   }

   sem_wait(&mutex);
   while(carsOnBridge){
      sem_post(&mutex);
      sleep(1);
      sem_wait(&mutex);
   } //no cars on bridge. can cross
   carsOnBridge = true;
   sem_post(&mutex);

   GETONBRIDGE:
   carIn->onBridge = true;
   if(trafficFlow != carIn->direction){
      trafficFlow = carIn->direction;
      printf( "Direction: %s\n", trafficFlow == 'N' ? "North": "South");
   }
   while(carIn->duration >= 0){
      carIn->duration--;
      sleep(1);
   }
   //need to delete off list
   //if list is empty then set allCarsPassed to true
   if(carIn->next){
      if(carIn->next->onBridge == false){
      sem_wait(&mutex);
      carsOnBridge = false;
      sem_post(&mutex);
      }
   } else { //there is no next car
      sem_wait(&mutex);
      carsOnBridge = false;
      sem_post(&mutex);
   }
   printf("%s \n", carIn->driver);
   removeCar(carIn, &(carIn->direction));

   if(!NorthList && !SouthList)
      allCrossed = true;
}

//list is already in order so carIn should actually be head
void removeCar(struct Car * carIn, char * direction){
   struct Car * car;
   if(*direction == 'N'){
      car = NorthList;
      NorthList = NorthList->next;
   } else {
      car = SouthList;
      SouthList = SouthList->next;
   }
   free(car);
}
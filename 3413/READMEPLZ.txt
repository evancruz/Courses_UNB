A1: 2.55/3
algorithm has a mistake on rescheduling, when job with remaining 2 units of time has just finished execution, and a job that just arrived requires more time to execute are compared,
then the algorithm will start to execute the new with a (longer) job, contrary to the assignment text. 
Sample test: User Process Arrival Duration
Alex B 2 4 
Nadia C 4 3, with a quantum 2

A2: 3/3
InsertFront and InsertBehind are mixed up and didnt fix it until the next assignment

A3: 2.52/3
From the assignment description: "Using pthreads, modify your program to create one pthread per cpu that you specify." You have created only one thread and then joined it immediately which simplified assignment solution. -10
You should revise use of mutexes, there might be more places where they should be applied, but your program is "fine" since it effectively uses only one thread

A4:3/3

A5: 1.5/3
solution fails to account with cars with the same name driving multiple times
Your solution fails on test where several cars arrive in altering directions one after another on tight schedule
Your program fails the test where multiple cars are on the bridge simultaneously


A6: did not do 

A7: 2.7/3
did not implement page frames switching properly: physical pages grow indefinitely.

A8: didn't take the time to complete the assignment
(-10) discarding pages algorithm on read mode (minor page fault - swap) is wrong
(-10) hitting pages algorithm on read mode (minor page fault - page hits) is wrong
(-30) LRU and optimal algorithm are not implemented properly

A9+A10: did not do
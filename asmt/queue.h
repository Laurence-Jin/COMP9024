// Queue ADT header file ... COMP9024 21T3

typedef struct QueueRep *queue;

typedef struct node {
   int data;
   struct node *next;
} NodeT;

typedef struct QueueRep {
   int   length;
   NodeT *head;
   NodeT *tail;
} QueueRep;

queue newQueue();               // set up empty queue
void  dropQueue(queue);         // remove unwanted queue
int   QueueIsEmpty(queue);      // check whether queue is empty
void  QueueEnqueue(queue, int); // insert an int at end of queue
int   QueueDequeue(queue);      // remove int from front of queue
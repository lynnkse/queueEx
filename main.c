#include "Queue.h"
#include <stdio.h>

typedef enum User_Choice
{
    CREATE_QUEUE,
    DELETE_QUEUE,
    PUSH,
    POP,
    PRINT_QUEUE,
    IS_EMPTY,
    COUNT,
    EXIT
} User_Choice;

typedef void (*Func)(Queue**);

typedef struct TestStruct
{
    int m_a;
    int m_b;
}

int main()
{
    return 0;
}

/*static void CreateQueue(Queue**);
static void DeleteQueue(Queue**);
static void Push(Queue**);
static void Pop(Queue**);
static void Print(Queue**);
static User_Choice InputToUserChoice(int _input);
static void Exit(Queue**);
static void IsEmpty(Queue**);
static void Count(Queue**);

static Func funcs[] = {CreateQueue, DeleteQueue, Push, Pop, Print, IsEmpty, Count, Exit};

int main()
{
  Queue* queue = NULL;
  int input;
  User_Choice choice = CREATE_QUEUE;
  
  while(choice != EXIT)
  {
    printf("Please make a choice:\n(1) Create queue\n(2) Delete queue\n(3) Push data\n(4) Pop data\n(5) Print queue\n(6) Check if the queue is empty\n(7) Number of elements in the queue\n(8) Exit\n\n");
    scanf("%d", &input);
    choice = InputToUserChoice(input);
    funcs[choice](&queue);
    printf("\n");
  }
  
  return 0;
}

static void CreateQueue(Queue** _queue)
{
  unsigned int size;
  
  if(*_queue != NULL)
  {
    printf("Queue already exists\n\n");
    return;
  }

  printf("Enter queue size:\n");
  scanf("%d", &size);

  *_queue = Queue_Create(size);
}

static void Exit(Queue** _queue)
{}

static void IsEmpty(Queue** _queue)
{
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  if(Queue_IsEmpty(*_queue))
  {
    printf("The queue is empty\n");
  }
  else
  {
    printf("The queue is not empty\n");
  }
}

static void Count(Queue** _queue)
{
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  printf("Number of elements in the queue: %d\n", Queue_Count(*_queue));
}

static void DeleteQueue(Queue** _queue)
{
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  Queue_Destroy(*_queue);

  *_queue = NULL;
}

static void Push(Queue** _queue)
{
  QUEUE_DATA data;
  
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  printf("Enter data to push:\n");
  scanf("%d", &data);

  if(Queue_PushBack(*_queue, data) == QUEUE_SUCCESS)
  {
    printf("Data pushed sucessfully\n");
  }
  else
  {
    printf("Can't push data, the queue in full\n");
  }
}

static void Pop(Queue** _queue)
{
  QUEUE_DATA data;
  
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  if(Queue_PopFront(*_queue, &data) != QUEUE_SUCCESS)
  {
    printf("There's no data in queue\n");
  }
  else
  {
    printf("Data received from queue: %d\n", data);
  }
}

static void Print(Queue** _queue)
{
  if(!*_queue)
  {
    printf("Queue does not exist\n");
    return;
  }

  Queue_Print(*_queue);
}

static User_Choice InputToUserChoice(int _input)
{
  return _input - 1;
}

*/

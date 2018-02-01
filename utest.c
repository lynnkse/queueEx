#include "mu_test.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "Queue.h"

int g_multiplicationProduct = 1;

static Queue_Result MultiplyAll(QUEUE_DATA data)
{
  g_multiplicationProduct *= data;

  return QUEUE_SUCCESS;
}

UNIT(CREATION)
Queue* queue = NULL;
Queue* failed_queue = NULL;
queue = Queue_Create(5);
failed_queue = Queue_Create(0);
ASSERT_THAT(queue);
ASSERT_THAT(!failed_queue);
END_UNIT

UNIT(INSERTION)
Queue* queue = Queue_Create(5);
ASSERT_THAT(Queue_IsEmpty(queue));
Queue_PushBack(queue, 5);
ASSERT_THAT(!Queue_IsEmpty(queue));
Queue_Destroy(queue);
queue = NULL;
ASSERT_THAT(1);
END_UNIT

UNIT(FAILED_INSERTION_OVERFLOW)
Queue* queue = Queue_Create(3);
ASSERT_THAT(Queue_PushBack(queue, 1) == QUEUE_SUCCESS);
ASSERT_THAT(Queue_PushBack(queue, 1) == QUEUE_SUCCESS);
ASSERT_THAT(Queue_PushBack(queue, 1) == QUEUE_SUCCESS);
ASSERT_THAT(Queue_PushBack(queue, 1) != QUEUE_SUCCESS);
Queue_Destroy(queue);
queue = NULL;
ASSERT_THAT(1);
END_UNIT

UNIT(POP)
int data;
Queue* queue = Queue_Create(5);
Queue_PushBack(queue, 1);
Queue_PushBack(queue, 2);
Queue_PushBack(queue, 3);
Queue_PopFront(queue, &data);
ASSERT_THAT(data == 1);
Queue_PopFront(queue, &data);
ASSERT_THAT(data == 2);
Queue_PopFront(queue, &data);
ASSERT_THAT(data == 3);
Queue_Destroy(queue);
queue = NULL;
ASSERT_THAT(1);
END_UNIT

UNIT(NUM_OF_ITEMS)
Queue* queue = Queue_Create(5);
ASSERT_THAT(Queue_Count(queue) == 0);
Queue_PushBack(queue, 1);
Queue_PushBack(queue, 2);
Queue_PushBack(queue, 3);
ASSERT_THAT(Queue_Count(queue) == 3);
Queue_Destroy(queue);
queue = NULL;
ASSERT_THAT(1);
END_UNIT

UNIT(FOR_EACH)
Queue* queue = Queue_Create(5);
Queue_PushBack(queue, 1);
Queue_PushBack(queue, 2);
Queue_PushBack(queue, 3);
Queue_ForEach(queue, MultiplyAll);
ASSERT_THAT(g_multiplicationProduct == 6);
Queue_Destroy(queue);
queue = NULL;
ASSERT_THAT(1);
END_UNIT

TEST_SUITE(QUEUE_TESTS)
TEST(CREATION)
TEST(INSERTION)
TEST(FAILED_INSERTION_OVERFLOW)
TEST(POP)
TEST(NUM_OF_ITEMS)
TEST(FOR_EACH)
END_SUITE

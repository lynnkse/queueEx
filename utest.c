#include "mu_test.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "Queue.h"
#include <pthread.h>

typedef struct IdxAndQueue
{
    size_t m_idx;
    size_t m_currVal;
    Queue* m_queue;
} IdxAndQueue;

typedef struct TestStruct
{
    int m_a;
    int m_b;
} TestStruct;


void SendData(IdxAndQueue* _idxq)
{
    size_t i;
    for(i = 1; i < 1000001; ++i)
    {
	TestStruct* ts = malloc(sizeof(TestStruct));
	ts->m_a = _idxq->m_idx;
	ts->m_b = i;
	Queue_PushBack(_idxq->m_queue, (void*)ts);
    }
}

void FetchAndCheck(IdxAndQueue* _idxq)
{
    TestStruct* ts;
    size_t i;
    size_t currVals[] = {0, 0, 0};

    for(i = 0; i < 3000000; ++i)
    {
	Queue_PopFront(_idxq->m_queue, (void**)&ts);
	if(ts->m_b != currVals[ts->m_a] + 1)
	{
	    break;
	}
	currVals[ts->m_a] = ts->m_b;
	free(ts);
    }
}

void Destruct(void* _item)
{
    free((TestStruct*)_item);
}

void EmptyDestruct(void* _item)
{}

Queue_Result TimesTwo(void* _item)
{
    ((TestStruct*)_item)->m_a *= 2;
    ((TestStruct*)_item)->m_b *= 2;

    return QUEUE_SUCCESS;
}

UNIT(THREADS)
void* junk;
Queue* queue = Queue_Create(5000);
pthread_t threads[3];
pthread_t fthread;
size_t i;
IdxAndQueue iaqs[] = 
{
    {0, 0, queue},
    {1, 0, queue},
    {2, 0, queue}
};

for(i = 0; i < 3; ++i)
{
    pthread_create(&threads[i], NULL, (void* (*)(void*))SendData, (void*)&iaqs[i]);
}

pthread_create(&fthread, NULL, (void* (*)(void*))FetchAndCheck, (void*)&iaqs[0]);

for(i = 0; i < 3; ++i)
{
    pthread_join(threads[i], &junk);
}

pthread_join(fthread, &junk);

ASSERT_THAT(Queue_IsEmpty(queue));

Queue_Destroy(queue, Destruct);

END_UNIT

UNIT(CREATION)
Queue* queue = NULL;
Queue* failed_queue = NULL;
queue = Queue_Create(5);
failed_queue = Queue_Create(0);
ASSERT_THAT(queue);
ASSERT_THAT(!failed_queue);
Queue_Destroy(queue, Destruct);
END_UNIT

UNIT(SIMPLE_INSERTION)
TestStruct* ts = malloc(sizeof(TestStruct));
Queue* queue = Queue_Create(5);
ASSERT_THAT(Queue_IsEmpty(queue));
Queue_PushBack(queue, ts);
ASSERT_THAT(!Queue_IsEmpty(queue));
Queue_Destroy(queue, Destruct);
END_UNIT

UNIT(IN_OUT)
Queue* queue = Queue_Create(5);
TestStruct* ts = NULL;
TestStruct data[] =
{
    {1, 2},
    {3, 4},
    {5, 6}
};

Queue_PushBack(queue, &data[0]);
Queue_PushBack(queue, &data[1]);
Queue_PushBack(queue, &data[2]);

Queue_PopFront(queue, (void*)&ts);
ASSERT_THAT(ts->m_a == 1 && ts->m_b == 2);
Queue_PopFront(queue, (void*)&ts);
ASSERT_THAT(ts->m_a == 3 && ts->m_b == 4);
Queue_PopFront(queue, (void*)&ts);
ASSERT_THAT(ts->m_a == 5 && ts->m_b == 6);

Queue_Destroy(queue, EmptyDestruct);
END_UNIT

UNIT(FOR_EACH)
Queue* queue = Queue_Create(5);
TestStruct* ts = NULL;
int sumBefore  = 0, sumAfter = 0;
int i;
TestStruct data[] =
{
    {1, 2},
    {3, 4},
    {5, 6}
};

for(i = 0; i < 3; ++i)
{
    sumBefore += data[i].m_a;
    sumBefore += data[i].m_b;
}

Queue_PushBack(queue, &data[0]);
Queue_PushBack(queue, &data[1]);
Queue_PushBack(queue, &data[2]);

Queue_ForEach(queue, TimesTwo);

for(i = 0; i < 3; ++i)
{
    sumAfter += data[i].m_a;
    sumAfter += data[i].m_b;
}

ASSERT_THAT(sumAfter == sumBefore * 2);

Queue_Destroy(queue, EmptyDestruct);
END_UNIT

TEST_SUITE(QUEUE_TESTS)
TEST(CREATION)
TEST(SIMPLE_INSERTION)
TEST(IN_OUT)
TEST(FOR_EACH)
TEST(THREADS)
END_SUITE

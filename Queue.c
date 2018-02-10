#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "Queue.h"

#define TRUE 1
#define FALSE 0

struct Queue
{
    void**   m_data;
    size_t  m_head;      /* Index of head in m_vec. */
    size_t  m_tail;      /* Index of tail in m_vec. */
    size_t  m_size;      /* Capacity of the queue   */
    size_t  m_full;
    size_t  m_empty;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond_full;
    pthread_cond_t m_cond_empty;
};

Queue* Queue_Create(unsigned int _size)
{
    Queue* queue;
    if(_size == 0)
    {
	return NULL;
    }
  
    queue  = (Queue*) malloc(sizeof(Queue));
    if (!queue)
    {
	return NULL;
    }

    queue->m_data = malloc((_size + 1) * sizeof(void*));
    if (!queue->m_data)
    {
	free(queue);
	return NULL;
    }
    
    queue->m_size = _size + 1;
    queue->m_head = 0;
    queue->m_tail = 0;
    queue->m_full = 0;
    queue->m_empty = _size;
    pthread_cond_init(&queue->m_cond_full, NULL);
    pthread_cond_init(&queue->m_cond_empty, NULL);
    pthread_mutex_init(&queue->m_mutex, NULL);
    
    return queue;
}

void Queue_Destroy(Queue *_queue, DestructFunc _destructFunc)
{
    if (_queue)
    {
	unsigned int head = _queue->m_head;
	unsigned int tail = _queue->m_tail;
  
	while(head != tail)
	{
	    _destructFunc(_queue->m_data[head]);
	    head = (head + 1) % _queue->m_size;
	}

	pthread_cond_destroy(&_queue->m_cond_full);
	pthread_cond_destroy(&_queue->m_cond_empty);
	pthread_mutex_destroy(&_queue->m_mutex);
	
	free(_queue->m_data);
        free(_queue);
    }
}

Queue_Result Queue_PushBack(Queue *_queue, void* _item)
{

   if(!_queue)
   {
     return QUEUE_NOT_INITIALIZED_ERROR;
   }

   pthread_mutex_lock(&_queue->m_mutex);

   while(_queue->m_empty == 0)
   {
       pthread_cond_wait(&_queue->m_cond_empty, &_queue->m_mutex);
   }

   *(_queue->m_data + _queue->m_tail) = _item;
    _queue->m_tail =  (_queue->m_tail+1) % _queue->m_size;

    ++_queue->m_full;
    --_queue->m_empty;

    pthread_cond_broadcast(&_queue->m_cond_full);
    pthread_mutex_unlock(&_queue->m_mutex);
    
    return QUEUE_SUCCESS;
}

Queue_Result Queue_PopFront(Queue *_queue, void** _item)
{

    if (!_queue)
    {
        return QUEUE_NOT_INITIALIZED_ERROR;
    }

    if(!_item)
    {
	return NULL_PTR_ERROR;
    }
    
    pthread_mutex_lock(&_queue->m_mutex);
    while(_queue->m_full == 0)
    {
	pthread_cond_wait(&_queue->m_cond_full, &_queue->m_mutex);
    }

    ++_queue->m_empty;
    --_queue->m_full;

    pthread_cond_broadcast(&_queue->m_cond_empty);
    pthread_mutex_unlock(&_queue->m_mutex);

    *_item = *(_queue->m_data + _queue->m_head);
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    return QUEUE_SUCCESS;
}

unsigned int Queue_Count(const Queue *_queue)
{
    unsigned int result;

    if(!_queue)
    {
	return 0;
    }

    pthread_mutex_lock(&((Queue*)_queue)->m_mutex);
    
    result = _queue->m_full;
    
    pthread_mutex_unlock(&((Queue*)_queue)->m_mutex);
    
    return result;
}

int Queue_IsEmpty(const Queue *_queue)
{
    int result;

    if(!_queue)
    {
	return TRUE;
    }


    pthread_mutex_lock(&((Queue*)_queue)->m_mutex);
    result = (_queue->m_full == 0);
    pthread_mutex_unlock(&((Queue*)_queue)->m_mutex);

    return result;
}

void Queue_ForEach(const Queue *_queue, QueueCallback _func)
{
    size_t head, tail;
  
    if(!_queue)
    {
	return;
    }

    pthread_mutex_lock(&((Queue*)_queue)->m_mutex);
    
    head = _queue->m_head;
    tail = _queue->m_tail;

    while(head != tail)
    {
	if(_func(_queue->m_data[head]) != QUEUE_SUCCESS)
	{
	    break;
	}

	head = (head + 1) % _queue->m_size;
    }

    pthread_mutex_unlock(&((Queue*)_queue)->m_mutex);
}




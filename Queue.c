#include <stdlib.h>
#include <stdio.h>


#include "Queue.h"

#define TRUE 1
#define FALSE 0

struct Queue
{
  QUEUE_DATA*    m_vec;
  size_t  m_head;      /* Index of head in m_vec. */
  size_t  m_tail;      /* Index of tail in m_vec. */
  size_t  m_size;      /* Capacity of the queue   */
};

static Queue_Result PrintData(QUEUE_DATA _data);

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

  queue->m_vec = malloc((_size + 1) * sizeof(int));
  if (!queue->m_vec)
  {
      free(queue);
      return NULL;
  }

  queue->m_size = _size + 1;
  queue->m_head = 0;
  queue->m_tail = 0;

  return queue;
}

void Queue_Destroy(Queue *_queue)
{
    if (_queue)
    {
        free(_queue->m_vec);
        free(_queue);
    }
}

Queue_Result Queue_PushBack(Queue *_queue, int _item)
{

   if(!_queue)
   {
     return QUEUE_NOT_INITIALIZED_ERROR;
   }

   if((_queue->m_tail + 1) % _queue->m_size == _queue->m_head)
   {
     return QUEUE_ISFULL_ERROR;
   }

   *(_queue->m_vec + _queue->m_tail) = _item;

    _queue->m_tail =  (_queue->m_tail+1) % _queue->m_size;

    return QUEUE_SUCCESS;
}

Queue_Result Queue_PopFront(Queue *_queue, int *_item)
{

    if (!_queue)
    {
        return QUEUE_NOT_INITIALIZED_ERROR;
    }

    if (_queue->m_head == _queue->m_tail)
    {
        /* Queue is empty. */
        return QUEUE_ISEMPTY_ERROR;
    }

    *_item = *(_queue->m_vec + _queue->m_head);
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    return QUEUE_SUCCESS;
}

unsigned int Queue_Count(const Queue *_queue)
{
  size_t head, tail;
  unsigned int ret_val;

  if(!_queue)
  {
    return 0;
  }

  head = _queue->m_head;
  tail = _queue->m_tail;
  
  if(tail >= head)
  {
    ret_val = tail-head;
  }
  else
  {
    ret_val = tail + _queue->m_size - head;
  }

  return ret_val;
}

int Queue_IsEmpty(const Queue *_queue)
{
  if(!_queue)
  {
    return TRUE;
  }

  return (_queue->m_tail == _queue->m_head);
}

void Queue_ForEach(const Queue *_queue, QueueCallback _func)
{
  size_t head, tail;
  
  if(!_queue)
  {
    return;
  }

  head = _queue->m_head;
  tail = _queue->m_tail;
  
  while(head != tail)
  {
    if(_func(_queue->m_vec[head]) != QUEUE_SUCCESS)
    {
      break;
    }

    head = (head + 1) % _queue->m_size;
  }
}

void Queue_Print(const Queue *_queue)
{
  if(!_queue)
  {
    return;
  }

  Queue_ForEach(_queue, PrintData);
}

static Queue_Result PrintData(QUEUE_DATA _data)
{
  printf("%d ", _data);

  return QUEUE_SUCCESS;
}


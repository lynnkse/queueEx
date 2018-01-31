#include <stdlib.h>
#include <stdio.h>


#include "queue.h"

struct Queue
{
    QUEUE_DATA*    m_vec;
    size_t  m_size;
    size_t  m_head;      /* Index of head in m_vec. */
    size_t  m_tail;      /* Index of tail in m_vec. */    
};

Queue* QueueCreate(size_t _size)
{
    Queue* queue  = (Queue*) malloc(sizeof(Queue));
    if (!queue)
    {
        return NULL;
    }

    queue->m_vec = malloc(_size * sizeof(int));
    if (!queue->m_vec)
    {
        free(queue);
        return NULL;
    }

    queue->m_size    = _size;
    queue->m_head    = 0;
    queue->m_tail    = 0;
    queue->m_nItems  = 0;

    return queue;
}

void QueueDestroy(Queue *_queue)
{
    if (_queue)
    {
        free(_queue->m_vec);
        free(_queue);
    }
}

ADTErr QueueInsert(Queue *_queue, int _item)
{

   if(!_queue)
   {
        return ERR_NOT_INITIALIZED;
   }

   if (_queue->m_nItems == _queue->m_size)
   {
       /* Queue is full. */
       return ERR_OVERFLOW;
   }

    *(_queue->m_vec + _queue->m_tail) = _item;

    _queue->m_tail =  (_queue->m_tail+1) % _queue->m_size;
    ++_queue->m_nItems;

    return ERR_OK;

}

ADTErr QueueRemove(Queue *_queue, int *_item)
{

    if (!_queue)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (!_queue->m_nItems)
    {
        /* Queue is empty. */
        return ERR_UNDERFLOW;
    }

    *_item = *(_queue->m_vec + _queue->m_head);
    _queue->m_head = (_queue->m_head + 1) % _queue->m_size;
    --_queue->m_nItems;

    return ERR_OK;
}

int QueueIsEmpty(Queue *_queue)
{
    if (!_queue)
    {
        return TRUE;
    }

    return(_queue->m_nItems ? FALSE : TRUE);

}

/*  Unit-Test functions  */
void QueuePrint(Queue *_queue)
{

    if (!_queue) {
         printf("Queue details> Queue is not initialized.\n");
         return;
    }

    printf("Queue details> Size: %u, Head: %u, Tail: %u, nItems: %u\n", _queue->m_size, _queue->m_head,
                                                                        _queue->m_tail, _queue->m_nItems);
    if (!_queue->m_nItems){
      printf("Queue items>   The Queue is empty.");
      return;
    }

    printf("Queue items>   ");
    int i;
    if (_queue->m_head < _queue->m_tail){
        for (i=_queue->m_head; i<_queue->m_tail; ++i) {
            printf("%d ",_queue->m_vec[i]);
        }
    } else {
        for (i=_queue->m_head; i<_queue->m_size; ++i) {
            printf("%d ",_queue->m_vec[i]);
        }
        for (i=0; i<_queue->m_tail; ++i) {
            printf("%d ",_queue->m_vec[i]);
        }
    }
    printf("\n-------------------------------------------------------\n");
}

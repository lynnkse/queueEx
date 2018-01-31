#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue Queue;
typedef int QUEUE_DATA;

typedef enum Vector_Result {
	QUEUE_SUCCESS,
	QUEUE_ISFULL_ERROR,				/**< Uninitialized vector error 	*/
	QUEUE_ISEMPTY_ERROR,				/**< realloc error on grow/shrink   */
	/* Add more as needed by your implementation */
} Vector_Result;

/**  
 * @brief Create a queue on a cyclic buffer. 
 * @param _size - initial capacity, number of elements that can be stored initially
  * @return Vector * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the vector will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Queue* Queue_Create(unsigned int _size);

void Queue_Destroy(Queue *_queue);


int Queue_PushBack(Queue *_queue, QUEUE_DATA _item);
int Queue_PopFront(Queue *_queue, QUEUE_DATA *_item);

unsigned int Queue_Count(const Queue *_queue);
int Queue_IsEmpty(const Queue *_queue);

void Queue_Print(const Queue *_queue);

void Queue_ForEach(const Queue *_queue......);

#endif /*__QUEUE_H__*/

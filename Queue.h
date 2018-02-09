#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue Queue;
typedef int QUEUE_DATA;

typedef enum Queue_Result {
	QUEUE_SUCCESS,
	QUEUE_ISFULL_ERROR,				/**< Uninitialized vector error 	*/
	QUEUE_ISEMPTY_ERROR,				/**< realloc error on grow/shrink   */
	QUEUE_NOT_INITIALIZED_ERROR,
	QUEUE_CALLBACK_FUNC_FAIL,
	NULL_PTR_ERROR
} Queue_Result;

typedef Queue_Result (*QueueCallback)(void*);
typedef void (*DestructFunc)(void*);

/**  
 * @brief Create a queue on a cyclic buffer. 
 * @param _size - initial capacity, number of elements that can be stored initially
  * @return Vector * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the vector will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */

/**  
 * @brief Create a queue on a cyclic buffer. 
 * @param _size - initial capacity, number of elements that can be stored initially
 * @return  Queue* - on success / NULL on fail 
 * @warning if _blockSize is 0 function will not create queue and will return NULL. 
 */
Queue* Queue_Create(unsigned int _size);

/**  
 * @brief Destroys queue and deallocates the resourses 
 * @param Queue* - ptr to a queue to be destroyed
 * @return void
 * @warning if received param is NULL, function will not do anything 
 */
void Queue_Destroy(Queue *_queue,  DestructFunc _destructFunc);

/**  
 * @brief Pushed data into the queue
 * @param _queue - queue to push into
 * @param _item - data to push
 * @return Queue_Result - error code 
 * @warning if queue capacity is reached, item will not be pushed 
 */
Queue_Result Queue_PushBack(Queue *_queue, void* _item);

/**  
 * @brief Pop data from the queue
 * @param _queue - queue to push into
 * @param _item - data to push
 * @return Queue_Result - error code 
 * @warning if queue capacity is reached, item will not be pushed 
 */
Queue_Result Queue_PopFront(Queue *_queue, void** _item);

/**  
 * @brief Returns number of items in queue
 * @param _queue to check number of items in
 * @return unsigned int - number of items
 * @warning if queue capacity is reached, item will not be pushed 
 */
unsigned int Queue_Count(const Queue *_queue);

/**  
 * @brief Check if the queue is empty
 * @param _queue to check
 * @return unsigned int - 1 if empty, 0 otherwise
 */
int Queue_IsEmpty(const Queue *_queue);

/**  
 * @brief Prints out the queue
 * @param _queue to print
 * @return void
 */
void Queue_Print(const Queue *_queue);

/**  
 * @brief Invokes callback function on every element in the queue
 * @param _queue
 * @param _func - callback function
 * @return void
 */
void Queue_ForEach(const Queue *_queue, QueueCallback _func);

#endif /*__QUEUE_H__*/

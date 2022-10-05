#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <inttypes.h>
#include <stdbool.h>

/*** DO NOT MODIFY THIS FILE IN ANY WAY!! ***/
   	
/**  Generic data structure using contiguous storage for user data objects,
 *   which are stored in ascending order, as defined by a user-supplied
 *   comparison function.  The interface of the comparison function must
 *   conform to the following requirements:
 * 
 *     int32_t compareElems(const void* const pLeft, const void* const pRight);
 *        Returns:  < 0 if *pLeft < *pRight
 *                    0 if *pLeft = *pRight
 *                  > 0 if *pLeft > *pRight
 * 
 *   An arrayList will increase the amount of storage, as needed, as objects
 *   are inserted.
 *   
 *   If the user's data object involves dynammically-allocated memory, the
 *   arrayList depends on a second user-supplied function:
 * 
 *     void cleanElem(void* const pElem);
 * 
 *   If this is not needed, the user should supply a NULL pointer in lieu
 *   of a function pointer.
 * 
 *   The use of a void* in several of the relevant functions allows the
 *   user's data object to of any type; but it burdens the user with the
 *   responsibility to ensure that element pointers that are passed to
 *   arrayList functions do point to objects of the correct type.
 * 
 *   An arrayList object AL is proper iff:
 *      -  AL.data points to an array large enough to hold AL.capacity
 *         objects that each contain AL.elemSz bytes,
 *         or
 *         AL.data == NULL and AL.capacity == 0
 *      -  Cells 0 to AL.usage - 1 hold user data objects, or AL.usage == 0
 */
struct _arrayList {
	
   uint8_t* data;       // points to block of memory used to store user data
   uint32_t elemSz;     // size (in bytes) of the user's data objects
   uint32_t capacity;   // maximum number of user data objects that can be stored
   uint32_t usage;      // actual number of user data objects currently stored
   
   // User-supplied function to compare user data objects
   int32_t (*compareElems)(const void* const pLeft, const void* const pRight);
   // User-supplied function to deallocate dynamic content in user data object.
   void    (*cleanElem)(void* const pElem);

};
typedef struct _arrayList arrayList;

/**  Creates a new, empty arrayList object such that:
 * 
 *      - capacity equals dimension
 *      - elemSz equals the size (in bytes) of the data objects the user
 *        will store in the arrayList
 *      - data points to a block of memory large enough to hold capacity
 *        user data objects
 *      - usage is zero
 *      - the user's comparison function is correctly installed
 *      - the user's clean function is correctly installed, if provided

 *   Returns:  new arrayList object
 */
arrayList* AL_create(uint32_t dimension, uint32_t elemSz, 
                    int32_t (*compareElems)(const void* const pLeft, const void* const pRight),
                    void (*freeElem)(void* const pElem));

/**  Inserts the user's data object into the arrayList.
 * 
 *   Pre:     *pAL is a proper arrayList object
 *            *pElem is a valid user data object
 *   Post:    a copy of the user's data object has been inserted, at the
 *            position defined by the user's compare function
 *   Returns: true unless the insertion fails (unlikely unless it's not
 *            possible to increase the size of the arrayList
 */
bool      AL_insert(arrayList* const pAL, const void* const pElem);

/**  Removes the data object stored at the specified index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             index is a valid index for *pAL
 *   Post:     the element at index has been removed; succeeding elements
 *             have been shifted forward by one position; *pAL is proper
 *   Returns:  true unless the removal failed (most likely due to an
 *             invalid index)
 */
bool      AL_remove(arrayList* const pAL, uint32_t index);

/**  Searches for a matching object in the arrayList.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             *pElem is a valid user data object
 *   Returns:  pointer to a matching data object in *pAL; NULL if no
 *             match can be found
 */
void*     AL_find(const arrayList* const pAL, const void* const pElem);

/**  Returns pointer to the data object at the given index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             indexis a valid index for *pAL
 *   Returns:  pointer to the data object at index in *pAL; NULL if no
 *             such data object exists
 */
void*     AL_elemAt(const arrayList* const pAL, uint32_t index);

/**  Deallocates all dynamic content in the arrayList, including any
 *   dynamic content in the user data objects in the arrayList.
 * 
 *   Pre:   *pAL is a proper arrayList object
 *   Post:  the data array in *pAL has been freed, as has any dynamic
 *          memory associated with the user data objects that were in
 *          that array (via the user-supplied clean function); all the
 *          fields in *pAL are set to 0 or NULL, as appropriate.
 */
void      AL_clean(arrayList* const pAL);

#endif

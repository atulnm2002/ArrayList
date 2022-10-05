#ifndef ALTESTHELPER_H
#define ALTESTHELPER_H
#include "arrayList.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

/*** DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

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
void refAL_create(uint32_t dimension, uint32_t elemSz, 
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
bool      refAL_insert(const void* const pElem);

/**  Removes the data object stored at the specified index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             index is a valid index for *pAL
 *   Post:     the element at index has been removed; succeeding elements
 *             have been shifted forward by one position; *pAL is proper
 *   Returns:  true unless the removal failed (most likely due to an
 *             invalid index)
 */
bool      refAL_remove(arrayList* const pAL, uint32_t index);

/**  Searches for a matching object in the arrayList.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             *pElem is a valid user data object
 *   Returns:  pointer to a matching data object in *pAL; NULL if no
 *             match can be found
 */
void*     refAL_find(const arrayList* const pAL, const void* const pElem);

/**  Returns pointer to the data object at the given index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             indexis a valid index for *pAL
 *   Returns:  pointer to the data object at index in *pAL; NULL if no
 *             such data object exists
 */
void*     refAL_elemAt(uint32_t index);

/**  Deallocates all dynamic content in the arrayList, including any
 *   dynamic content in the user data objects in the arrayList.
 * 
 *   Pre:   *pAL is a proper arrayList object
 *   Post:  the data array in *pAL has been freed, as has any dynamic
 *          memory associated with the user data objects that were in
 *          that array (via the user-supplied clean function); all the
 *          fields in *pAL are set to 0 or NULL, as appropriate.
 */
void      refAL_clean(arrayList* const pAL);

/**  Performs low-level comparison of an arrayList of MLBPerson objects
 *   to the "shadow" arrayList created by runBuildingTest().
 *   Pre:   fp is open for output
 *          pAL points to a proper arrayList object
 *   Returns:  true iff *pAL matches the "shadow" arrayList
 */
bool checkList(FILE* fp, const arrayList* const pAL);

/**  Checks whether a pointer is properly aligned with respect to the
 *   boundaries of the user data objects within an arrayList.
 *   Pre:   pAL points to a proper arrayList object
 *   Returns:  true iff ptr is properly aligned
 */
bool alignmentOK(const arrayList* const pAL, void* ptr);

/**  Cleans up some internal dynamic allocations made by the test helper
 *   code.
 */
void alTestHelper_clean();

#endif

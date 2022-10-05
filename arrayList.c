#include "arrayList.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Atul Bharadwaj
// atulnm2002


// Declare any static helper functions here:
static void* binarySearch(const arrayList* const pAL, const void* const pElem, uint32_t left, uint32_t right){
  
   uint32_t mid = (left + right)/2;
   if (left > right){
      return NULL;
   }
   if (pAL->compareElems(pElem, AL_elemAt(pAL, mid)) == 0){
      return AL_elemAt(pAL, mid);
   }
   else if (pAL->compareElems(pElem, AL_elemAt(pAL, mid)) < 0){
      return binarySearch(pAL, pElem, left, mid - 1);
   }
   else {
      return binarySearch(pAL, pElem, mid + 1, right);
   }
}

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
                     void (*cleanElem)(void* const pElem)) {

   arrayList* ar = malloc(sizeof(arrayList));
   ar->capacity = dimension;
   ar->elemSz = elemSz;
   ar->data = calloc(dimension, elemSz);
   ar->usage = 0;
   ar->compareElems = compareElems;
   ar->cleanElem = cleanElem;
	return ar;
}

/**  Inserts the user's data object into the arrayList.
 * 
 *   Pre:     *pAL is a proper arrayList object
 *            *pElem is a valid user data object
 *   Post:    a copy of the user's data object has been inserted, at the
 *            position defined by the user's compare function
 *   Returns: true unless the insertion fails (unlikely unless it's not
 *            possible to increase the size of the arrayList
 */
bool AL_insert(arrayList* const pAL, const void* const pElem) {
	if (pAL->data == NULL)
      {
         return false;
      }
   if (pAL->usage == pAL->capacity){
      pAL->capacity = 2 * pAL->capacity;
      pAL->data = realloc(pAL->data, pAL->capacity * pAL->elemSz);
   }

   uint32_t i = 0;
   for (;i < pAL->usage; i++){
      if ((pAL->compareElems(pElem, pAL->data +(i*pAL->elemSz)) <= 0)){
         break;
      }
   }
   if(i<pAL->usage)
   memmove(pAL->data + ((i + 1) * pAL->elemSz), pAL->data +(i * pAL->elemSz), (pAL->usage - i) * pAL->elemSz);
   memcpy(pAL->data + (i * pAL->elemSz), pElem, pAL->elemSz);
   pAL->usage = pAL->usage + 1;
   return true;
}

/**  Removes the data object stored at the specified index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             index is a valid index for *pAL
 *   Post:     the element at index has been removed; succeeding elements
 *             have been shifted forward by one position; *pAL is proper
 *   Returns:  true unless the removal failed (most likely due to an
 *             invalid index)
 */
bool AL_remove(arrayList* const pAL, uint32_t index) {
	if(pAL->capacity > 0){
      index = index + 1;
   }
	return false;

}

/**  Searches for a matching object in the arrayList.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             *pElem is a valid user data object
 *   Returns:  pointer to a matching data object in *pAL; NULL if no
 *             match can be found
 */
void* AL_find(const arrayList* const pAL, const void* const pElem) {

   return binarySearch(pAL, pElem, 0, pAL->usage);

}

/**  Returns pointer to the data object at the given index.
 * 
 *   Pre:      *pAL is a proper arrayList object
 *             indexis a valid index for *pAL
 *   Returns:  pointer to the data object at index in *pAL; NULL if no
 *             such data object exists
 */
void* AL_elemAt(const arrayList* const pAL, uint32_t index) {
   if (index >= pAL->usage){
      return NULL;
   }
	return pAL->data + (index * pAL->elemSz);

}

/**  Deallocates all dynamic content in the arrayList, including any
 *   dynamic content in the user data objects in the arrayList.
 * 
 *   Pre:   *pAL is a proper arrayList object
 *   Post:  the data array in *pAL has been freed, as has any dynamic
 *          memory associated with the user data objects that were in
 *          that array (via the user-supplied clean function); all the
 *          fields in *pAL are set to 0 or NULL, as appropriate.
 */
void AL_clean(arrayList* const pAL) {

      for (uint32_t i = 0; i < pAL->usage; i++){
         pAL->cleanElem(AL_elemAt(pAL, i));
      }
      free(pAL->data);
}

// Implement static helper functions below:


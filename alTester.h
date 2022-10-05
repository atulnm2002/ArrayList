#ifndef ALTESTER_H
#define ALTESTER_H
#include <stdio.h>
#include <stdbool.h>
#include "arrayList.h"

/*** DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

/**  Attempts to create an arrayList object and populate it with MLBPerson
 *   objects, created from the previously-created MLB data file.
 *   Pre:   dbFile is open for reading on a file of MLB data
 *   Post:  an arrayList has been created storing MLPPerson objects created
 *             from the data in dbFile;
 *          a "shadow" arrayList has been created using the reference 
 *             implementation and the same data objects
 *   Returns:  pointer to the new arrayList; NULL if it was not created
 */
arrayList* runBuildingTest(FILE* dbFile);

/**  Tests the AL_elemAt() function on an arrayList of MLBPerson objects.
 *   Pre:   pAL points to an arrayList of MLBPerson objects, created by
 *             a call to runBuildingTest() 
 *   Returns:  true iff AL_elemAt() passed all tests
 */
bool runElemAtTest(const arrayList* const pAL);

/**  Tests the AL_Find() function on an arrayList of MLBPerson objects.
 *   Pre:   pAL points to an arrayList of MLBPerson objects, created by
 *             a call to runBuildingTest() 
 *   Returns:  true iff AL_Find() passed all tests
 */
bool runFindTest(const arrayList* const pAL);

/**  Utility function used by runBuildingTest(); provided for users who
 *   want to create an arrayList and perform their own testing.
 *   Pre:   dbFile is open for reading on a file of MLB data
 *   Returns:  pointer to the new arrayList; NULL if it was not created
 */  
arrayList* AL_builder(FILE* dbFile);

/**  Triggers cleanup of memory associated with the "shadow" arrayList
 *   created by runBuildingTest().
 */
void alTester_clean();

/**  Prints a formatted display of the MLBPerson objects in an arrayList.
 *   Pre:   fp is open for writing
 *          pAL points to a proper arrayList of MLBPerson objects
 */
void printList(FILE* fp, const arrayList* const pAL);

#endif

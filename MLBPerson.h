#ifndef MLBPERSON_H
#define MLBPERSON_H
#include <stdio.h>
#include <inttypes.h>

/*** DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

/**  Data type to organize some information about personnel in MLB, where
 *   each datum is a dynamically-allocated C-string.
 * 
 *   An MLBPerson object is proper iff:
 *     - each pointer is either NULL, or
 *       points to a properly-terminated C-string
 */
struct _MLBPerson {
	char* id;
	char* name;
	char* firstGame;
	char* lastGame;
};
typedef struct _MLBPerson MLBPerson;

/**  Creates an MLBPerson object from a string consisting of the following
 *   fields, in the order listed, delimited by single tab characters:
 * 
 *     1:  playerID
 *     2:  first name
 *     3:  last name
 *     4:  date of first game
 *     5:  date of final game
 * 
 *   Pre:  *str is in the format described above
 *   Returns:  a proper MLBPerson object holding the data supplied in *str
 */
MLBPerson MLBP_create(const char* const str);

/**  Prints a formatted display of the contents of a MLBPerson object.
 *   Pre:  fp is open for output
 *         record is a proper MLBPerson object
 */
void      MLBP_print(FILE* fp, MLBPerson record);

/**  Compares the name fields of two MLBPerson objects.
 *   Pre:  pLeft and pRight point to proper MLBPerson objects with 
 *            non-NULL name fields.
 *   Returns:  < 0  if pLeft-> name precedes pRight->name
 *             = 0  if pLeft-> name equals pRight->name
 *             > 0  if pLeft-> name succeeds pRight->name
 */
int32_t   MLBP_compare(const void* const pLeft, const void* const pRight);

/**  Deallocates the dynamic memory content of an MLBPerson object.
 *   Pre:   *pMLBP is a proper MLBPerson object
 */
void      MLBP_clean(void* const pMLBP);

#endif

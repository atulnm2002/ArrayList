#ifndef MLBSELECTOR_H
#define MLBSELECTOR_H
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#define MAX_DBLINE 100       // maximum length of a line in the MLB data file
#define MAX_LINES  10000     

/*** DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

/**  Extracts a random subset of records from the master MLB data file
 *   and writes them to a new file.
 *   Pre:   dbFile is opened for output
 *          MLB.txt is in the current directory
 *          nRequested is the number of desired records
 *   Post:  dbFile contains nRequested MLB records
 *   Returns:  true iff the requested number of records were extracted
 *                and written to dbFile
 */
bool chooseRecords(FILE* dbFile, FILE* dataSource, uint32_t nRequested);

#endif
 

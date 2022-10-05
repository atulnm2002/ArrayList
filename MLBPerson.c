#include "MLBPerson.h"
#include <stdlib.h>
#include <string.h>

static char* copyOf(const char* const str);

/**  Creates an MLBPerson object from a string consisting of the following
 *   fields, in the order listed, delimited by single tab characters:
 * 
 *     1:  playerID
 *     2:  first name
 *     3:  last name
 *     4:  date of first game
 *     5:  date of final game
 */
MLBPerson MLBP_create(const char* const str) {
	
	MLBPerson record = {NULL, NULL, NULL, NULL};
	
	char* cpy = copyOf(str);
	
	record.id        = copyOf( strtok(cpy, "\t") );
	char* firstName  = strtok(NULL, "\t");
	char* lastName   = strtok(NULL, "\t");
	record.name = calloc(strlen(firstName) + strlen(lastName) + 3, sizeof(char));
	strcpy(record.name, lastName);
	strcat(record.name, ", ");
	strcat(record.name, firstName);
	record.firstGame = copyOf( strtok(NULL, "\t") );
	record.lastGame  = copyOf( strtok(NULL, "\t") );
	
	free( cpy );
	return record;
}

void MLBP_print(FILE* fp, MLBPerson record) {
	
	if ( record.id != NULL ) {
	   fprintf(fp, "ID:     %s\n", record.id);
	}
	else {
	   fprintf(fp, "ID:     <not provided>\n");
	}
	if ( record.id != NULL ) {
   	   fprintf(fp, "Name:   %s\n", record.name);
	}
	else {
   	   fprintf(fp, "Name:   <not provided>\n");
	}
	if ( record.firstGame != NULL ) {
	   fprintf(fp, "Debut:  %s\n", record.firstGame);
	}
	else {
	   fprintf(fp, "Debut:  <not provided>\n");
	}
	if ( record.lastGame != NULL ) {
	   fprintf(fp, "Finale: %s\n", record.lastGame);
	}
	else {
	   fprintf(fp, "Finale: <not provided>\n");
	}
}

int32_t MLBP_compare(const void* const pLeft, const void* const pRight){
	
	const MLBPerson* left  = (MLBPerson*) pLeft;
	const MLBPerson* right = (MLBPerson*) pRight;
	
	return strcmp(left->name, right->name);
}

void MLBP_clean(void* const pMLBP) {
	
	MLBPerson record = *(MLBPerson*) pMLBP;
	
	free(record.id);
	free(record.name);
	free(record.firstGame);
	free(record.lastGame);
}

//-------------------------------------------------------------------- private
static char* copyOf(const char* const str) {
	
	if ( str == NULL ) {
		return calloc(1, sizeof(char));
	}
	
	char* copy = calloc(strlen(str) + 1, sizeof(char));
    strcpy(copy, str);	
	
	return copy;
}


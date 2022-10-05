#include "mlbSelector.h"
#include <stdio.h>

char* masterDB = "MLB.txt";      // name of master MLB data file
const uint32_t dbSize = 19892;   // hardwired for the supplied file

static bool eatLines(FILE* fp, uint32_t toSkip);

bool chooseRecords(FILE* dbFile, FILE* dataSource, uint32_t nRequested) {
	
	uint32_t skipDistance = dbSize / nRequested;
	uint32_t nSelected = 0;
	char line[MAX_DBLINE];
	
	// eat header line
	fgets(line, MAX_DBLINE, dataSource);
	
	while ( nSelected < nRequested && fgets(line, MAX_DBLINE, dataSource) != NULL ) {
       nSelected++;		
	   fprintf(dbFile, "%s", line);
	   if ( !eatLines(dataSource, skipDistance) ) {
		   printf("Error skipping lines in master database file\n");
		   return false;
	   }
	}
	
	return (nSelected == nRequested);
}

static bool eatLines(FILE* fp, uint32_t toSkip) {
	
	char line[MAX_DBLINE];
	uint32_t nSkipped = 0;
	
	while ( nSkipped < toSkip && fgets(line, MAX_DBLINE, fp) != NULL ) {
       nSkipped++;		
	}
	return (nSkipped = toSkip);
}



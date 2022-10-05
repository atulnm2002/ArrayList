#include "alTester.h"
#include "alTestHelper.h"
#include "MLBPerson.h"
#include "mlbSelector.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

arrayList* runBuildingTest(FILE* dbFile) {
	
	FILE* fp = fopen("buildLog.txt", "w");
	if ( fp == NULL ) {
		printf("Unable to create build log.\n");
		return NULL;
	}
	
	fprintf(fp, "Beginning test of AL_elemAt()...\n\n");

	fprintf(fp, "   Building an arrayList from the MLB data file...\n");
	arrayList* pAL = AL_builder(dbFile);
	
	fprintf(fp, "   Comparing your arrayList to the reference arrayList...\n");
	bool passed = checkList(fp, pAL);
	if ( !passed ) {
		pAL = NULL;
	}
	
	fclose(fp);
	return pAL;
}

arrayList* AL_builder(FILE* dbFile) {
	
    arrayList* pAL = AL_create(32, sizeof(MLBPerson), MLBP_compare, MLBP_clean);
    refAL_create(32, sizeof(MLBPerson), MLBP_compare, MLBP_clean);
    
    if ( pAL == NULL ) return NULL;
    
    char dbLine[MAX_DBLINE];
    
    while ( fgets(dbLine, MAX_DBLINE, dbFile) != NULL ) {
		
		//printf("read:  %s\n", dbLine);
	    MLBPerson person = MLBP_create(dbLine);
	    MLBPerson percpy = MLBP_create(dbLine);
	    
        AL_insert(pAL, (void*) &person);
        refAL_insert((void*) &percpy);
	}
	
	return pAL;
}

bool runElemAtTest(const arrayList* const pAL) {
	
	FILE* fp = fopen("elemAtLog.txt", "w");
	if ( fp == NULL ) {
		printf("Unable to create search log.\n");
		return false;
	}
	
	fprintf(fp, "Beginning test of AL_elemAt()...\n\n");
	uint32_t ptsPerCase = 10;
	uint32_t score = 0;
	
	bool success = true;
	bool *checked = calloc(pAL->usage, sizeof(bool));
	
	uint32_t numCases = 10;
	uint32_t listSz = pAL->usage;
	
	for (uint32_t test = 1; test <= numCases; test++) {
		
		fprintf(fp, "Test case %"PRIu32":\n", test);
		
		uint32_t caseIdx = rand() % listSz;
		while ( checked[caseIdx] ) {
			caseIdx = (caseIdx + 1) % pAL->usage;
		}
		checked[caseIdx] = true;
		
		fprintf(fp, "   Looking for the record at index %"PRIu32"\n", caseIdx);
		
		MLBPerson* pSought = (MLBPerson*)  refAL_elemAt(caseIdx);
		
		fprintf(fp, "   Calling AL_elementAt(%"PRIu32")...\n", caseIdx);
		MLBPerson* found = AL_elemAt(pAL, caseIdx);
		
		if ( !alignmentOK(pAL, found) ) {
			fprintf(fp, "   Returned pointer is misaligned: %p\n", found);
			fprintf(fp, "   We are not going to dereference that...\n");
			success = false;
		}
		else if ( found == NULL ) {
			fprintf(fp, "   Bummer, got NULL back for %s\n", pSought->name);
			success = false;
		}
		else if ( MLBP_compare(pSought, found) != 0 ) {
			fprintf(fp, "   Bummer, MLBP_compare() says the found record is not a match\n");
			fprintf(fp, "   Name field of found record is: >>%s<<\n", found->name);
			fprintf(fp, "   Note that the prevous output may be garbage if your pointer was bad\n");
			success = false;
		}
		else {
			fprintf(fp, "   MLBP_compare() says the found record is a match\n");
			score += 10;
		}
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "2 >> Score for AL_elemAt():  %"PRIu32" / %"PRIu32"\n", score, ptsPerCase * numCases);
	fclose(fp);
	
	free(checked);
    return success;
}

bool runFindTest(const arrayList* const pAL) {
	
	FILE* fp = fopen("findLog.txt", "w");
	if ( fp == NULL ) {
		printf("Unable to create search log.\n");
		return false;
	}
	
	fprintf(fp, "Beginning test of AL_Find()...\n\n");
	uint32_t ptsPerCase = 10;
	uint32_t score = 0;
	
	bool success = true;
	bool *checked = calloc(pAL->usage, sizeof(bool));
	
	uint32_t numCases = 10;
	uint32_t listSz = pAL->usage;
	
	for (uint32_t test = 1; test <= numCases; test++) {
		
		fprintf(fp, "Test case %"PRIu32":\n", test);
		
		uint32_t caseIdx = rand() % listSz;
		while ( checked[caseIdx] ) {
			caseIdx = (caseIdx + 1) % pAL->usage;
		}
		checked[caseIdx] = true;
		
		MLBPerson* pSought = (MLBPerson*)  refAL_elemAt(caseIdx);
		fprintf(fp, "   Looking for a match for :  %s\n", pSought->name);
		
		fprintf(fp, "   Calling AL_Find(%s)...\n", pSought->name);
		MLBPerson* found = AL_find(pAL, pSought);
		
		if ( !alignmentOK(pAL, found) ) {
			fprintf(fp, "   Returned pointer is misaligned: %p\n", found);
			fprintf(fp, "   We are not going to dereference that...\n");
			success = false;
		}
		else if ( found == NULL ) {
			fprintf(fp, "   Bummer, got NULL back for %s\n", pSought->name);
			success = false;
		}
		else if ( MLBP_compare(pSought, found) != 0 ) {
			fprintf(fp, "   Bummer, MLBP_compare() says the found record is not a match\n");
			fprintf(fp, "   Name field of found record is: >>%s<<\n", found->name);
			fprintf(fp, "   Note that the prevous output may be garbage if your pointer was bad\n");
			success = false;
		}
		else {
			fprintf(fp, "   MLBP_compare() says the found record is a match\n");
			score += ptsPerCase;
		}
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "3 >> Score for AL_Find():  %"PRIu32" / %"PRIu32"\n", score, ptsPerCase * numCases);
	fclose(fp);

	free(checked);
	return success;
}

void printList(FILE* fp, const arrayList* const pAL) {
	
	fprintf(fp, "arrayList attributes:\n");
	fprintf(fp, "Elem size: %4"PRIu32"\n", pAL->elemSz);
	fprintf(fp, "Capacity:  %4"PRIu32"\n", pAL->capacity);
	fprintf(fp, "Usage:     %4"PRIu32"\n", pAL->usage);
	fprintf(fp, "\n");
	fprintf(fp, "arrayList contents:\n");
	for (uint32_t idx = 0; idx < pAL->usage; idx++) {
		
		MLBPerson record = *(MLBPerson*) AL_elemAt(pAL, idx);
		fprintf(fp, "slot:%5"PRIu32"\n", idx);
		MLBP_print(fp, record);
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
}

void alTester_clean() {
	
	alTestHelper_clean();
}

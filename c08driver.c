//  Test driver for ordered arrayList project.
//
//  Necessary files:
//     c08driver.c
//        manages generation of test data and execution of tests
//     arrayList.h and arrayList.c
//        implementation of ordered arrayList data structure
//     alTester.h and alTester.c
//        top-level test functions and some utility functions
//     alTestHelper.h and alTestHelper.o
//        low-level test functions, reference soln
//     MLBPerson.h and MLBPerson.c
//        data type used in testing
//     mlbSelector.h and mlbSelector.c
//        selects test data from master MLB data file
//     MLB.txt
//        master data file; data for ~20,000 MLB personnel
//
//  Build instruction:
//     gcc -o c08 -std=c11 -Wall -W c08driver.c arrayList.c alTester.c alTestHelper.o MLBPerson.c mlbSelector.c
//
//  Execution for basic testing:
//     c08 <# tests> <test data file> <master data file>
//        # tests is the desired number of test cases; no more than 50
//        test data file will be created and hold the chosen test cases
//        master data file is the supplied file of all possible test cases
//
//  Basic operation:
//     Creates the following files (if successful):
//        text file holding a subset of the records in the master data file
//        buildLog.txt
//        elemAtLog.txt
//        findLog.txt
//
//  Score data should be found at the end of each log file, unless a runtime error
//  occurs.  The tests are executed sequentially.  If any test fails, the others
//  are not performed.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mlbSelector.h"   // date selector supplies test data file
#include "arrayList.h"     // spec'd arrayList interface
#include "MLBPerson.h"     // data type used in testing
#include "alTester.h"      // top-level test functions

int main(int argc, char** argv) {

   // Check for correct number of command-line arguments:
   if ( argc != 4 ) {
      printf("Invocation: %s <# records requested> <name of data file to create> <name of master data file>\n", argv[0]);
      return -1;
   }
   
   uint32_t dataSz = atoi(argv[1]);
   if ( dataSz > 50 ) {
      printf("Must request no more than 50 records, not %"PRIu32"\n", dataSz);
      return -2;
   }
    
   // Create the file to hold the selected MLB records:
   FILE* MLBPFile = fopen(argv[2], "w");
   if ( MLBPFile == NULL ) {
      printf("Error, could not open %s\n", argv[2]);
      return -3;
   }
   
   FILE* MLBPsource = fopen(argv[3], "r");
   if ( MLBPsource == NULL ) {
      printf("Error, could not open %s\n", argv[3]);
      return -4;
   }

   // Select some MLB records:
   if ( !chooseRecords(MLBPFile, MLBPsource, dataSz) ) {
      printf("Unable to create requested data file: %s\n", argv[1]);
      return -5;
   }
   // We are done with the master data file, so close it:
   fclose(MLBPsource);
   // We are done with writing the data file, so close it:
   fclose(MLBPFile);
   
   // Reopen the data file for reading:
   MLBPFile = fopen(argv[2], "r");
   
   // Test the ability to create an arrayList and put data elements in it:
   printf("Beginning test of arrayList building...\n");
   arrayList* pAL = runBuildingTest(MLBPFile);
    
   // We are done with the data file, so close it:
   fclose(MLBPFile);
    
   // The previous test should have created an arrayList and returned a
   // pointer to it; if not, we are done:
   if ( pAL == NULL ) {
      printf("Failed to create an arrayList!\n");
      return -4;
   }
   
   // If we created and populated an arrayList, test AL_elemAt():
   printf("Beginning test of AL_elemAt()...\n");
   if ( !runElemAtTest( pAL ) ) {
      printf("Failed test of Al_elemAt()... see elemAtLog.txt for details.\n");
      AL_clean(pAL);
      free(pAL);
      return -5;
   }
   
   // If elemAt() passed testing, test AL_find():
   printf("Beginning test of AL_find()...\n");
   if ( !runFindTest( pAL ) ) {
      printf("Failed test of Al_find()... see findLog.txt for details.\n");
      AL_clean(pAL);
      free(pAL);
      return -5;
   }
   
   // Deallocate all dynamic content for the arrayList; this can only be 
   // verified by running the program on Valgrind:
   AL_clean( pAL );
   
   // The arrayList object itself was allocated dynammically, so we need
   // to deallocate it as well:
   free( pAL );
   
   // And... make a call to clean up the memory assocated with the reference
   // arrayList created during testing:
   alTester_clean();
    
   return 0;
}


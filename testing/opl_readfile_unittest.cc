/* STUDENTS:  DO NOT EDIT THIS FILE.  INSTEAD, MODIFY YOUR OWN PROJECT
 * CODE TO FIT THE SPECIFICATION GIVEN BY THE TESTS IN THIS FILE.
 *
 * If you DO modify it, we overwrite it with a fresh version from our repo
 * when grading, so you can't use it to fudge the tests anyway.
 *
 * This file is used by the CS5801 auto-grading system.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */
/*******************************************************************************
* This test file are inspired by CS5801 Fall 2019
******************************************************************************/
 #ifdef OPL_READFILE_TESTS

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <gtest/gtest.h>
#include "src/opl.h"

class OPLReadFileTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize anything for TESTS
  }

  OPL *opl = new OPL();
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

/*******************************************************************************
 * OPL ReadFile
 * - Input: a sample csv file
 * - Testing: value in the report after readfile.
 ******************************************************************************/
TEST_F(OPLReadFileTest, ReadFile) {
  opl->ReadFile("opl.csv");
  EXPECT_EQ(opl->report_.GetNumTotalCandidates(), 7 ) << "FAIL: OPLReadFileTest:ReadFile - TotalCandidates is incorrect";
  EXPECT_EQ(opl->report_.GetNumBallots(), 100 ) << "FAIL: OPLReadFileTest:ReadFile - NumBallots is incorrect";
  EXPECT_EQ(opl->report_.GetNumTotalSeats(), 5 ) << "FAIL: OPLReadFileTest:ReadFile - TotalSeats is incorrect";
  /* There should be more for checking party and candidates.
  * However, at this point, report are incomplete
  * Still wait for the report to fully check other values.
  **/
};


#endif  // OPL_READFILE_TESTS

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
 #ifdef OPL_AUDIT_EFFICIENCY

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <ctime>
#include <cmath>
#include <gtest/gtest.h>
#include "src/opl.h"
#include <string>
#include <unistd.h>
using namespace std;
class OPLAuditEfficiency : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize anything for TESTS
    opl->ReadFile("opl_large_1.csv");
  }

  OPL *opl = new OPL();
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(OPLAuditEfficiency, AuditOPLFile) {
  opl->Audit();
  EXPECT_EQ(opl->report_.GetNumTotalCandidates(), 7 ) << "FAIL: oplReadFileTest:ReadFile - TotalCandidates is incorrect";
  EXPECT_EQ(opl->report_.GetNumBallots(), 5000 ) << "FAIL: oplReadFileTest:ReadFile - NumBallots is incorrect";
  EXPECT_EQ(opl->report_.GetNumTotalSeats(), 5 ) << "FAIL: oplReadFileTest:ReadFile - TotalSeats is incorrect";

  clock_t start, end;

  start = clock();
  opl->Audit();
  end = clock();
  float t = (float)(end - start)/CLOCKS_PER_SEC;

  // Testing if Audit runs in under a minute
  // Testing for 500,000, but scaled up to save memory
  EXPECT_LT(t * 100, 60) << "FAIL";

  EXPECT_EQ(opl->report_.GetWinnerParty().size(), 2 ) << "FAIL: GetWinnerParty";
  EXPECT_EQ(opl->report_.GetWinnerParty()[0].list_candidates_.size(), 3 ) << "FAIL";
  EXPECT_EQ(opl->report_.GetWinnerParty()[1].list_candidates_.size(), 2 ) << "FAIL";
  
};

#endif  // OPL_AUDIT_EFFICIENCY
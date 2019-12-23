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
 #ifdef CPL_AUDIT_EFFICIENCY

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <ctime>
#include <cmath>
#include <gtest/gtest.h>
#include "src/cpl.h"
#include <unistd.h>
class CPLAuditEfficiency : public ::testing::Test {

 protected:
  virtual void SetUp() {
    // Initialize anything for TESTS
    cpl->ReadFile("cpl_large_1.csv");
  }

  CPL *cpl = new CPL();
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(CPLAuditEfficiency, AuditFile) {

  clock_t start, end;

  start = clock();
  cpl->Audit();
  end = clock();
  float t = (float)(end - start)/CLOCKS_PER_SEC;

  // Testing if Audit runs in under a minute
  // Testing for 500,000, but scaled up to save memory
  EXPECT_LT(t * 100, 60) << "FAIL";


  EXPECT_EQ(cpl->report_.GetNumTotalCandidates(), 17 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetNumBallots(), 5000 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetNumTotalSeats(), 10 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetNumTotalSeats(), 10 ) << "FAIL";

  EXPECT_EQ(cpl->report_.GetWinnerParty().size(), 4 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetWinnerParty()[0].GetBallotList().size(), 1400 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetWinnerParty()[1].GetBallotList().size(), 1400 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetWinnerParty()[2].GetBallotList().size(), 1200 ) << "FAIL";
  EXPECT_EQ(cpl->report_.GetWinnerParty()[3].GetBallotList().size(), 1000 ) << "FAIL";

  // Testing if each party at least gets 2 seats, for quota = 5000/10 = 500
  EXPECT_GE(cpl->report_.GetWinnerParty()[0].list_candidates_.size(), 2 ) << "FAIL";
  EXPECT_GE(cpl->report_.GetWinnerParty()[1].list_candidates_.size(), 2 ) << "FAIL";
  EXPECT_GE(cpl->report_.GetWinnerParty()[2].list_candidates_.size(), 2 ) << "FAIL";
  EXPECT_GE(cpl->report_.GetWinnerParty()[3].list_candidates_.size(), 2 ) << "FAIL";

};

#endif  // CPL_AUDIT_EFFICIENCY
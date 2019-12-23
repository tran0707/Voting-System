/*******************************************************************************
* This test file are inspired by CS5801 Fall 2019
******************************************************************************/
 #ifdef PARTY_TESTS
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "src/party.h"
#include "src/candidate.h"
#include <cmath>
#include <iostream>
#include <gtest/gtest.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>

class PartyTests : public ::testing::Test {
  protected:
    Party * party;
    Candidate *cand1, *cand2, *cand3, *cand4;
    std::vector<Candidate> cand_vec;
    std::vector <int> list_ballot_id_{};
    virtual void SetUp() {
      cand1 = new Candidate("Benjamin" , 1);
      cand2 = new Candidate("Sam" , 2);
      cand3 = new Candidate("Steve" , 3);
      cand4 = new Candidate("Alice" , 4);
      cand1->list_ballot_id_.push_back(1);
      cand1->list_ballot_id_.push_back(2);
      cand2->list_ballot_id_.push_back(3);
      cand2->list_ballot_id_.push_back(4);
      party = new Party();
    }

    virtual void TearDown() {
      delete party;
      delete cand1;
      delete cand2;
      delete cand3;
      delete cand4;
    }
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PartyTests, AddCandidateTests) {
  party->AddCandidate(*cand1);
  party->AddCandidate(*cand2);
  party->AddCandidate(*cand3);
  party->AddCandidate(*cand4);
  cand_vec = party->GetCandidates();
  EXPECT_EQ( static_cast<int> (cand_vec.size()), 4) << "Fail: To add candidate name";
  EXPECT_EQ(cand_vec[0].GetName().compare("Benjamin"), 0) << "Fail: To add candidate name";
  EXPECT_EQ(cand_vec[1].GetName().compare("Sam"), 0) << "Fail: To add candidate name";
  EXPECT_EQ(cand_vec[2].GetName().compare("Steve"), 0) << "Fail: To add candidate name";
  EXPECT_EQ(cand_vec[3].GetName().compare("Alice"), 0) << "Fail: To add candidate name";
};

TEST_F(PartyTests, AddBallotIdTests) {
  party->AddBallotId(1);
  party->AddBallotId(2);
  party->AddBallotId(3);
  party->AddBallotId(4);
  list_ballot_id_ = party->GetBallotList();
  EXPECT_EQ(static_cast<int> (party->GetBallotList().size()), 4) << "Fail: To add Ballot ID name";
  EXPECT_EQ(list_ballot_id_[0], 1) << "Fail: To add Ballot ID name";
  EXPECT_EQ(list_ballot_id_[1], 2) << "Fail: To add Ballot ID name";
  EXPECT_EQ(list_ballot_id_[2], 3) << "Fail: To add Ballot ID name";
  EXPECT_EQ(list_ballot_id_[3], 4) << "Fail: To add Ballot ID name";
};


#endif   // PARTY_TESTS

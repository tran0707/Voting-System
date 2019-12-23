/**
 * @file report_UT.cc
 * @author Team#22
 * @brief Unit Test for Report class
 * @version 0.1
 * @date 2019-11-17
 *
 * @copyright Copyright (c) 2019
 *
 */


#ifdef REPORT_UNIT_TESTS

#include <gtest/gtest.h>
#include "../src/report.h"
#include "../src/party.h"
#include "../src/candidate.h"
#include "../src/cpl.h"
#include "../src/opl.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class ReportUnitTests : public ::testing::Test
{
protected:
  virtual void SetUp() {
    // All Candidates
    cand1 = new Candidate("Davis", 1);
    cand2 = new Candidate("Victor", 2);
    cand3 = new Candidate("Frank", 1);
    cand4 = new Candidate("Janifer", 2);

    // Add list ballot id for each candidates
    cand1->list_ballot_id_.push_back(1);
    cand1->list_ballot_id_.push_back(2);
    cand2->list_ballot_id_.push_back(3);
    cand2->list_ballot_id_.push_back(4);
    cand2->list_ballot_id_.push_back(5);
    cand3->list_ballot_id_.push_back(6);
    cand3->list_ballot_id_.push_back(7);
    cand3->list_ballot_id_.push_back(8);
    cand3->list_ballot_id_.push_back(9);
    cand4->list_ballot_id_.push_back(10);

    // Push each candidate into 2 different vector
    cand_vec_1.push_back(*cand1);
    cand_vec_1.push_back(*cand2);
    cand_vec_2.push_back(*cand3);
    cand_vec_2.push_back(*cand4);

    // Add candidate vector and party name into parties
    pa1 = new Party("D", cand_vec_1);
    pa2 = new Party("R", cand_vec_2);

    // Add Ballot Id into 2 Party
    pa1->AddBallotId(1);
    pa1->AddBallotId(2);
    pa1->AddBallotId(3);
    pa1->AddBallotId(4);
    pa1->AddBallotId(5);
    pa2->AddBallotId(6);
    pa2->AddBallotId(7);
    pa2->AddBallotId(8);
    pa2->AddBallotId(9);
    pa2->AddBallotId(10);
    pa1->SetNumSeats(1);
    pa2->SetNumSeats(1);

    // push two party into a party_vec vector
    party_vec.push_back(*pa1);
    party_vec.push_back(*pa2);

    // For Winner Candidates
    cand_winner1.push_back(*cand2);
    cand_winner2.push_back(*cand3);
    pa3 = new Party("D", cand_winner1);
    pa4 = new Party("R", cand_winner2);
    pa3->SetNumSeats(1);
    pa4->SetNumSeats(1);
    pa3->AddBallotId(3);
    pa3->AddBallotId(4);
    pa3->AddBallotId(5);
    pa3->SetNumVotes(3);
    pa4->AddBallotId(6);
    pa4->AddBallotId(7);
    pa4->AddBallotId(8);
    pa4->AddBallotId(9);
    pa4->SetNumVotes(4);
    winner_party.push_back(*pa3);
    winner_party.push_back(*pa4);

    // OPL Setter
    reportOPL->SetVotingType("OPL");
    reportOPL->SetNumToTalCandidates(4);
    reportOPL->SetNumBallots(10);
    reportOPL->SetNumTotalSeats(2);
    reportOPL->SetVecAllParty(party_vec);
    reportOPL->SetVecWinnerParty(winner_party);
    reportOPL->SetFileAuditing("opl.txt");

    // CPL Setter
    reportCPL->SetVotingType("CPL");
    reportCPL->SetNumToTalCandidates(4);
    reportCPL->SetNumBallots(10);
    reportCPL->SetNumTotalSeats(2);
    reportCPL->SetVecAllParty(party_vec);
    reportCPL->SetVecWinnerParty(winner_party);
    reportCPL->SetFileAuditing("cpl.txt");
  }

  virtual void TearDown() {
    delete reportOPL;
    delete reportCPL;
    delete pa1;
    delete pa2;
    delete pa3;
    delete pa4;
    delete cand1;
    delete cand2;
    delete cand3;
    delete cand4;
  }
  Report *reportOPL = new Report();
  Report *reportCPL = new Report();
  Party *pa1, *pa2, *pa3 , *pa4;
  Candidate *cand1, *cand2 , *cand3, *cand4;
  std::vector <Candidate> cand_vec_1, cand_vec_2, cand_winner1, cand_winner2;
  std::vector <Party> party_vec, winner_party;

  /**
   * @brief check if a file is exist in the current directory
   *
   * @param name
   * @return true
   * @return false
   */
  bool exists_file (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
  }

  /**
   * @brief Get the last word of second line of a file
   *
   * @param file
   * @return string
   */
  string find_last_word_of_sec_line(string file) {
    int count_run = 0;
    string text;
    ifstream infile(file);
    while (infile.good()) {
      count_run++;
      getline(infile, text);
      if (count_run == 1) {
        getline(infile, text);
        break;
      }
    }
    int i = text.length() - 1;
    while (i != 0 && !isspace(text[i])) {
      --i;
    }
    return text.substr(i+1);
  }

};

// TEST if two display function for CPL and OPL execute successfully
TEST_F(ReportUnitTests, ReportDisplayRunTest) {
  reportOPL->Display();
  reportCPL->Display();
  EXPECT_EQ(1,1) << "FAIL: Display functions are not called";
};

// TEST if the export to audit and export to public for OPL can execute successfully.
// ALSO, test for a opl audit file and a opl share file created with the right voting type
TEST_F(ReportUnitTests, OPLExportsFileCreatedTests) {
  reportOPL->SetFileAuditing("audit_result.txt");
  reportOPL->ExportToAuditFile();
  EXPECT_EQ(exists_file("audit_result.txt"), true) << "FAIL: Exists File Audit OPL in Report Unittest Failed";
  EXPECT_EQ(find_last_word_of_sec_line("audit_result.txt"),"OPL") << "FAIL: OPL Audit Created File with Wrong Voting Type";

  reportOPL->SetFileAuditing("sharing_result.txt");
  reportOPL->ExportToPublicFile();
  EXPECT_EQ(exists_file("sharing_result.txt"), true) << "FAIL: Exists File Share OPL in Report Unittest Failed";
  EXPECT_EQ(find_last_word_of_sec_line("sharing_result.txt"),"OPL") << "FAIL: OPL Share Created File with Wrong Voting Type";

  // Remove the output of the export filed after tested
  std::remove("audit_result.txt");
  std::remove("sharing_result.txt");
};

// TEST if the export to audit and export to public for CPL can execute successfully.
// ALSO, test for a cpl audit file and a cpl share file created with the right voting type
TEST_F(ReportUnitTests, CPLExportsFileCreatedTests) {
  reportCPL->SetFileAuditing("audit_result.txt");
  reportCPL->ExportToAuditFile();
  EXPECT_EQ(exists_file("audit_result.txt"), true) << "FAIL: Exists File Audit CPL in Report Unittest Failed";
  EXPECT_EQ(find_last_word_of_sec_line("audit_result.txt"),"CPL") << "FAIL: CPL Audit Created File with Wrong Voting Type";

  reportCPL->SetFileAuditing("sharing_result.txt");
  reportCPL->ExportToPublicFile();
  EXPECT_EQ(exists_file("sharing_result.txt"), true) << "FAIL: Exists File Share CPL in Report Unittest Failed";
  EXPECT_EQ(find_last_word_of_sec_line("sharing_result.txt"),"CPL") << "FAIL: CPL Audit Created File with Wrong Voting Type";

  // Remove the output of the export filed after tested
  std::remove("audit_result.txt");
  std::remove("sharing_result.txt");
};

// TEST for the ExtractFileName helper function of Report class
TEST_F(ReportUnitTests, ExtractFileNameFunctionTests) {
  EXPECT_EQ(reportOPL->ExtractFileName("opl.csv"), "opl") << "FAIL: Extract OPL Name Failed";
  EXPECT_EQ(reportOPL->ExtractFileName("cpl.csv"), "cpl") << "FAIL: Extract CPL Name Failed";
};

// TEST for the FindLongestCPLCandidateName helper function of Report class
TEST_F(ReportUnitTests, FindLongestStringFunctionTests) {
  EXPECT_EQ(reportOPL->FindLongestCPLCandidateName(party_vec), 14) << "FAIL: NOT the longest Name of Candidate";
  EXPECT_EQ(reportCPL->FindLongestCPLCandidateName(party_vec), 14) << "FAIL: NOT the longest Name of Candidate";
};

#endif // REPORT_UNIT_TESTS

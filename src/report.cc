/**
 * @file report.cc
 * @author Team#22
 * @brief Report.cc
 * @version 0.1
 * @date 2019-11-16
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iomanip>
#include "report.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>
#include "params.h"
using namespace std;

Report::Report(std::vector <Party> all_parties_vec,
    std::vector <Party> winner_vec,
    std::string vote_type, int total_candidates, int nballots,
    int total_seats, std::string file) {
        AllCandidateParty = all_parties_vec;
        Winner = winner_vec;
        voting_type = vote_type;
        num_total_candidates = total_candidates;
        num_ballots = nballots;
        num_total_seats = total_seats;
        file_auditing = file;
}

//! A function that use to find max length of Party name
bool Report::Candidate_comparator(Candidate& c1, Candidate& c2) {
	return c1.GetName().length() < c2.GetName().length();
}

//! Function to Extract Name of any file(Ex: hello.csv will return hello)
string Report::ExtractFileName(std::string file) {
    return file.substr(0, file.find("."));
}

//! Function to find the current time
string Report::CurrentDateTime() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return dt;
}

//! Function to find the longest name of Candidate in a Party Vector
int Report::FindLongestCPLCandidateName(vector <Party> pa) {
    std::vector <string> mystr = {};
    int first_cand = 0;
    std::string currentCand = "";
    for (auto p: pa) { // For in list of parties
        std::vector <Candidate> allCandidates = p.GetCandidates();
        first_cand = 0;
        currentCand = "";
        for (auto c: allCandidates) { // for in list of candidate from a party
            if (first_cand == 0) {
                first_cand ++;
                currentCand += (c.GetName());
            }
            else {
                currentCand += (", " + c.GetName());
            }
        } // concat all name in list of candidate of a party
        mystr.push_back(currentCand);
    }
    int max = mystr[0].length();
    // Extract max length of a name
    for (int i = 1; i < static_cast<int>(mystr.size()); i++) {
        if (static_cast<int>(mystr[i].length()) > max) {
            max = mystr[i].length();
        }
    }
    return max;
}

// Display General  information of the Audit process
void Report::DisplayGeneral() {
  // start generating the audit result from here
  std::cout << "=========================AUDIT RESULT=========================="
    << std::endl;
  // start printing all information for each party from here by providing
  // all neccesary information to the screen
  std::cout<< "Voting Type: " << voting_type << std::endl;
  std::cout<< "Number of Total Candidates: " << num_total_candidates
    << std::endl;
  std::cout<< "Number of Total Seats: " << num_total_seats << std::endl;
  std::cout<< "Number of Ballots: " << num_ballots << std::endl;
  std::cout<< "-------" << std::endl;
  cout <<  "PARTY/SEAT RECIEVED: " << endl;
  // Display general title of a winner
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    cout <<  Winner[i].GetName() << " - " << Winner[i].GetNumSeats() << " seats"
        << " - " << Winner[i].GetNumVotes() << " total votes" << endl;
  }
}

// Dispay the OPL party to report the winner
void Report::DisplayOPL() {
  DisplayGeneral();
  std::cout << "-------" << std::endl;
  // start reporting the OPL winner from here
  std::cout << "OPL REPORT WINNERS:" << std::endl;
  std::cout << "-------" << std::endl;
  // create a table to organize all the information for the OPL winner
  std::cout << std::left << setw(MAX_CAND_NAME_WIDTH) << "Candidate Name"
            << setw(20) << "Party Name" << setw(20) << "Number of Vote"
            << std::endl;
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
        j++) {
      // display OPL winner infor
      std::cout << std::left << setw(MAX_CAND_NAME_WIDTH)
              << Winner[i].list_candidates_[j].GetName()
              << setw(20) << Winner[i].GetName() << setw(20)
              <<  Winner[i].list_candidates_[j].list_ballot_id_.size()
              << std::endl;
    }
  }
  // the result of winner has ended here
  std::cout << "==========================END RESULT==========================="
    << std::endl;
}

// display CPL party to report the winner
void Report::DisplayCPL() {
  DisplayGeneral();
  std::cout << "-------" << std::endl;
  // start reporting the CPL winner from here
  std::cout << "CPL REPORT WINNERS:" << std::endl;
  std::cout << "-------" << std::endl;
  // create a table to organize all the information for the CPL winner
  std::cout << std::left << setw(10) << "Party"<< setw(MAX_CAND_NAME_WIDTH)
        << "Number of Seats" << setw(30) << "Winners Name"
        << setw(20) << "Number of Vote" << std::endl;
  // loop through to fine the winner in list of candidate and get their name
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    std::string winnerCandidateNames = "";
    for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
        j++) {
      if (j == 0) {
        winnerCandidateNames += (Winner[i].list_candidates_[j].GetName());
      }
      else {
        winnerCandidateNames += (", " +Winner[i].list_candidates_[j].GetName());
      }
    }
    // creat a table to organize all the information of the winner
    std::cout << std::left << setw(10) << Winner[i].GetName() << setw(20)
      << Winner[i].GetNumSeats() << setw(MAX_CAND_NAME_WIDTH+20)
      << winnerCandidateNames << setw(20) << Winner[i].GetBallotList().size()
      << std::endl;
  }
  // the winner result has ended here
  std::cout << "==========================END RESULT==========================="
    << std::endl;
}

// display the report for OPL or CPL
void Report::Display() {
  if (voting_type == "OPL") {
    DisplayOPL();
  } else {
    DisplayCPL();
  }
}

// export the audit file to the same directory
void Report::ExportToAuditFile() {
  if (voting_type == "OPL") {
    ExportToAuditFileOPL();
  } else {
    ExportToAuditFileCPL();
  }
}

// export to audit file for OPL party by providing all neccesary information
// and teh voting result for OPL party in to the file
void Report::ExportToAuditFileOPL() {
  std::ofstream file(audit_result_file_name_);
  // the audit result starts here
  file << "=========================AUDIT RESULT=========================="
    << std::endl;
  file << "Voting Type: " << voting_type << "\n";
  file << "Number of Total Candidates: " << num_total_candidates << "\n";
  file << "Number of Total Seats: " << num_total_seats << std::endl;
  file << "Number of Ballots: " << num_ballots << std::endl;
  // The candidates infomation contain all candidates in party
  file << "-------" << std::endl;
  file <<  "PARTY/CANDIDATE INFO: " << endl;
  // loop through to find all the candidate information
  for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
    file << "Party " << AllCandidateParty[i].GetName() << " has candidates: ";
    std::string all_candidates = "";
    for (int j = 0;
        j < static_cast<int> (AllCandidateParty[i].list_candidates_.size());
        j++) {
      if (j == 0) { // concat candidate name
        all_candidates += (AllCandidateParty[i].list_candidates_[j].GetName());
      }
      else {  // concat candidate name with comma
        all_candidates += (", " +
          AllCandidateParty[i].list_candidates_[j].GetName());
      }
    }
    file << all_candidates << "\n"; //All candidate names from a party into file
  }
  file << "-------" << std::endl;
  file <<  "PARTY/SEAT RECIEVED: " << endl;
  // loop through to find the winners result
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    file <<  Winner[i].GetName() << " - " << Winner[i].GetNumSeats() << " seats"
        << " - " << Winner[i].GetNumVotes() << " total votes" << endl;
  } /* for */
  file << "-------" << std::endl;
  file << "Ballot ID List: "<< endl;
  // export all list of ballot corresponding to party and candidate
  for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
    file << "Party: " << AllCandidateParty[i].GetName() << "\n";
    for (int j = 0;
        j < static_cast<int> (AllCandidateParty[i].list_candidates_.size());
        j++) {
      file << "-------" << (AllCandidateParty[i].list_candidates_[j].GetName())
      << " : "
      << ConcatListInt(AllCandidateParty[i].list_candidates_[j].list_ballot_id_)
      << "\n";;
    }
  } /* for */

  file << "-------" << std::endl;
  // report the OPL winner has started here
  file << "OPL REPORT WINNERS:" << std::endl;
  file << "-------" << std::endl;
  // create a table to organize all the information for OPL winner
  file << std::left << setw(MAX_CAND_NAME_WIDTH) << "Candidate Name"
            << setw(20) << "Party Name" << setw(20) << "Number of Vote"
            << std::endl;
  // export all winner information
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
        j++) {
      // winner infor
      file << std::left << setw(MAX_CAND_NAME_WIDTH)
            << Winner[i].list_candidates_[j].GetName()
            << setw(20) << Winner[i].GetName() << setw(20)
            << to_string(Winner[i].list_candidates_[j].list_ballot_id_.size())
            << std::endl;
    }
  }
  // the result of the winner has ended here
  file << "==========================END RESULT==========================="
    << std::endl;
}

// export to audit file for CPL party by providing all neccesary information
// and voting result related to CPL party into the file
void Report::ExportToAuditFileCPL() {
  std::ofstream file(audit_result_file_name_);
  // Start report teh audit result into file
  file << "=========================AUDIT RESULT=========================="
    << std::endl;
  // start providing all the neccesary information for CPL party
  file << "Voting Type: " << voting_type << "\n";
  file << "Number of Total Candidates: " << num_total_candidates << "\n";
  file << "Number of Total Seats: " << num_total_seats << std::endl;
  file << "Number of Ballots: " << num_ballots << std::endl;
  // The candidates infomation contain all candidates in party
  file << "-------" << std::endl;
  file <<  "PARTY/CANDIDATE INFO: " << endl;
  // walking thorough list of party
  for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
    file << "Party " << AllCandidateParty[i].GetName() << " has candidates: ";
    std::string all_candidates = "";
    // walking thorough list of candidate from a party
    for (int j = 0;
        j < static_cast<int> (AllCandidateParty[i].list_candidates_.size());
        j++) {
      if (j == 0) {
        all_candidates += (AllCandidateParty[i].list_candidates_[j].GetName())
          + " - " +
          to_string(AllCandidateParty[i].list_candidates_[j].GetPriority());
      }
      else { // concat candidate name with comma
        all_candidates += (", "
          + AllCandidateParty[i].list_candidates_[j].GetName())
          + " - "
          + to_string(AllCandidateParty[i].list_candidates_[j].GetPriority());
      }
    }
    file << all_candidates << "\n";//All candidate names from a party into file
  }
  file << "-------" << std::endl;
  file <<  "PARTY/SEAT RECIEVED: " << endl;
  // loop through to find the information for the winner
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    file <<  Winner[i].GetName() << " - " << Winner[i].GetNumSeats() << " seats"
        << " - " << Winner[i].GetNumVotes() << " total votes" << endl;
  }
  file << "-------" << std::endl;
  file << "Ballot ID List: "<< endl;
  // concat the list of ballot
  for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
    file << "-----Party: " << AllCandidateParty[i].GetName() << " : "
      << ConcatListInt(AllCandidateParty[i].GetBallotList()) << "\n";
  }

  file << "-------" << std::endl;
  // CPL has reported the winners from here
  file << "CPL REPORT WINNERS:" << std::endl;
  file << "-------" << std::endl;
  // create a table to organize all the information for the CPL winner
  file << std::left << setw(10) << "Party"<< setw(MAX_CAND_NAME_WIDTH)
        << "Number of Seats" << setw(30) << "Winners Name"
        << setw(20) << "Number of Vote" << std::endl;
  // export all winner information
  for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
    std::string winnerCandidateNames = "";
    for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
        j++) {
      if (j == 0) { // concat candidate name
        winnerCandidateNames += (Winner[i].list_candidates_[j].GetName());
      }
      else { // concat candidate name with comma
        winnerCandidateNames += (", " +Winner[i].list_candidates_[j].GetName());
      }
    }
    // a winner info
    file << std::left << setw(10) << Winner[i].GetName() << setw(20)
      << Winner[i].GetNumSeats() << setw(MAX_CAND_NAME_WIDTH+20)
      << winnerCandidateNames << setw(20)
      << to_string(Winner[i].GetBallotList().size())
      << std::endl;
  }
  // the audit reported has ended here
  file << "==========================END RESULT==========================="
    << std::endl;
}

// concatenate the list of integer
std::string Report::ConcatListInt(std::vector <int> intList) {
  std::string concat_ballot_id = "";
  // looping through the size of integer list
  for (int i = 0; i < static_cast<int> (intList.size()); i++) {
    if (i == 0) {
        concat_ballot_id += to_string(intList[i]);
    } else {
      concat_ballot_id += (", " + to_string(intList[i]));
    }
  }
  return concat_ballot_id;
}

// export the audit result to the public file for sharing the result of voting
void Report::ExportToPublicFile() {
  std::ofstream file(sharing_result_file_name_);
  file << "=========================AUDIT RESULT=========================="
    << std::endl;
  file << "Voting Type: " << voting_type << "\n";
  file << "Number of Total Candidates: " << num_total_candidates << "\n";
  file << "Number of Total Seats: " << num_total_seats << std::endl;
  file << "Number of Ballots: " << num_ballots << std::endl;
  // The candidates infomation contain all candidates in party
  file << "-------" << std::endl;
  file <<  "PARTY/CANDIDATE INFO: " << endl;
  // check to see if the voting type is OPL or CPL
  if (voting_type == "OPL") {
    for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
      file << "Party " << AllCandidateParty[i].GetName() << " has candidates: ";
      std::string all_candidates = "";
      // concat all name of candidates
      for (int j = 0;
          j < static_cast<int> (AllCandidateParty[i].list_candidates_.size());
          j++) {
        if (j == 0) {
          all_candidates += (AllCandidateParty[i].list_candidates_[j].GetName());
        }
        else {
          all_candidates += (", "
            + AllCandidateParty[i].list_candidates_[j].GetName());
        }
      }
      file << all_candidates << "\n"; // concat all name of candidates
    }
    file << "-------" << std::endl;
    // reporting the OPL winners into the file by providing the important result
    // of the winner
    file << "OPL REPORT WINNERS:" << std::endl;
    file << "-------" << std::endl;
    file << std::left << setw(MAX_CAND_NAME_WIDTH) << "Candidate Name"
              << setw(20) << "Party Name" << setw(20) << "Number of Vote"
              << std::endl;
    for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
      for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
          j++) {
            // export winner infor
        file << std::left << setw(MAX_CAND_NAME_WIDTH)
              << Winner[i].list_candidates_[j].GetName()
              << setw(20) << Winner[i].GetName() << setw(20)
              << to_string(Winner[i].list_candidates_[j].list_ballot_id_.size())
              << std::endl;
      } /* for j */
    } /* for i */
  } else {
    file << "-------" << std::endl;
    file <<  "PARTY/CANDIDATE INFO: " << endl;
    // Export all candidate from list of party info
    for (int i = 0; i < static_cast<int> (AllCandidateParty.size()); i++) {
      file << "Party " << AllCandidateParty[i].GetName() << " has candidates: ";
      std::string all_candidates = "";
      // concat all candidate in a party
      for (int j = 0;
          j < static_cast<int> (AllCandidateParty[i].list_candidates_.size());
          j++) {
        if (j == 0) {
          all_candidates += (AllCandidateParty[i].list_candidates_[j].GetName())
            + " - "
            + to_string(AllCandidateParty[i].list_candidates_[j].GetPriority());
        }
        else { // concat name with comma
          all_candidates += (", "
            + AllCandidateParty[i].list_candidates_[j].GetName())
            + " - "
            + to_string(AllCandidateParty[i].list_candidates_[j].GetPriority());
        }
      }
      // export list name of candidates from a party
      file << all_candidates << "\n";
    }

    file << "-------" << std::endl;
    // report the CPL winners
    file << "CPL REPORT WINNERS:" << std::endl;
    file << "-------" << std::endl;
    file << std::left << setw(10) << "Party"<< setw(MAX_CAND_NAME_WIDTH)
          << "Number of Seats" << setw(30) << "Winners Name"
          << setw(20) << "Number of Vote" << std::endl;

    for (int i = 0; i < static_cast<int> (Winner.size()); i++) {
      std::string winnerCandidateNames = "";
      for (int j = 0; j < static_cast<int> (Winner[i].list_candidates_.size());
          j++) {
        if (j == 0) {
          winnerCandidateNames += (Winner[i].list_candidates_[j].GetName());
        }
        else {
          winnerCandidateNames += (", "
            + Winner[i].list_candidates_[j].GetName());
        }
      }
      // Export CPL winner info
      file << std::left << setw(10) << Winner[i].GetName() << setw(20)
        << Winner[i].GetNumSeats() << setw(MAX_CAND_NAME_WIDTH+20)
        << winnerCandidateNames << setw(20)
        << to_string(Winner[i].GetBallotList().size())
        << std::endl;
    }
  }

  file << "==========================END RESULT==========================="
      << std::endl;
} /* ExportToPublicFile() */

// NOTICE: THIS FUNCTION IS OUT OF SCOPE, WE WONT PROVIDE ANY TEST FOR THIS
// export the short report file to the election officials
void Report::ExportToShortReport() {
    std::string is_winner = "NO";
    int first_cand = 0;
    int cand_count = 0;
    int count = 0;
    int max_cand_opl_ele_len = 0;
    vector <string> concatCandName;
    int maxConcatCands = 0;
    int max_cand_width = 0;
    std::string all_candidates = "";
    std::string all_party_and_seat = "";
    std::string allCandidate = "";
    std::vector <int> ballot_id_list = {};
    std::string concat_ballot_id = "";
    std::string candidate_list = "";
    // std::string name = "Short_report_" + ExtractFileName(file_auditing) + ".txt";
    std::string name = file_auditing;
    std::ofstream file;
    file.open(name);
    file << "Current Date & Time: " << CurrentDateTime();
    file << "Voting Type: " << voting_type << "\n";

    // Loop through all Candidate Party
    for (auto a: AllCandidateParty) {
        count++;
        if (count == 1) {
            for (auto h: AllCandidateParty) {
                file << "Party " << h.GetName() << " has candidates: ";
                all_candidates = "";
                // Concate all Candidate Names
                for (auto c: h.GetCandidates()) {
                    all_candidates += c.GetName();
                    cand_count++;
                    if (unsigned(cand_count) != h.GetCandidates().size()) {
                        all_candidates += ", ";
                    } else {
                        all_candidates += ".";
                    }
                }
                cand_count = 0;
                file << all_candidates << "\n";
            }
            // Print out to file number of seat for each Party with Candidates Name
            for (auto k: AllCandidateParty) {
                file << "Number of Seats for Party " <<  k.GetName() << ": " << k.GetNumSeats() << "\n";
            }
        }
        if (voting_type == "OPL") { // FOR OPL
            std::vector <Candidate> allOPLCandidates = a.GetCandidates();
            // Find the max length of Candidate Names and use it to set whitespace in table
            auto find_ele = std::max_element(allOPLCandidates.begin(), allOPLCandidates.end(), Candidate_comparator);
            max_cand_opl_ele_len = (find_ele->GetName()).length();
            if (max_cand_opl_ele_len >  static_cast<int>(std::strlen("Candidate Name"))) {
                max_cand_width = max_cand_opl_ele_len + 5;
            } else {
                max_cand_width = std::strlen("Candidate Name") + 5;
            }
            if (count == 1) {
                file << "\n";
                // report all the candidates name, parties, and the winners into the file
                // by using the set whitespace to create a table
                file << "All Candidates, Their Parties, and The Winner" << "\n";
                file << "---------------------------------------------" << "\n";
                file << std::left << setw(max_cand_width) << "Candidate Name" << setw(20) << "Party Name" << setw(10) <<"Winner?" << "\n";
            }
            is_winner = "NO";
            // Loop through the Winner and set YES to a winner or Default= NO is loser
            for (auto c: allOPLCandidates) {
                for (auto w: Winner) {
                    for (auto r: w.GetCandidates()){
                        if (r.GetName() == c.GetName()) {
                            is_winner = "YES";
                        }
                    }
                }
                // creating a table
                file << std::left << setw(max_cand_width) << c.GetName() << setw(20) << a.GetName() << setw(10) << is_winner << "\n";
                is_winner = "NO";
            }
        }
        else { // FOR CPL
            std::vector <Candidate> allCPLCandidates = a.GetCandidates();
            // Find the longest concate name for each Winner Party
            maxConcatCands = FindLongestCPLCandidateName(AllCandidateParty);
            if (unsigned(maxConcatCands) < strlen("List of Winner Candidate Name")) {
                maxConcatCands = strlen("List of Winner Candidate Name") + 5;
            }
            file << "\n";
            file << "All Candidates and Their Parties" << "\n";
            file << "--------------------------------" << "\n";
            // creating a table to report Party, Number of seat, list of candidate, winner.
            file << std::left << setw(10) << "Party"<< setw(20) << "Number of Seats For Party" << setw(maxConcatCands+5) << "List of Candidates Name" << setw(20) << "Winner?" << "\n";
            allCandidate = "";
            first_cand = 0;
            is_winner = "NO";
            // Loop to concate all Candidates name for each party and set it to YES
            for (auto c: allCPLCandidates) {
                if (first_cand == 0) {
                    first_cand ++;
                    allCandidate += (c.GetName());
                }
                allCandidate += (", " + c.GetName());
                for (auto w: Winner) {
                    for (auto r: w.GetCandidates()){
                        if (r.GetName() == c.GetName()) {
                            is_winner = "YES";
                        }
                    }
                }
                // Print to file info in form of a table
                file <<  std::left << setw(10) << a.GetName() << setw(20) << a.GetNumSeats() << setw(maxConcatCands+5) << allCandidate << setw(20) << is_winner << "\n";
                is_winner = "NO";
            }
        }
    }
    file.close();
}

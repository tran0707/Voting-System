/**
 * @file voting_system.cc
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <time.h>
#include <cstdio>
#include <sstream>      // std::istringstream
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <numeric>
#include <random>

#include "cpl.h"
#include "sortby.h"
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void CPL::ReadFile (std::string file_name) {
	std::ifstream fin(file_name);
	if (!fin)	{
		std::cout << "OPS...! Error opening input file." << std::endl;
	} else { // success open file
		int count = 1;
		std::string line;
		int ballot_pos = 1;
		while (getline(fin, line)) {
			if (count != 1) { // Skip 1st line
				if (count == 2) { // Number of Parties
					// NO NEED
					// report_.SetNumParties(stoi(line));
				} else if (count == 3) { // Parties in Order of Ballot Ordering
					std::string sub_line = line.substr(1, line.length() - 2);
					std::string ch;
					std::istringstream ss(sub_line);
					while (std::getline(ss, ch, ',')) {
						parties_.push_back(Party(ch));
					}
				} else if (count == 4) {
					total_seats_ = stoi(line);
					report_.SetNumTotalSeats(total_seats_);
				} else if (count == 5) { // Number of Ballots
					total_votes_ = stoi(line);
					report_.SetNumBallots(total_votes_);
				} else if (count == 6) { // Number of Candidates
					report_.SetNumToTalCandidates(stoi(line));
				}
				// Following line 6 are the candidates’ information
				else if (count < 6 + report_.GetNumTotalCandidates() + 1) {
					// Remove [] of string, eg "[Mike]" => "Mike"
					std::string sub_line = line.substr(1, line.length() - 2);
					// (e.g "Mike, D, 11" => ["Mike", "D", "11"])
					std::vector<std::string> candidate_info = SplitByComma(sub_line);
					// Add candidates to correspond party in parties list
					for (unsigned i = 0; i < parties_.size(); i++) {
						if (parties_[i].GetName() == candidate_info[1]) {
							parties_[i].AddCandidate(Candidate(candidate_info[0],
								stoi(candidate_info[2])));
							break;
						}
					}
				} else { // following is all of the ballots
					// Remove [] of string, eg "[Mike]" => "Mike"
					std::string sub_line = line;
					// (e.g "Mike, D, 11" => ["Mike", "D", "11"])
					std::vector<std::string> ballot_info = SplitByComma(line);
					// Count ballot for each party
					for (unsigned i = 0; i < ballot_info.size(); i++) {
						if (ballot_info[i] == "1") {
							parties_[i].AddBallotId(ballot_pos);
							break;
						}
					}
					ballot_pos++;
				}
			}
			count++;
		} /* while */
		fin.close();
		fin.clear();
	} /* else */
}  /* ReadFile */

void CPL::Audit() {
	// setup the number of voters for each party
	for (int i = 0; i < static_cast<int> (parties_.size()); i++) {
		parties_[i].SetNumVotes(parties_[i].GetBallotList().size());
	}
	// distribute seat into party
	DistributeSeatsToParty();

	std::vector <Party> winners;
	// Set up the list of winner
	for (int i = 0; i < static_cast<int> (parties_.size()); i++) {
		if (parties_[i].GetNumSeats() > 0) {
			winners.push_back(DistributeSeatToCandidate(parties_[i]));
		}
	}
	// transfer winner data + all original candidate to report
	report_.SetVecAllParty(parties_);
	report_.SetVecWinnerParty(winners);
} /* Audit() */

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
#include <functional>
#include <ctime>

#include "opl.h"
using namespace std;
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void OPL::ReadFile(std::string file_name) {
	std::ifstream fin(file_name);
	if (!fin) {
        cout << "OPS...! Error opening input file." << endl;
  } else { // success open file
		int count = 1;
		std::string line;
		int ballot_order = 1;
		while (getline(fin, line)) {
			if (count != 1) { // Skip 1st line
				if (count == 2) { // Number of Seats
					total_seats_ = stoi(line);
					report_.SetNumTotalSeats(total_seats_);
				} else if (count == 3) { // Number of Ballots
					report_.SetNumBallots(stoi(line));
				} else if (count == 4) { // Number of Candidates
					report_.SetNumToTalCandidates(stoi(line));
				}
				// Following the 4th line are the candidates info.
				else if (count < 4 + report_.GetNumTotalCandidates() + 1) {
					// Read the candidate into parties list, similar to CPL
					// Remove [] of string, eg "[Mike]" => "Mike"
					std::string sub_line = line.substr(1, line.length() - 2);
					std::string ch;
					std::istringstream ss(sub_line);
					int pos = 0;
					// Read candidate info
					Candidate candidate;
					while (std::getline(ss, ch, ',')) {
						if (pos == 0) {
							candidate = Candidate(ch);
						}
						else if (pos == 1) {
							bool update = false;
							// whether candidate create new party
							for (int i = 0;  i < static_cast<int> (parties_.size()); i++) {
								if (parties_[i].GetName() == ch) {
									update = true;
										// Adding candidate to approriate party
									parties_[i].AddCandidate(candidate);
									candidate_pos_.push_back(std::make_pair(i,
										parties_[i].GetCandidates().size() - 1));
									break;
								}
							}
							if (update == false) {
								Party party = Party(ch);
								parties_.push_back(party);
								// Adding candidate to approriate party
								parties_[parties_.size() - 1].AddCandidate(candidate);
								candidate_pos_.push_back(std::make_pair(parties_.size() - 1,0));
							}
						}
						pos++;
					} /* While */
				} else { // The following is ballot info
					std::string ch;
					std::istringstream ss(line);
					int vote_for_candidate_pos = 0;
					while (std::getline(ss, ch, ',')) {
						if (ch == "1") {	// check what voter vote for
							parties_[candidate_pos_[vote_for_candidate_pos].first]
								.list_candidates_[candidate_pos_[vote_for_candidate_pos].second]
									.list_ballot_id_.push_back(ballot_order);
							total_votes_++;
							break;
						}
						vote_for_candidate_pos++;
					} /* while */
					ballot_order++;
				}
			}
			count++;
		} /* while */
		fin.close();
		fin.clear();
	} /* else */
	fin.close();
	fin.clear();
} /* ReadFile */

/* The goal of this function is to create a
 * new Party list to replace the original.
 * The new list will only contain the winners,
 * and kicking out the losers.
 * Then, it is up for report.cc to display them.
*/
void OPL::Audit() {
	// distribute votes into candidate
	PopulateVotes() ;
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

void OPL::PopulateVotes() {
	// Populate each party's total votes
	// Also populate each candidates vote count
	for (int i = 0; i < static_cast<int> (parties_.size()); i++) {
		int accum = 0;
		for (int j = 0; j < static_cast<int> (parties_[i].list_candidates_.size());
		 j++) {
			int cand_vote_count = static_cast<int>
				(parties_[i].list_candidates_[j].list_ballot_id_.size());
			parties_[i].list_candidates_[j].SetOrderPriorityParty(-cand_vote_count);
			accum += cand_vote_count;
		}  /* for (int J  */
		parties_[i].SetNumVotes(accum);
	} /* for (int i  */
} /* PopulateVotes() */

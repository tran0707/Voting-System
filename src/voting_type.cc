/**
 * @file voting_system.cc
 *
 * @brief VotingType's destructor. `delete` all objects created.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <time.h>
#include<cstdio>
#include <string>
#include <numeric>
#include <random>
#include <vector>

#include "voting_type.h"
#include "opl.h"
#include "params.h"
#include "sortby.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
using namespace std;
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
VotingType::VotingType() { }

VotingType::~VotingType() { }

/*******************************************************************************
 * Helper Functions
 ******************************************************************************/

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

std::vector<int> VotingType::RandomSelectWinner(int num) {
	std::vector<int> v(num);
	std::iota(v.begin(), v.end(), 0);
	srand(time(NULL));
	int any_num = rand() % RAND_A_NUM_LESS_THAN;		// Random 1st time
	for (int i = 0; i < any_num ; i ++) {
		// shuffle n times where n is a random number < predefine number.
		// random_shuffle will make sure it is random list
		std::random_shuffle(v.begin(), v.end());
	}
	return v;
} /* RandomSelectWinner() */

void VotingType::DistributeSeatsToParty() {
	/** make pair vector with
	* first: party remain votes Number
	* second: position of party in list of Parties
	* because I want to hold order of new party as the original list of party
	*/
	std::vector <std::pair<int, int>> parties;
	int remaining_seat = report_.GetNumTotalSeats();
	// calculate quota for voting
	int quota = report_.GetNumBallots() / report_.GetNumTotalSeats();
	// start 1st round distribution
	for (int i = 0; i <  static_cast<int> (parties_.size()); i++) {
		int num_seats =
			 (static_cast<int> (parties_[i].GetNumVotes()))/quota;
		parties_[i].SetNumSeats(num_seats);
		parties_[i].SetRemainingVotes(
			 static_cast<int> (parties_[i].GetNumVotes()) % quota);
		// remain seat info is in new parties vector
		parties.push_back(std::make_pair(parties_[i].GetRemainingVotes(),i));
		remaining_seat -= num_seats;
	}	/* for() */

	// Seek rand
	srand(rand());
	int randomize = rand() % A_SMALL_RAND_NUM;		// Random 1st time
	for (int i = 0; i < randomize ; i ++) {
		// shuffle n times where n is a random number < predefine number.
		// random_shuffle will make sure it is random list
		std::random_shuffle(parties.begin(), parties.end());
	}		/* for() */
	// the new parties are sort, if parties are tie, they are in random place
	// but still in decend order
	std::sort(parties.begin(), parties.end(), sortbypartyvote());
	// start 2nd round distribution
	for (int i = 0; i < remaining_seat; i++) {
		parties_[parties[i].second].
			SetNumSeats(parties_[parties[i].second].GetNumSeats()+1);
	}	/* for() */
} /* DistributeSeatsToParty() */

Party VotingType::DistributeSeatToCandidate(Party p) {
	/** SIMILARLY to DistributeSeatsToParty()
	* make pair vector with
	* first: candidate priority value
	* second: position of candidate in list of candidates
	* because want to hold order of new candidate as original list of candidates
	*/
	std::vector <std::pair<int, int>> new_list_cand;
	//  make pair vector new_list_cand contains candidate info
	for (int i = 0; i < static_cast<int> (p.list_candidates_.size()); i++) {
		new_list_cand.push_back(
				std::make_pair(p.list_candidates_[i].GetPriority(),i));
	} /* for() */

	// Seek rand
	srand(rand());
	int randomize = rand() % A_SMALL_RAND_NUM;		// Random 1st time
	for (int i = 0; i < randomize ; i ++) {
		// shuffle n times where n is a random number < predefine number.
		// random_shuffle will make sure it is random list
		std::random_shuffle(new_list_cand.begin(), new_list_cand.end());
	}	/* for() */
	// the new list cand is sorted, if cands are tie, they are in random place
	// but still in decend order
	std::sort(new_list_cand.begin(), new_list_cand.end(), sortbypriority());

	Party new_party = p;
	new_party.EmptyCandidate();
	// Start distribute seats to cands, return new_party contain winner candidate
	for (int i = 0; i < p.GetNumSeats(); i++) {
			new_party.AddCandidate(p.list_candidates_[new_list_cand[i].second]);
	}	/* for() */
	return new_party;
} /* DistributeSeatToCandidate() */

std::vector<std::string> VotingType::SplitByComma(std::string str) {
	char delimiter = ',';
	std::vector<std::string> result;
	std::string temp = "";
	for (int i = 0; i < static_cast<int> (str.size()); i++) {
		if (str[i] == delimiter) {
			// push the characters before comma the reset temp
			result.push_back(temp);
			temp = "";
		} else {
			// the characters before comma
			temp += str[i];
		}
	} /* for */
	result.push_back(temp);
	return result;
} /* SplitByComma() */

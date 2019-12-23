/**
 * @file party.h
 *
 * @copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.
 */
#ifndef SRC_PARTY_H
#define SRC_PARTY_H


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "candidate.h"

class Candidate;
/**
 * @brief A Party mainly holds instances of Candidates.
 * It also contains some variables for seat distribution
 * calculation.
 */
class Party {
 public:
  /**
  * @brief Party is a constructor of class Party for Open Party List (OPL)
  *
  * that contains the name of party and the vector of candidates
  *
  * @return None
  */
  Party(std::string name, std::vector<Candidate> candidates );
  /**
  * @brief Party is a constructor of class Party for Closed Party List (CPL)
  *
  * that contains only the name of the party
  *
  * @return None
  */
  Party(std::string name);
  /**
  * @brief Party is a default constructor
  *
  * @return None
  */
  Party();
  /**
  * @brief set the name of each party
  *
  * @return name_
  */
  //Party(const Party &p);
  std::string SetName(std::string name);
  /**
  * @brief get the name of each party
  *
  * @return name_
  */
  std::string GetName();
  /**
  * @brief get the list of candidates from the Candidate class
  *
  * @return list_candidates_
  */
  std::vector <Candidate> GetCandidates();
  /**
  * @brief get the number of seats
  *
  * @return num_seats_
  */
  int GetNumSeats();
  /**
  * @brief get the number of votes
  *
  * @return num_votes_
  */
  int GetNumVotes();
  /**
  * @brief set the number of votes
  *
  * @return None
  */
  void SetNumVotes(int num);
  /**
  * @brief get the number of candidates
  *
  * @return  num_candidates_
  */
  int GetNumCandidate();
  /**
  * @brief add the candidate into the list of candidates
  *
  * @return None
  */
  void AddCandidate(Candidate candidate);
  /**
  * @brief set the number of seats
  *
  * @return None
  */
  void SetNumSeats(int num);
  /**
  * @brief add the ballot identification into the list of ballot
  *
  * identification
  *
  * @return None
  */
  void AddBallotId(int ballot_id);
  /**
  * @brief get the list of ballots
  *
  * @return list_ballot_id_
  */
  std::vector<int> GetBallotList();
  /**
  * @brief candidate contains a list of candidates
  *
  * @return
  */
  std::vector <Candidate> list_candidates_{};

  void SetCandidates(std::vector<Candidate> cands);
  /**
  * @brief get the list of ballots
  *
  * @return list_ballot_id_
  */
  int GetRemainingVotes() { return remaining_votes_;}
  void SetRemainingVotes(int num) { remaining_votes_ = num; }
  void EmptyCandidate();
//  void SetCandidates(const std::vector <Candidate> c);
 private:
  // the remaining votes using for audit
  int remaining_votes_{0};
	// the name of party
	std::string name_{""};
  // the number of seats for each parties
	int num_seats_{0};
	// the number of candidates of each parties
	int num_candidates_{0};
	// the number of votes for each parties
	int num_votes_{0};
	// the list of identification's ballot
	std::vector <int> list_ballot_id_{};
};
#endif  // SRC_PARTY_H

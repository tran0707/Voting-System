// copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "party.h"
#include "candidate.h"
#include <iostream>
#include <string>
#include <list>

// Party is a constructor for OPL, and it takes 2 arguments which are name and candidates
Party::Party(std::string name, std::vector <Candidate> candidates) {
 name_ = name;
 list_candidates_ = candidates;
}

// Party is a constructor for CPL, and it takes 1 argument which is name
Party::Party(std::string name) {
	name_ = name;
}

// Party is a Default constructor
Party::Party() {

}

// Set the name of the party
std::string Party::SetName(std::string name) {
  name_ = name;
  return name_;
}

// Get the name of the party
std::string Party::GetName() {
return name_;
}

// Get the list of the candidates in the party
std::vector<Candidate> Party::GetCandidates() {
  return list_candidates_;
}

//void Party::SetCandidates1(const std::vector <Candidate> c) {
//   list_candidates_ ={};
//   list_candidates_ = c;
// }

// Get the number of seats of the party
int Party::GetNumSeats() {
  return num_seats_;
}

// Get the number of votes of the party
int Party::GetNumVotes() {
  return num_votes_;
}

// Get the number of candidates of the party
int Party::GetNumCandidate() {
  return num_candidates_;
}

// Set the number of seats of the party
void Party::SetNumSeats(int num) {
  num_seats_ = num;
}

// Set the number of votes of the party
void Party::SetNumVotes(int num) {
  num_votes_ = num;
}

// Add the candidate in to the list of candidates in the party
void Party::AddCandidate(Candidate candidate) {
  // using the push_back function to add the candidates into the list of candidates
  list_candidates_.push_back(candidate);
}

// Make the list of candidates empty
void Party::EmptyCandidate() {
  list_candidates_ = {};
}

// Set the list of candidates
void Party::SetCandidates(std::vector<Candidate> cands) {
    list_candidates_ = {};
  list_candidates_ = cands;
}

// Add the ballots identification into the list of ballots
void Party::AddBallotId(int ballot_id) {
  // using the push_back function to add the ballots identification into the list
  // of candidates
	list_ballot_id_.push_back(ballot_id);
}

// Get the list of ballot identification in party
std::vector<int> Party::GetBallotList() {
  return list_ballot_id_;
}

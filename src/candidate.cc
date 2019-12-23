// copyright 2019, Fall Semester, 5801 Student Group 22, All rights reserved.

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "candidate.h"
#include <iostream>
#include <string>
#include <list>

// Candidate is a constructor for CPL, and it takes 2 arguments which is name
// and order_priority_party
Candidate::Candidate(std::string name, int order_priority_party) {
  name_ = name;
  order_priority_party_ = order_priority_party;
}

// Candidate is a constructor for OPL, and it takes 1 argument which is name
Candidate::Candidate(std::string name) {
  name_ = name;
}

// Candidate is a default constructor
Candidate::Candidate() {
}

// Set the order_priority_party for the candidate
void Candidate::SetOrderPriorityParty(int order_priority_party) {
  order_priority_party_ = order_priority_party;
}

// Get the name of the candidate
std::string Candidate::GetName() {
  return name_;
}

// Set the ballot number of candidates
void Candidate::SetBallotNum(int num) {
  counting_ballot = num;
}

// Get the number of ballots for candidates
int Candidate::GetBallotNum() {
  return counting_ballot;
}

// Get the priority order for candidate
int Candidate::GetPriority() {
  return order_priority_party_;
}
